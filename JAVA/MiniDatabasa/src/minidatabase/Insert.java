/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Insert
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-27  17:11
 */
package minidatabase;

import javax.lang.model.element.Name;
import java.io.*;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Insert {
    public static SqlResult insert(String sql) {
        boolean bool = isError(sql.toLowerCase());
        String Mes = "Error: 语句错误\n";
        if(!bool) {             // 没有明显的语法错误
            int idx = sql.indexOf("(");
            String Name = sql.substring(12, idx - 7);       // 数据表名为前后固定的关键字
            Name = Name.trim();
            String Data = "";
            // 获取括号中的数据
            Pattern pattern = Pattern.compile("\\(.*?\\)");
            Matcher matcher = pattern.matcher(sql);
            if(matcher.find())
                Data = matcher.group();
            Data = Data.substring(1, Data.length() - 1);

            // 判断是否有该表
            Iterator<TableInfo> it = TableManager.tableInfo.iterator();
            while(it.hasNext()) {
                TableInfo tmp = it.next();
                if(tmp.Name.equals(Name)) {
                    // 将记录写入
                    Mes = Utils.Write2table(Data, tmp,true);
                    break;
                } else {
                    Mes = "数据表 " + Name + " 不存在\n";
                }
            }
        }
        return new SqlResult(Mes, null);
    }

    public static boolean isError(String sql) {
        // 关键字insert into 和 values
        String regex = "insert into (.*)";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(sql);
        if(matcher.find()) {
//            System.out.println(matcher.group());
            if (!matcher.group().equals(sql)) return true;
        }
        else return true;
        regex = "values\\(.*\\);";
        pattern = Pattern.compile(regex);
        matcher = pattern.matcher(sql);
//        System.out.println(matcher.group(1));
        if(!matcher.find()) return true;
        // 括号匹配
        if(!Utils.bracketMatch(sql)) return true;

        return false;
    }

}