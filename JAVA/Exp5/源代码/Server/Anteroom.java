/**
 * @BelongsProject: Exp5_final
 * @BelongsPackage: Server
 * @ClassName:Anteroom
 * @Author: yuzuwxy
 * @CreateTime: 2022-06-04  00:32
 */
package Server;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Map;

public class Anteroom extends Thread{
    static Socket s = null;

    @Override
    public void run() {
        try {
            while(true){
                try{
                    s = Server.ss.accept();
                } catch (SocketException e) { }

                try {
                    sleep(60);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                // 判断昵称重复
                DataInputStream dis = new DataInputStream(s.getInputStream());
                String user = dis.readUTF();         // 是一个阻塞性方法
                if(Server.userMap.containsKey(user)) {
                    new Sender(s, "昵称重复");
                    continue;
                }

                Server.userMap.put(user, s);
                SimpleDateFormat sf = new SimpleDateFormat("hh:mm:ss");
                String mes = "[" + sf.format(new Date()) + "] 欢迎 " + user + " 进入聊天室";
                for (Map.Entry<String, Socket> entry : Server.userMap.entrySet()) {
                    //System.out.println(entry.getKey()+entry.getValue());
                    Socket st = entry.getValue();
                    new Sender(st, mes);
                }
                new Receiver(s, user);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}