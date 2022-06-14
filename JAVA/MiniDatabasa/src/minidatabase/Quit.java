/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Quit
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-26  20:27
 */
package minidatabase;

public class Quit {
    public static SqlResult quit() {
        Utils.Write2Ti();
        TableManager.Running = false;
        return new SqlResult("Bye", null);
    }
}