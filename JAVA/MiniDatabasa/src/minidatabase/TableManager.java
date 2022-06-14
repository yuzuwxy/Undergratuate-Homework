/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: PACKAGE_NAME
 * @ClassName:TableManager
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-26  17:04
 */

package minidatabase;

import java.util.HashSet;

public class TableManager {
    static HashSet<TableInfo> tableInfo = new HashSet<>();                  // 存储数据表结构信息（读取ti文件获得）
    static boolean Running = true;                                          // 数据库管理系统正在运行的标志，避免永真循环

    static String PATH = "D:\\";                                            // 数据表存储的位置，读取配置文件获得
    static int Len = 100;                                                   // 数据表中的int类型和decimal类型存储的字节长度

    // 支持的sql语句类型
    private static final String help = "help";
    private static final String quit = "quit";
    private static final String show = "show";
    private static final String desc = "desc";
    private static final String create = "create";
    private static final String drop = "drop";
    private static final String select = "select";
    private static final String insert = "insert";
    private static final String delete = "delete";
    private static final String update = "update";

    public static SqlResult operate(String sql){
        String start = SqlAnalysis.analysis(sql);           // 分析输入的语句，提取第一个单词
        SqlResult result = new SqlResult();                 // 操作结果对象
        switch (start) {                                    // 根据首单词进行对应的操作
            case help:
                result = Help.help();
                break;
            case quit:
                result = Quit.quit();
                break;
            case show:
                result = Show.show(sql);
                break;
            case desc:
                result = Desc.desc(sql);
                break;
            case drop:
                result = Drop.drop(sql);
                break;
            case insert:
                result = Insert.insert(sql);
                break;
            case select:
                result = Select.select(sql);
                break;
            case delete:
                result = Delete.delete(sql);
                break;
            case update:
                result = Update.update(sql);
                break;
            case create:
                result = Create.create(sql);
                break;
            default:
                result = new SqlResult("Error: 未识别命令。您可以输入help语句查看可用命令\n", null);
        }
        return result;
    }

    public static void main(String[] args) {
        PATH = Utils.readProperties();                  // 读取配置文件
        Utils.readTi();                                 // 读取存储数据表结构信息的ti文件
        while(Running) {
            String sql = Input.get();                   // 与命令行交互
            SqlResult result = operate(sql);            // 调用API
            System.out.println(result.toString());      // 输出结果
        }
    }
}