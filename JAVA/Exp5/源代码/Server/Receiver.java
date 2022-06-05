/**
 * @BelongsProject: Exp5_final
 * @BelongsPackage: Server
 * @ClassName:Receiver
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-22  10:32
 */
package Server;

import java.awt.*;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.IOException;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Map;

import static java.lang.Thread.sleep;

public class Receiver implements Runnable{
    Socket s = null;
    String name = "";

    public Receiver(Socket s, String name) {
        this.s = s;
        this.name = name;
        new Thread(this).start();
    }

    @Override
    public void run() {
        try {
            while (true) {
                DataInputStream dis = new DataInputStream(this.s.getInputStream());
                String mes = dis.readUTF();
                if(!Server.userMap.containsKey(name)) continue;
                if (mes.trim().length() != 0) {
                    SimpleDateFormat sf = new SimpleDateFormat("hh:mm:ss");
                    String mes1 = "[" + sf.format(new Date()) + "]" + name + ": " + mes;
                    if(mes.equals("----bye----")) {
                        mes1 = "[" + sf.format(new Date()) + "]" + "用户 " + name + " 下线了";
                        Server.userMap.remove(name);
                        for (Map.Entry<String, Socket> entry : Server.userMap.entrySet()) {
                            Socket st = entry.getValue();
                            DataOutputStream dops = new DataOutputStream(st.getOutputStream());//数据输出流
                            dops.writeUTF(mes1 + "\n");
                        }
                        return;
                    }
                    for (Map.Entry<String, Socket> entry : Server.userMap.entrySet()) {
                        Socket st = entry.getValue();
                        if(!st.isClosed())
                            new Sender(st, mes1);
                    }
                }
                try {
                    sleep(60);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        } catch (IOException ignored) {
        }
    }
}