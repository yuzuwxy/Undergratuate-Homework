/**
 * @BelongsProject: Exp5_final
 * @BelongsPackage: Client
 * @ClassName:Receiver
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-22  10:32
 */
package Client;

import java.io.DataInputStream;
import java.io.EOFException;
import java.io.IOException;
import java.net.Socket;
import java.net.SocketException;

import static java.lang.Thread.sleep;

public class Receiver implements Runnable{
    Socket s = null;

    public Receiver(Socket s) {
        this.s = s;
        new Thread(this).start();
    }
    @Override
    public void run() {
        try {
            while(true) {
                DataInputStream dis = new DataInputStream(s.getInputStream());
                String revMes = dis.readUTF();
                System.out.println(revMes);
                Client.Showta.append(revMes);

                try {
                    sleep(60);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        } catch (EOFException | SocketException ignored) {
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}