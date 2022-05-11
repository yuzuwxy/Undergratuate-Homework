import java.awt.*;
import java.util.ArrayList;

/**
 * @BelongsProject: Exp4
 * @BelongsPackage: PACKAGE_NAME
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-4  13:09
 */

public class ThreadClass extends Thread{
    ArrayList<Enemy> enemys = new ArrayList<>();
    ArrayList<InterObj> interobjs = new ArrayList<>();
    Graphics g;
    int speed;
    int score;

    public ThreadClass(ArrayList<Enemy> enemy, ArrayList<InterObj> inteobjs, int speed, Graphics g) {
        this.g = g;
        this.speed = speed;
        this.enemys = enemy;
        this.interobjs = inteobjs;
    }

    public int getScore() {
        return score;
    }

    public void run() {
        while(true) {
            g.setColor(Color.WHITE);
            g.fillRect(0,0, 800, 600);
            System.out.println(enemys.size());
            for (int i = 0; i < enemys.size(); i++) {
                Enemy tmp = enemys.get(i);
                if(tmp.placejudge()) {
                    g.setColor(Color.BLUE);
                    g.fillOval(tmp.getX(), tmp.getY(), 30,30);
                    enemys.get(i).move();
                    System.out.println(enemys.get(i).getX());
                }else{
                    enemys.remove(i);
                    EnemyThread enemyThread = new EnemyThread(enemys, speed);
                    enemyThread.run();
                }
            }

//            System.out.println(interobjs.size());
            for (int i = 0; i < interobjs.size(); i++) {
                InterObj tmp = interobjs.get(i);
                if(!tmp.overBound()){
                    g.setColor(Color.RED);
                    g.fillOval(tmp.getX(), tmp.getY(), 20, 20);
                    interobjs.get(i).move();
                }else{
                    interobjs.remove(i);
                    InterObjThread interThread = new InterObjThread(interobjs, speed);
                    interThread.run();
                }
            }

            try {
                Thread.sleep(25);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

            for (int i = 0; i < interobjs.size(); i++) {
                InterObj tmpInter = interobjs.get(i);
                for (int i1 = 0; i1 < enemys.size(); i1++) {
                    Enemy tmpenemy = enemys.get(i1);
                    if(tmpenemy.getRect().intersects(tmpInter.getRect())) {
                        score ++;
                        enemys.remove(i1);
                        interobjs.remove(i);
                        break;
                    }
                }
            }


            try {
                Thread.sleep(30);
            }catch (Exception ef) {}
        }
    }
}