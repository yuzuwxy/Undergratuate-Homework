/**
 * @BelongsProject: Exp5_final
 * @BelongsPackage: Server
 * @ClassName:Server
 * @Author: yuzuwxy
 * @CreateTime: 2022-06-04  00:29
 */
package Server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Server {
    static ServerSocket ss = null;      // 服务器端口
    static final int PORT = 8888;       // 端口号设置为常量
    static Map<String, Socket> userMap = new HashMap<>();

    public Server() {
        try {
            Server.ss = new ServerSocket(Server.PORT);
        } catch (IOException e2) {
            throw new RuntimeException(e2);
        }
        new Inspection().start();           // 巡检
        new Control().start();              // 接收键盘信息控制服务器端
        new Anteroom().start();             // 启动服务器端，与客户端信息交换
    }

    public static void main(String[] args) {
        new Server();
    }
}