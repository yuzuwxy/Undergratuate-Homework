/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:SqlResult
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-26  19:45
 */
package minidatabase;

import java.util.Arrays;

public class SqlResult {
    String sqlFeedBack = "Query ok\n";
    Object[][] valueLines = null;

    public SqlResult() { }
    public SqlResult(String sqlFeedBack, Object[][] valueLines) {
        this.sqlFeedBack = sqlFeedBack;
        this.valueLines = valueLines;
    }

    @Override
    public String toString() {
        String str = "";
        if(valueLines != null)
            for (int i = 0; i < valueLines.length; i++) {
                for(int j = 0; j<valueLines[i].length;j++) {
                    if(j != 0) str += ", ";
                    str += valueLines[i][j];
                }
                if(!str.endsWith("\n"))
                    str += "\n";
            }
        str += sqlFeedBack;
        return str;
    }
}