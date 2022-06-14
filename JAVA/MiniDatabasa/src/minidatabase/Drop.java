/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Drop
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-27  16:32
 */
package minidatabase;

import java.io.File;
import java.util.Iterator;
import java.util.Locale;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Drop {
    public static SqlResult drop(String sql){
        String Mes = "Error: 错误命令\n";
        boolean bool = isError(sql.toLowerCase());
        if(!bool) {
            String Name = sql.substring(11, sql.length()-1);
            // 判断是否存在
            Iterator<TableInfo> it = TableManager.tableInfo.iterator();
            while(it.hasNext()) {
                TableInfo cntTable = it.next();
                if(cntTable.Name.equals(Name)){
                    TableManager.tableInfo.remove(cntTable);
                    File tableFile = new File(TableManager.PATH, Name+".midb");
                    boolean value = tableFile.delete();
                    if(!value) Mes = "Error: 数据表不存在\n";
                    else Mes = "数据表 " + Name + " 已删除\n";
                    Utils.Write2Ti();
                    break;
                } else {
                    Mes = "Error: 数据表 " + Name + " 不存在\n";
                }
            }
        }
        return new SqlResult(Mes, null);
    }

    public static boolean isError(String sql) {
        String regex = "drop table (.*)";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(sql);
        String s = "";
        if(matcher.find())
            s = matcher.group();
        if(s.equals(sql)) return  false;
        else return true;
    }
}