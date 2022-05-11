package Config.Shape;

import java.awt.*;

public class scale extends PublicSetting{
    private Color color = Color.BLACK;
    private int wid = 1;                // 线宽吗
    private String direction = "x";     // 坐标轴方向
    private int pos = 0;           // 这个不知道是啥
    private double from = 0;            // 坐标原点啊
    private double step = 1;            // 步长
    private int amount = 10;         // 间隔数量
    private int precision = 1;       // 精度吗，就是保留几位小数

    public scale() {};

    @Override
    public void setColor(String col) {
        if(!col.equals("")) {
            super.setColor(col);
            color = super.color;
        }
    }
    @Override
    public Color getColor() {
        return color;
    }

    public int getWid() {
        return wid;
    }
    public void setWid(int wid) {
        this.wid = wid;
    }

    public String getDirection() {
        return direction;
    }
    public void setDirection(String direction) {
        this.direction = direction;
    }

    public int getPos(){
        return pos;
    }
    public void setPos(int pos) {
        this.pos = pos;
    }

    public double getFrom() {
        return from;
    }
    public void setFrom(double from) {
        this.from = from;
    }

    public double getStep() {
        return step;
    }
    public void setStep(double step) {
        this.step = step;
    }

    public int getAmount() {
        return amount;
    }
    public void setAmount(int amount) {
        this.amount = amount;
    }

    public int getPrecision() {
        return precision;
    }
    public void setPrecision(int precision) {
        this.precision = precision;
    }

    public double range() {
        return (double)amount * step;
    }
}
