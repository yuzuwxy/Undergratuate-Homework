/**
 * @BelongsProject: Exp5_final
 * @BelongsPackage: Server
 * @ClassName:Inspection
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-22  10:32
 */
package Server;

import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Map;

public class Inspection extends Thread{
    @Override
    public void run() {
        while (true) {
            for (Map.Entry<String, Socket> entry : Server.userMap.entrySet()) {
                Socket st = entry.getValue();
                if (st.isClosed())
                    Server.userMap.remove(entry.getKey());
            }
            try {
                sleep(60);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}