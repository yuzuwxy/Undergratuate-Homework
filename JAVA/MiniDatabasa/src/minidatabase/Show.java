/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Show
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-27  10:37
 */
package minidatabase;

import java.io.EOFException;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.Iterator;
import java.util.Locale;

public class Show {
    public static SqlResult show(String sql) {
        boolean bool = isError(sql);        // 判断输入语句是否有明显的语法错误
        String Mes = "数据表\n";
        if(bool) Mes = "Error: 语句错误\n";
        else {
            int Num = TableManager.tableInfo.size();
            Iterator<TableInfo> it = TableManager.tableInfo.iterator();
            while (it.hasNext())
                Mes += it.next().Name + "\n";
            Mes += "共有 " + Num + " 个数据表\n";
        }
        return new SqlResult(Mes, null);
    }

    public static boolean isError(String sql) {
        sql = sql.toLowerCase().substring(0,sql.length() - 1).trim();
//        sql = sql.replaceAll("\r|\n|\t", "");
//        System.out.println(sql);
        if(sql.equals("show tables")) return false;
        return true;
    }
}