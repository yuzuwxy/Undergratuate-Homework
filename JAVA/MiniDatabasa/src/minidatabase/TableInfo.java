/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:TableInfo
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-26  17:06
 */
package minidatabase;

import java.io.Serializable;
import java.util.ArrayList;

public class TableInfo implements Serializable {
    String Name = "";
    ArrayList<String[]> colInfo = new ArrayList<>();

    public TableInfo() {}

    public TableInfo(String name, ArrayList<String[]> colInfo) {
        Name = name;
        this.colInfo = colInfo;
    }
}