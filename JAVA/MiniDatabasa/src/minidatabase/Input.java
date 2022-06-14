/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Input
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-26  20:15
 */
package minidatabase;

import java.util.Scanner;

public class Input {
    public static String get() {
        Scanner scanner = new Scanner(System.in);
        String input = "";
        do {
            System.out.print(">>");
            input += " " + scanner.nextLine();
            input = input.replaceAll("(\\s+|\r|\n|\t)$", "");   // 防止分号后有多个空格无法结束
            input = input.trim();
//            System.out.println(input);
        } while (!input.endsWith(";"));                     // 完整语句以分号结束
        String sql = Format.sqlFormat(input);
        return sql;
    }
}