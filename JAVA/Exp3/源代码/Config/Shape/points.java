package Config.Shape;

import java.awt.*;

public class points extends PublicSetting{
    private boolean pad = true;
    private Color color = Color.BLACK;
    private int wid = 1;
    private int radius = 1;
    private String[] list = {""};
    private int len = list.length;

    public points(){};

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

    public boolean isPad() {
        return pad;
    }
    public void setPad(boolean pad) {
        this.pad = pad;
    }

    public int getWid() {
        return wid;
    }
    public void setWid(int wid) {
        this.wid = wid;
    }

    public int getRadius() {
        return radius;
    }
    public void setRadius(int radius) {
        this.radius = radius;
    }

    public String[] getList() {
        return list;
    }

    public void setList(String[] list) {
        this.list = list;
        len = list.length;
    }
    public void addPoint(double x, double y){
        list[len] = x + "," + y;
        len = list.length;
    }
    public void addPoint(String point) {
        list[len] = point;
        len = list.length;
    }
}