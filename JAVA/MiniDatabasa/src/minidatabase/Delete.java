/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Delete
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-28  11:46
 */
package minidatabase;

import javax.management.Query;
import java.io.*;
import java.util.Iterator;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Delete {
    public static SqlResult delete(String sql) {
        boolean bool = isError(sql.toLowerCase());       // 判断关键词是否有错误
        String Mes = "Error: 语句错误\n";
        if(!bool) {
            int idx = sql.toLowerCase().indexOf("where");
            String Name = sql.substring(12, idx);
            Name = Name.trim();
            // 数据表是否存在
            Iterator<TableInfo> it = TableManager.tableInfo.iterator();
            while(it.hasNext()) {
                TableInfo info = it.next();
                if(info.Name.equals(Name)){
                    SqlResult table = Utils.ReadTable(info);        // 读取数据表的内容
                    int delNum = 0;
                    // 获取条件的字符串数组
                    String conditions = sql.substring(idx + 5, sql.length() - 1);
                    conditions = conditions.trim();
                    String[] condList = Utils.getConditionList(conditions);
                    // 清空文件
                    File tableFile = new File(TableManager.PATH, Name + ".midb");
                    try {
                        FileWriter fw = new FileWriter(tableFile);
                        fw.write("");
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                    // 不符合条件的写入
                    for (int i = 0; i < table.valueLines.length; i++) {
                        if (!Utils.isFit(table.valueLines[i], condList, info.colInfo)){
                            delNum += 1;
                            String record = "";
                            for (int j = 0; j < info.colInfo.size(); j++) {
                                if(j != 0) record += ",";
                                record += table.valueLines[i][j].toString();
                            }
                            Utils.Write2table(record, info,true);
                        }
                        else continue;
                    }
                    Mes = "共删除了 " + (table.valueLines.length - delNum) + " 条记录\n";
                    break;
                } else {
                    Mes = "Error: 数据表 " + Name +" 不存在\n";
                }
            }
        }
        return new SqlResult(Mes, null);
    }

    public static boolean isError(String sql) {
        // 识别关键字delete from
        String regex = "delete from (.*)";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(sql);
        if(matcher.find())
            if(!matcher.group().equals(sql)) return true;
        return false;
    }
}