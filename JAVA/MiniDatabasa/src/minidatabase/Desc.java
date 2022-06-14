/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Desc
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-27  12:15
 */
package minidatabase;

import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * 显示数据表的表结构
 */
public class Desc {
    public static SqlResult desc(String sql) {
        boolean bool = isError(sql.toLowerCase());        // 是否有明显的语法错误
        String Mes = "Error: 错误命令\n";
        String[][] tableinfo = null;
        if(!bool) {
            String Name = sql.substring(11, sql.length()-1).trim();
            // 判断表是否存在
            Iterator<TableInfo> it = TableManager.tableInfo.iterator();
            while(it.hasNext()){
                TableInfo tmp = it.next();
                if(tmp.Name.equals(Name)) {
                    tableinfo = new String[tmp.colInfo.size() + 1][3];
                    String Header = "列名称, " + "列类型, " + "列宽度\n";
                    tableinfo[0] = Header.split(", ");
                    int idx = 1;
                    for(int i=0;i<tmp.colInfo.size();i++) {
                        tableinfo[idx] = tmp.colInfo.get(i);
//                        tableinfo[idx][2] += "\n";
                        idx += 1;
                    }
                    Mes = "Query ok\n";
                    break;
                } else{
                    Mes = "Error: 数据表 " + Name + " 不存在\n";
                }
            }
        }
        return new SqlResult(Mes, tableinfo);
    }

    public static boolean isError(String sql) {
        String regex = "desc table (.*)";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(sql);
        String s = "";
        if(matcher.find())
            s = matcher.group();
//        System.out.println(sql);
        if(s.equals(sql)) return false;
        else return true;
    }
}