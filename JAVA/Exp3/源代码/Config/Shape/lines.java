package Config.Shape;

import java.awt.*;

public class lines extends PublicSetting{
    private Color color = Color.BLACK;
    private int wid = 1;

    private String[] list = {""};
    private int len = list.length;

    public lines(){};

    @Override
    public Color getColor() {
        return color;
    }
    @Override
    public void setColor(String col) {
        if(!col.equals("")) {
            super.setColor(col);
            color = super.color;
        }
    }

    public int getWid() {
        return wid;
    }
    public void setWid(int wid) {
        this.wid = wid;
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