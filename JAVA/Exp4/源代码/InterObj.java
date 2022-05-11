import java.awt.*;

/**
 * @BelongsProject: Exp4
 * @BelongsPackage: PACKAGE_NAME
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-3  12:07
 */

public class InterObj {
    private int x = 400, y = 600;
    private int speed = 12;

    public InterObj() {}

    public InterObj(int x, int y, int speed) {
        this.x = x;
        this.y = y;
        this.speed = speed;
    }

    public boolean overBound(){
        if(x > RedFlag.WIDTH || x < 0) return false;
        else return true;
    }

    public void move() {
        y -= speed;
    }

    public void setSpeed(int speed) {
        this.speed = speed;
    }
    public int getSpeed() {
        return speed;
    }

    public Rectangle getRect() {
        return new Rectangle(x, y, 20, 20);
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
}