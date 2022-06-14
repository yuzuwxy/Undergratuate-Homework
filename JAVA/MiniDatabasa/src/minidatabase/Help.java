/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Help
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-26  19:21
 */
package minidatabase;

public class Help {
    private static final String Mes = "" +
            "quit; ---- 退出迷你数据库系统\n" +
            "help; ---- 显示所有可用指令\n" +
            "show tables; -- 显示目前所有数据表\n" +
            "desc table XXX -- 显示数据表XXX的表结构\n" +
            "create table XXX(columnA varchar(10), columnB int, columnC decimal) ---- 创建一个3列的名称为XXX的数据表, " +
            "列名称分别为columnA, columnB, columnC, 其类型分别为10位以内的字符, 整型数, 小数\n" +
            "drop table XXX ---- 删除表格XXX\n" +
            "select colX, colY, colZ from XXX where colZ > 1.5 order by colZ desc ---- " +
            "从数据表XXX中选取3列，colX, colY, colZ, 每一个记录必须满足colZ的值大于1.5, 且显示时按照colZ这一列降序排序\n" +
            "select * from XXX where colA <> '北林信息' ---- 从数据表XXX中选取所有的列, 但要记录满足列colA不是'北林信息'\n" +
            "insert into XXX value('北林信息', 15, 25.5) ---- 向数据表XXX中追加一条记录, 各个列的值分别为'北林信息', 15, 25.5\n" +
            "delete from XXX where colB = 10 ---- 把表格XXX中colB的值是10的记录全部删除\n" +
            "update XXX set colD = '计算机科学与技术' where colA = '北林信息' ---- " +
            "在数据表XXX中把colA的值为'北林信息'的记录中colD列全部改写为'计算机科学与技术'\n";

    public static SqlResult help() {
        return new SqlResult(Mes, null);
    }
}