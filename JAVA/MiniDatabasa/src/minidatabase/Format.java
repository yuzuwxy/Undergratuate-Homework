/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Format
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-26  17:18
 */
package minidatabase;

public class Format {
    public static String sqlFormat(String input){
        String sql = "";
        sql = input.trim();         // 去掉首尾空格
        sql = sql.replaceAll("\\s{2,}", " ");   // 将多个空格转化为一个空格
        return sql;
    }
}