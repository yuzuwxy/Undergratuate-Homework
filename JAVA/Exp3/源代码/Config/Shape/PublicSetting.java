package Config.Shape;

import java.awt.*;

public class PublicSetting {
    protected Color color = Color.white;

    public void setColor(String col) {
        int ret = col.indexOf(",");
        if(ret == -1) {         // 用颜色名确定颜色
            if(col.equals("black"))  color = Color.BLACK;
            if(col.equals("white"))  color = Color.white;
            if(col.equals("red"))    color = Color.RED;
            if(col.equals("green"))  color = Color.GREEN;
            if(col.equals("gray"))   color = Color.GRAY;
            if(col.equals("cyan"))   color = Color.CYAN;
            if(col.equals("pink"))   color = Color.PINK;
            if(col.equals("orange")) color = Color.orange;
            if(col.equals("yellow")) color = Color.YELLOW;
            if(col.equals("blue"))   color = Color.blue;
        }
        else {                 // RGB信息确定颜色
            String[] colorRGB = col.split(",");
            color = new Color(Integer.parseInt(colorRGB[0]),Integer.parseInt(colorRGB[1]),Integer.parseInt(colorRGB[2]));
        }
    }

    public Color getColor() {
        return color;
    }
}
