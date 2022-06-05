/**
 * @BelongsProject: Exp5_final
 * @BelongsPackage: Server
 * @ClassName:Sender
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-22  10:32
 */
package Server;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class Sender implements Runnable {
    Socket s;
    String mes;

    public Sender(Socket s, String mes) {
        this.s = s;
        this.mes = mes;
        new Thread(this).start();
    }

    @Override
    public void run() {
        try {
            DataOutputStream dops = new DataOutputStream(s.getOutputStream());//数据输出流
            dops.writeUTF(mes + "\n");
//            System.out.println(mes);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}