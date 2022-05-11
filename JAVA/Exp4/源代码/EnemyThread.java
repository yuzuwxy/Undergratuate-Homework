import java.util.ArrayList;
import java.util.Random;

/**
 * @BelongsProject: Exp4
 * @BelongsPackage: PACKAGE_NAME
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-3  13:26
 */

public class EnemyThread {
    ArrayList<Enemy> enemys = new ArrayList<>();
    int speed = 0;

    public EnemyThread(ArrayList<Enemy> enemys, int speed) {
        this.enemys = enemys;
        this.speed = speed;
    }

    public void run() {
        Random random = new Random();
        while(enemys.size() < 15) {
            int x = -random.nextInt(100);
            int y = random.nextInt(500);
            Enemy enemy = new Enemy(x, y, speed);
            enemys.add(enemy);

            x = random.nextInt(800, 1000);
            y = random.nextInt(500);
            Enemy enemy2 = new Enemy(x, y, -speed);
            enemys.add(enemy2);
        }
    }
}