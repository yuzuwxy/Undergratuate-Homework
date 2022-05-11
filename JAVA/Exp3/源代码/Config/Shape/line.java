package Config.Shape;

import java.awt.*;

public class line extends PublicSetting{
    private Color color = Color.BLACK;
    private int wid = 1;
    private String point = "0,0";
    private String slope = "inf";

    public line(){};

    @Override
    public void setColor(String col) {
        if(!col.equals("")) {
            super.setColor(col);
            color = super.color;
//            System.out.println(111);
        }
        else{
            color = Color.black;
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

    public String getSlope() {
        return slope;
    }
    public void setSlope(String slope) {
        this.slope = slope;
    }

    public void setPoint(String point) {
        this.point = point;
    }
    public String getPoint() {
        return point;
    }
}