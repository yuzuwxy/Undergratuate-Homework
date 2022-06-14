/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:SqlAnalysis
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-26  17:31
 */
package minidatabase;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class SqlAnalysis {
    public static String analysis(String sql) {
        String start = "";
        String regex = "^[a-zA-Z]+";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(sql);

        while(matcher.find()) {
            start = matcher.group();
        }
        start = start.toLowerCase();
        return start;
    }
}