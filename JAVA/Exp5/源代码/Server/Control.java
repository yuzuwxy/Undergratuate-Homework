/**
 * @BelongsProject: Exp5_final
 * @BelongsPackage: Server
 * @ClassName:Control
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-22  10:32
 */
package Server;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Map;
import java.util.Scanner;

public class Control extends Thread{
    static String Mes = "请输入指令, end--结束程序; count-- 聊天者数量; chatters--列出所有聊天者; kickout + 空格 + 昵称--踢出聊天室";

    @Override
    public void run() {
        System.out.println(Mes);
        try {
            while(true) {
                Scanner scanner = new Scanner(System.in);
                String str = scanner.nextLine().trim();
//                System.out.println(str);
                if(str.contains("end")) {
                    System.out.println("聊天已终止, 断开与所有客户端的连接\n");
                    for (Map.Entry<String, Socket> entry : Server.userMap.entrySet()){
                        Socket sc = entry.getValue();
                        OutputStream outputStream = sc.getOutputStream();
                        DataOutputStream dout = new DataOutputStream(outputStream);
                        dout.writeUTF("服务器断开");
                    }
                    Server.userMap.clear();
                    System.exit(0);
                }
                else if(str.contains("count")){
                    System.out.println("共有 "+Server.userMap.size()+" 位聊天者\n");
                }
                else if(str.contains("chatters")) {
                    String res = "聊天者名单: ";
                    for (Map.Entry<String, Socket> entry : Server.userMap.entrySet()){
                        System.out.println(entry.getKey());
                    }
                }
                else{
                    String[] res = str.split(" ");
                    String name = res[1];
                    for (Map.Entry<String, Socket> entry : Server.userMap.entrySet()) {
                        Socket sc = entry.getValue();
                        OutputStream outputStream = sc.getOutputStream();
                        DataOutputStream dout = new DataOutputStream(outputStream);
                        SimpleDateFormat sf = new SimpleDateFormat("hh:mm:ss");
                        dout.writeUTF("[" + sf.format(new Date()) + "]" + name+" 被踢出聊天室\n");
                    }
                    System.out.println("用户" + name + "被踢出聊天室");
                    Server.userMap.remove(name);
                }
            }
        } catch (
        IOException e) {
            e.printStackTrace();
        }
    }
}