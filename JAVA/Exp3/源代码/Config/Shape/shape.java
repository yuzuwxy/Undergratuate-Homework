package Config.Shape;

import java.awt.*;

public class shape extends PublicSetting{
    private Color color = Color.BLACK;
    private int wid = 1;
    private static String OVAL = "oval";
    private static String RECT = "rect";
    private String type = "oval";
    private boolean pad = true;
    private String center = "0,0";
    private double width = 0;
    private double height = 0;

    public shape() {};

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

    public void setPad(boolean pad) {
        this.pad = pad;
    }
    public boolean isPad() {
        return pad;
    }

    public String getType() {
        return type;
    }
    public void setType(String type) {
        this.type = type;
    }

    public String getCenter() {
        return center;
    }
    public void setCenter(String center) {
        this.center = center;
    }

    public double getHeight() {
        return height;
    }
    public void setHeight(double height) {
        this.height = height;
    }

    public double getWidth() {
        return width;
    }
    public void setWidth(double width) {
        this.width = width;
    }
}