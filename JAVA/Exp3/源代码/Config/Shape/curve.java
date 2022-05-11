package Config.Shape;

import java.awt.*;

public class curve extends PublicSetting{
    private Color color = Color.black;
    private int wid = 1;
    private String range = "";
    private int amount = 10;
    private String function = "";

    public curve() {};

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

    public void setWid(int wid) {
        this.wid = wid;
    }
    public int getWid() {
        return wid;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }
    public int getAmount() {
        return amount;
    }

    public String getRange() {
        return range;
    }
    public void setRange(String range) {
        this.range = range;
    }

    public String getFunction() {
        return function;
    }
    public void setFunction(String function) {
        this.function = function;
    }
}