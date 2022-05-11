/**
 * @BelongsProject: Exp4
 * @BelongsPackage: PACKAGE_NAME
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-1  11:31
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.TimerTask;
import java.util.Timer;

public class RedFlag extends JFrame{

    JFrame frame = new JFrame("红旗-9");
    JPanel gamePanel = new JPanel();
    Graphics g;
    JLabel timeLabel = new JLabel("计时(秒): ");
    JLabel countLabel = new JLabel("计数(次): ");
    JTextField time = new JTextField();
    JTextField count = new JTextField();
    JButton Start = new JButton("开始");
    JButton Stop = new JButton("停止");
    JButton speedUp = new JButton("加速");
    JButton speedDown = new JButton("减速");
    JButton Intercept = new JButton("拦截");

    boolean thcflag = false;
    boolean intflag = false;

    ArrayList<Enemy> enemys = new ArrayList<Enemy>();
    ArrayList<InterObj> interObjs = new ArrayList<InterObj>();
    int interNum = 0;
    // 实现计时功能
    Timer timer = new Timer();
    timetask timeTask = new timetask();

    int speed = 2;
    EnemyThread enemyThread = new EnemyThread(enemys, speed);
    InterObjThread interThread = new InterObjThread(interObjs, speed + 2);
    ThreadClass thc;            // Thread子类，实现多线程

    int state = 0;          // 0 未开始，1开始，2暂停

    final static int Width = 800;
    final static int Height = 600;

    public RedFlag() {
        frame.setLocation(200, 100);
        frame.setSize(Width, Height);
        Box box = new Box(BoxLayout.X_AXIS);
        box.add(timeLabel);
        box.add(Box.createHorizontalStrut(5));
        box.add(time);
        time.setEditable(false);
        box.add(Box.createHorizontalStrut(5));
        box.add(Start);
        Start.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                state = 1;
                interNum = 0;
                Start.setEnabled(false);
                Stop.setEnabled(true);
                enemyThread.run();
                if(thcflag) {
                    thc.resume();
                    thcflag = false;
                }
            }
        });
        box.add(Box.createHorizontalStrut(5));
        box.add(speedUp);
        speedUp.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(enemys.size() != 0) {
                    if(speed < 8) {
                        speed *= 2;
                        for (int i = 0; i < enemys.size(); i++)
                            if(enemys.get(i).getSpeed() > 0)
                                enemys.get(i).setSpeed(speed);
                            else enemys.get(i).setSpeed(-speed);
//                        for (int i = 0; i < interObjs.size(); i++)
//                            interObjs.get(i).setSpeed(speed + 2);

                        enemyThread.speed = speed;
                        thc.speed = speed;
                    }
//                    System.out.println(speed);
                    if(speed >= 8)
                        speedUp.setEnabled(false);
                    if(speed >= 1)
                        speedDown.setEnabled(true);
                }
            }
        });
        box.add(Box.createHorizontalStrut(5));
        Intercept.setPreferredSize(new Dimension(150, Intercept.getWidth()));
        box.add(Intercept);
        Intercept.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int score = 0;
                interNum++;
                if(interNum >=10) Intercept.setEnabled(false);
                if(interObjs.size() < 100) {
//                if(interNum >= 10) {
                    if(intflag) {
                        Intercept.setEnabled(false);
                        intflag = false;
                    }
                    interThread.run();
                }
                else{
//                    interNum ++;
//                    interThread.run();
                    Intercept.setEnabled(false);
                    intflag = true;
                }
                score = thc.getScore();
                count.setText("" + score);
            }
        });
        box.add(Box.createHorizontalStrut(5));
        box.add(speedDown);
        speedDown.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(enemys.size() > 0) {
                    if(speed > 1) {
                        for (int i = 0; i < enemys.size(); i++)
                            enemys.get(i).setSpeed(enemys.get(i).getSpeed() / 2);
                        speed /= 2;
                        enemyThread.speed = speed;
                        thc.speed = speed;
                    }
                    if(speed <= 1)
                        speedDown.setEnabled(false);
                    if(speed <8)
                        speedUp.setEnabled(true);
                }
            }
        });
        box.add(Box.createHorizontalStrut(5));
        box.add(Stop);
        Stop.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                state = 0;
                Start.setEnabled(true);
                Stop.setEnabled(false);
                thc.score = 0;
                count.setText("0");
                interNum = 0;
                Intercept.setEnabled(true);
                thc.suspend();
                thcflag = true;

            }
        });
        box.add(Box.createHorizontalStrut(5));
        box.add(countLabel);
        box.add(Box.createHorizontalStrut(5));
        box.add(count);
        count.setEditable(false);
        box.add(Box.createHorizontalStrut(5));

        frame.add(box, BorderLayout.SOUTH);
        frame.add(gamePanel);

        frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
        frame.setVisible(true);

        g = gamePanel.getGraphics();
        thc = new ThreadClass(enemys, interObjs, speed, g);
        thc.start();
        timer.scheduleAtFixedRate(timeTask, 0, 800);
    }

    class timetask extends TimerTask {
        int cntTime = 0;
        @Override
        public void run() {
            if(state == 1) {
                if(!thcflag) {
                    cntTime ++;
                    time.setText("" + cntTime);
                }
            }
        }
    }

    public static void main(String[] args) {
        new RedFlag();
    }

}