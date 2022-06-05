/**
 * @BelongsProject: Exp5_final
 * @BelongsPackage: Client
 * @ClassName:Client
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-22  10:32
 */
package Client;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.IOException;
import java.net.Socket;
import java.net.SocketException;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

public class Client extends JFrame{
    static JLabel IPLabel = new JLabel("IP:");
    static JLabel PortLabel = new JLabel("端口:");
    static JLabel NameLabel = new JLabel("昵称:");
    static JTextField IPtf = new JTextField("127.0.0.1", 7);
    static JTextField Porttf = new JTextField("8888", 7);
    static JTextField Nametf = new JTextField(7);
    static JButton inBtn = new JButton("进入聊天室");
    static JButton outBtn = new JButton("退出聊天室");
    static JTextArea Showta = new JTextArea(10, 10);
    static JTextArea Inputta = new JTextArea(4, 30);
    static JButton okBtn = new JButton("发送");

    private Socket s = null;
    private String ConStr = "127.0.0.1";
    private int ConPort = 8888;
    private DataOutputStream dos = null;
    private String Name = "";

    public void init() {
        this.setTitle("全民大讨论聊天室客户端");
        this.setBounds(300, 300, 600, 400);
        JPanel northPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 5, 10));
        northPanel.add(IPLabel);
        northPanel.add(IPtf);
        northPanel.add(PortLabel);
        northPanel.add(Porttf);
        northPanel.add(NameLabel);
        northPanel.add(Nametf);
        northPanel.add(inBtn);
        northPanel.add(outBtn);
        outBtn.setEnabled(false);
        this.add(northPanel, BorderLayout.NORTH);

        Box box1 = new Box(BoxLayout.Y_AXIS);
        Box box2 = new Box(BoxLayout.X_AXIS);
        box2.add(new JScrollPane(Inputta));
        Inputta.setLineWrap(true);
        box2.add(Box.createHorizontalStrut(2));
        box2.add(okBtn);
        okBtn.setEnabled(false);
        box1.add(new JScrollPane(Showta));
        Showta.setLineWrap(true);
        Showta.setEditable(false);
        box1.add(Box.createVerticalStrut(3));
        box1.add(box2);
        this.add(box1);

        // 点击“进入聊天室”按钮
        inBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 1、与服务器连接
                try {
                    ConStr = IPtf.getText();
                    ConPort = Integer.parseInt(Porttf.getText());
                    s = new Socket(ConStr, ConPort);
                } catch (IOException e2) {
                    Showta.setText("服务器连接失败\n");
                }

                // 2.修改按钮和文本框状态
                IPtf.setEditable(false);
                Porttf.setEditable(false);
                Nametf.setEditable(false);
                inBtn.setEnabled(false);
                outBtn.setEnabled(true);
                okBtn.setEnabled(true);

                // 3. 开始接收服务器端的消息
                new Receiver(s);

                // 4. 客户端向服务器端发送昵称
                Name = Nametf.getText();
                new Sender(s, Name);
            }
        });
        okBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String strSend = Inputta.getText();      // 要发送到服务器上
                if(strSend.trim().length() == 0) return;
                new Sender(s, strSend);
//                System.out.println(strSend);
                Inputta.setText("");
            }
        });
        outBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 1. 改变组件状态
                IPtf.setEditable(true);
                Porttf.setEditable(true);
                Nametf.setEditable(true);
                inBtn.setEnabled(true);
                outBtn.setEnabled(false);
                okBtn.setEnabled(false);
                // 2. 退出
                try {
                    DataOutputStream dout = new DataOutputStream(s.getOutputStream());
                    dout.writeUTF("----bye----");//将用户名传入客户端
                    s.close();
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
            }
        });

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
    }

    public static void main(String[] args) {
        new Client().init();
    }
}