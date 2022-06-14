/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Create
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-26  20:29
 */
package minidatabase;

import java.io.File;
import java.io.IOException;
import java.util.Locale;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Create {
    public static SqlResult create(String sql) {
        // 解析SQL语句创建数据表
        String Mes = "Error: 语句错误\n";
        String tableName = "";
        File table;

        boolean bool = isError(sql.toLowerCase());           // 判断输入sql语句是否含有语法错误
        if(bool) {          // 没有较明显的语法错误
            int index = sql.indexOf("(");
            tableName = sql.substring(13, index).trim();
//            System.out.println(table.getAbsolutePath());
            Mes = "创建数据表 " + tableName + " 成功!\n";
            table = new File(TableManager.PATH, tableName+".midb");     // 在目标目录创建数据表文件
            if(!table.exists()) {
                // 提取字段信息，写入ti文件中
                TableInfo info = new TableInfo();
                info.Name = tableName;
                Pattern pattern = Pattern.compile("\\(.*\\)");
                Matcher matcher = pattern.matcher(sql);
                String s = "";
                if(matcher.find())
                    s = matcher.group(0);       // 提取两个括号之间的内容
                // 分别提取每个字段的内容
                s = s.substring(1, s.length() - 1);
                String[] field = s.split(",");
                for(String tmp : field){
                    tmp = tmp.trim();
                    if (tmp.contains("varchar")) {
                        tmp = tmp.replace("(", " ");
                        tmp = tmp.replace(")", "");
                    } else {
                        tmp += " " + "1";
                    }
//                    System.out.print(tmp);
                    String[] strings = tmp.split(" ");
                    for (int i = 0; i < 3; i++)
                        strings[i] = strings[i].trim();
//                    strings[2] += "\n";
                    strings[1] = strings[1].toLowerCase();
                    info.colInfo.add(strings);
                }
//                    System.out.println(col[0] + col[1]);
                // 结构信息写入TableInfo.ti文件中
                TableManager.tableInfo.add(info);
                Utils.Write2Ti();

                try {
                    table.createNewFile();
                } catch (IOException e) {
                    return new SqlResult("Error: 数据表文件创建失败！", null);
                }

            }
            else {
                Mes = "该表已存在！\n";
            }
        }
        return new SqlResult(Mes, null);
    }

    public static boolean isError(String sql) {
        boolean bool;                                   // 是否含有关键词table
        bool = sql.contains("table");
        if(!bool) return bool;
        bool = Utils.bracketMatch(sql);                 // 是否括号匹配
        if(bool) {
            int index = sql.indexOf("(");
            String Name = sql.substring(13, index);
            if(Name.trim().length() <= 0) bool = false; // 是否输入数据表名
        }
        return bool;
    }
}