/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Update
 * @Author: yuzuwxy
 * @CreateTime: 2022-06-01  17:02
 */
package minidatabase;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;
import java.util.Locale;

public class Update {
    public static SqlResult update(String sql) {
        int idxUpdate = 0;
        int idxSet = sql.toLowerCase().indexOf("set");
        int idxWhere = sql.toLowerCase().indexOf("where");
        String Name = sql.substring(idxUpdate + 6, idxSet).trim();

        // 判断数据表是否存在
        SqlResult object = new SqlResult();
        Iterator<TableInfo> it = TableManager.tableInfo.iterator();
        while(it.hasNext()){
            TableInfo info = it.next();
            if(info.Name.equals(Name)) {
                // 获取set
                String setString = "";
                if(idxWhere != -1) {
                    setString = sql.substring(idxSet + 3, idxWhere).trim();
                }
                else setString = sql.substring(idxSet + 3, sql.length() - 1).trim();
                String[] setList1 = setString.split(",");
                String[][] setList = new String[setList1.length][2];
                for(int i = 0; i < setList1.length; i ++) {
                    setList1[i] = setList1[i].trim();
                    setList[i] = setList1[i].split("=");
                    setList[i][0] = setList[i][0].trim();
                    setList[i][1] = setList[i][1].trim();
                }       // 将等号前后的列名与值分离，存入setList

                // 判断是否为数据表中的列
                int[] setIdx = new int[setList.length];
                int idx = -1, i = 0;
                for(i = 0; i < setList.length; i ++ ) {
                    idx = Utils.colIn(info, setList[i][0]);
                    if(idx == -1) break;
                    else setIdx[i] = idx;
                }
                if(idx == -1) {
                    object.sqlFeedBack = "Error: 列 " + setList[i][0] + " 不在数据表" + Name + "中\n";
                    break;
                }

                // 获取where条件
                String conString = "";
                String[] conList = new String[0];
                if(idxWhere != -1) {
                    conString = sql.substring(idxWhere + 5, sql.length() - 1);
                    conList = Utils.getConditionList(conString);
                }

                object = Utils.ReadTable(info);
                // 对数据表进行修改
                File tableFile = new File(TableManager.PATH, Name + ".midb");
                try {
                    FileWriter fw = new FileWriter(tableFile);
                    fw.write("");
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                int changeNum = 0;
                for(i = 0; i < object.valueLines.length; i ++) {
                    if(Utils.isFit(object.valueLines[i], conList, info.colInfo)) {      //满足条件
                        changeNum += 1;
                        for(int j = 0; j < setList.length; j ++)                        // 修改值
                            object.valueLines[i][setIdx[j]] = (Object) setList[j][1];
                    }
                    String record = "";
                    for(int j = 0; j < object.valueLines[i].length; j ++) {             // 写回
                        if(j != 0) record += ",";
                        record += object.valueLines[i][j];
                    }
//                    System.out.println(record);
                    Utils.Write2table(record, info, true);
                    object.sqlFeedBack = "成功修改 " + changeNum + " 条记录\n";
                }
                break;
            }
            else {
                object.sqlFeedBack = "Error: 数据表 " + Name + " 不存在\n";
            }
        }
        return new SqlResult(object.sqlFeedBack, null);
    }
}