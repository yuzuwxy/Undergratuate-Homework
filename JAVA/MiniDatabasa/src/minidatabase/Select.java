/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Select
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-29  03:57
 */
package minidatabase;

import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.Set;

public class Select {
    public static SqlResult select(String sql) {
        int idxSelect = 6;
        int idxFrom = sql.toLowerCase().indexOf("from");
        int idxWhere = sql.toLowerCase().indexOf("where");
        int idxOrder = sql.toLowerCase().indexOf("order by");
        boolean hasWhere = (idxWhere != -1);
        boolean hasOrder = (idxOrder != -1);
        Set<String> Col = new LinkedHashSet<>();
        String colString = sql.substring(idxSelect, idxFrom).trim();
        String[] colList = colString.split(",");
        for(String col:colList)
            Col.add(col.trim());
        // 获取数据表名
        String tableName = "";
        if(hasWhere)            // 有where条件
            tableName = sql.substring(idxFrom + 4, idxWhere).trim();
        else if(hasOrder)       // 没有where条件，但有order条件
            tableName = sql.substring(idxFrom + 4, idxOrder).trim();
        else
            tableName = sql.substring(idxFrom + 4, sql.length() - 1).trim();
//        System.out.println(tableName);
        // 获取条件的字符串数组
        String conString = "";
        String[] conList = new String[0];
        if(hasWhere) {
            if(hasOrder)
                conString = sql.substring(idxWhere + 5, idxOrder).trim();
            else conString = sql.substring(idxWhere + 5, sql.length() - 1).trim();
            conList = Utils.getConditionList(conString);
        }
        // 获取排序依据
        String orderString = "";
        String[] orderList = new String[0];
        if(hasOrder) {
            orderString = sql.substring(idxOrder + 8, sql.length() - 1).trim();
            orderList = orderString.split(",");
//            System.out.println(orderString);
            for(int i = 0; i < orderList.length; i ++) {
                orderList[i] = orderList[i].trim();
//                System.out.println(orderList[i]);
            }
        }
//        System.out.println(sql);
        SqlResult newObject = new SqlResult();
        // 判断数据表是否存在
        Iterator<TableInfo> it = TableManager.tableInfo.iterator();
        while(it.hasNext()){
            TableInfo info = it.next();
            if(info.Name.equals(tableName)){
                // 判断列是否存在
                boolean colin = true;
                Iterator<String> itSet = Col.iterator();
                int idxSet = 0;
                int[] colIdx = new int[Col.size()];         // colIdx[i]表示选择的第i列在总表中对应列的索引为colIdx[i]
                if(!colString.equals("*")) {
                    while (itSet.hasNext()) {
                        int tmp = Utils.colIn(info, itSet.next());      // 在总表中定位
                        if (tmp == -1) {
                            newObject.sqlFeedBack = "Error: 第 " + (idxSet + 1) + " 个输入的列名不在数据表 " + tableName + " 中\n";
                            colin = false;
                            break;
                        } else
                            colIdx[idxSet] = tmp;
                        idxSet += 1;
                    }
                    if (!colin) break;              // 列不存在，直接退出
                } else {                              // 选择全部的列
                    colIdx = new int[info.colInfo.size()];
                    for (int i = 0; i < info.colInfo.size(); i++)
                        colIdx[i] = i;
                }

                // 便于sqlResult对象输出填充表头（列名）
                int idx = 0;                                // 存储选中数据的二维数组的当前带填充索引
                SqlResult table = Utils.ReadTable(info);    // 将表中的数据读入
                if(colString.equals("*")) {                     // 每个记录选择一整行
                    newObject.valueLines = new Object[table.valueLines.length + 1][info.colInfo.size()];
                    for(int i = 0; i < info.colInfo.size(); i ++)
                        newObject.valueLines[idx][i] = info.colInfo.get(i)[0];
                }
                else {                                          // 只需要选择的列
                    newObject.valueLines = new Object[table.valueLines.length + 1][Col.size()];
                    newObject.valueLines = new Object[table.valueLines.length + 1][Col.size()];
                    Iterator<String> itSet2 = Col.iterator();
                    int tmpidx = 0;
//                    System.out.println(Col.size());
                    while(itSet2.hasNext()) {
                        newObject.valueLines[idx][tmpidx] = itSet2.next();
//                        System.out.println(newObject.valueLines[idx][tmpidx]);
                        tmpidx += 1;
                    }
                }
                idx += 1;

                // 将符合条件的数据写入newObject中
                for(int i = 0; i < table.valueLines.length; i ++) {
                    if(Utils.isFit(table.valueLines[i], conList, info.colInfo)) {   // 如果该条记录符合条件
                        if(colList[0].equals("*"))
                            newObject.valueLines[idx] = table.valueLines[i];
                        else {  // 提取选择的列, 使用LinkedHashSet插入和遍历的顺序是一致的
                            for(int j = 0; j < Col.size(); j ++)
                                newObject.valueLines[idx][j] = table.valueLines[i][colIdx[j]];
                        }
                        idx += 1;
                    }
                }
                newObject.sqlFeedBack = "共有 " + (idx - 1) + " 条记录\n";
                SqlResult resultObject = new SqlResult();
                resultObject.sqlFeedBack = newObject.sqlFeedBack;
                resultObject.valueLines = new Object[idx][newObject.valueLines[0].length];
                for(int i = 0; i < idx; i ++)
                    for(int j = 0; j < resultObject.valueLines[0].length; j ++)
                        resultObject.valueLines[i][j] = newObject.valueLines[i][j];
                newObject = resultObject;

                if(!hasOrder) break;

                // 将写入的数据按照规定排序
                String[][] order = new String[orderList.length][2];             // 第一列存储列名，第二列存储规则
                int k = 0;
                // 1. 分离列名和规则
                for(String tmp:orderList) {
                    String[] cnt = tmp.split(" ");
                    if(cnt.length == 1) {
                        order[k][0] = tmp.trim();
                        order[k][1] = "asc";
                    }
                    else
                        order[k] = cnt;
                    k += 1;
                }

                // 2. 确定order的列名在newobject中对应的列下标
                int [] orderIdx = new int[orderList.length];
                for(int i = 0; i < order.length; i ++) {
                    for(int j = 0; j < newObject.valueLines[0].length; j ++)
                        if(newObject.valueLines[0][j].equals(order[i][0]))
                            orderIdx[i] = j;
                }

                // 3. 进行冒泡排序
                idx = newObject.valueLines.length;
                for(int i = 1; i < idx; i ++){
                    Object[] tmp;
                    for(int j = 1; j < idx - i; j ++ ) {
                        // 遍历orderList即按照优先级排序
                        for(k = 0; k < order.length ; k ++) {
                            // 传入要比较的两个对象，类型，和顺序
//                            System.out.println(order[k][1]);
                            int res = Utils.compare(newObject.valueLines[j], newObject.valueLines[j + 1], orderIdx[k],
                                    info.colInfo.get(colIdx[orderIdx[k]])[1], order[k][1]);
                            if (res < 0) {
                                tmp = newObject.valueLines[j];
                                newObject.valueLines[j] = newObject.valueLines[j + 1];
                                newObject.valueLines[j + 1] = tmp;
                                break;
                            } else if(res == 1) break;
                        }
                    }
                }
                break;
            }
            else newObject.sqlFeedBack = "数据表 " + tableName + " 不存在\n";
        }
        return newObject;
    }
}