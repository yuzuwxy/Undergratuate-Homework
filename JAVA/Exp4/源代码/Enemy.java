import java.awt.*;

/**
 * @BelongsProject: Exp4
 * @BelongsPackage: PACKAGE_NAME
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-3  12:07
 */

public class Enemy {
    private int x, y;
    private int speed;

    public Enemy(int x, int y, int speed) {
        this.x = x;
        this.y = y;
        this.speed = speed;
    }

    public boolean placejudge() {
        if(x + speed>0&&x + speed<800) return true;
        else return false;
    }
    // 实现导弹的移动
    public void move() {
        x += speed;
    }

    public void setSpeed(int speed) {
        this.speed = speed;
    }
    public int getSpeed() {
        return speed;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getY() {
        return y;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getX() {
        return x;
    }
    // 用于判断敌方导弹和我方拦截导弹是否相撞
    public Rectangle getRect() {
        return new Rectangle(x, y, 30, 30);
    }
}