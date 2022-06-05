/**
 * @BelongsProject: Exp5_final
 * @BelongsPackage: Client
 * @ClassName:Sender
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-22  10:32
 */
package Client;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.SocketException;

public class Sender implements Runnable{
    Socket s = null;
    String mes = "";

    public Sender(Socket s, String mes) {
        this.s = s;
        this.mes = mes;
        new Thread(this).start();
    }
    @Override
    public void run() {
        try {
            DataOutputStream dout = new DataOutputStream(s.getOutputStream());
            dout.writeUTF(mes);
        } catch (SocketException ignored){
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}