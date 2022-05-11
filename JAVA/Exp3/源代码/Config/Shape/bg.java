package Config.Shape;

public class bg extends PublicSetting{
    private String xRange = "0,10";
    private String yRange = "0,10";

    public bg(){};

    public void setxRange(String xRange) {
        this.xRange = xRange;
    }

    public void setyRange(String yRange) {
        this.yRange = yRange;
    }

    public String getxRange() {
        return xRange;
    }
    public String getyRange() {
        return yRange;
    }
}

