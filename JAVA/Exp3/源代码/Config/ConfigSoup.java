package Config;
import java.util.LinkedList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import Config.Shape.*;

public class ConfigSoup {
    private String configInfo;

    private bg bgConfig = new bg();

    private scale xscaleConfig = new scale();
    private scale yscaleConfig = new scale();

    private List<points> pointsConfig = new LinkedList<>();
    private int pointsNum = 0;

    private List<lines> linesConfig = new LinkedList<>();
    private int linesNum = 0;

    private List<line> lineConfig = new LinkedList<>();
    private int lineNum = 0;

    private List<curve> curveConfig = new LinkedList<>();
    private int curveNum = 0;

    private List<shape> shapeConfig = new LinkedList<>();
    private int shapeNum = 0;

    public ConfigSoup(){};
    public ConfigSoup(String Info) {
        configInfo = new String(Info);
        Analysis(Info);
    }

    /**
     * 分离不同图形的配置信息
     * @param Info
     */
    public void Analysis(String Info) {
        // 删去空格
        Pattern p = Pattern.compile(" +");
        Matcher m = p.matcher(Info);
        Info = m.replaceAll("");
        // 删去注释
        p = Pattern.compile("(<!--.*?-->)", Pattern.DOTALL);
        m = p.matcher(Info);
        Info = m.replaceAll("");
//        System.out.println(Info);

        // 匹配背景设置
        p = Pattern.compile("(<bg>.*?</bg>)", Pattern.DOTALL);
        m = p.matcher((Info));
        if(m.find()){
            String bgInfo = Info.substring(m.start(), m.end());
            bgAnalysis(bgInfo);
        }

        // 匹配坐标轴
        p = Pattern.compile("(<scale>.*?</scale>)", Pattern.DOTALL);
        m = p.matcher(Info);
        while(m.find()) {
            String scaleInfo = Info.substring(m.start(), m.end());
//            System.out.println(scaleInfo);
            scaleAnalysis(scaleInfo);
        }

        // 匹配点
        p = Pattern.compile(("<points>.*?</points>"), Pattern.DOTALL);
        m = p.matcher(Info);
        while(m.find()) {
            String pointsInfo = Info.substring(m.start(), m.end());
            pointsAnalysis(pointsInfo);
            pointsNum+=1;
        }

        // 匹配折线
        p = Pattern.compile(("<lines>.*?</lines>"), Pattern.DOTALL);
        m = p.matcher(Info);
        while(m.find()) {
            String linesInfo = Info.substring(m.start(), m.end());
            linesAnalysis(linesInfo);
            linesNum += 1;
        }

        // 匹配射线
        p = Pattern.compile(("<line>.*?</line>"), Pattern.DOTALL);
        m = p.matcher(Info);
        while(m.find()) {
            String lineInfo = Info.substring(m.start(), m.end());
            lineAnalysis(lineInfo);
            lineNum +=1;
        }

        // 匹配曲线
        p = Pattern.compile(("<curve>.*?</curve>"), Pattern.DOTALL);
        m = p.matcher(Info);
        while(m.find()) {
            String curveInfo = Info.substring(m.start(), m.end());
            curveAnalysis(curveInfo);
            curveNum +=1;
        }

        // 匹配形状（椭圆或矩形）
        p = Pattern.compile(("<shape>.*?</shape>"), Pattern.DOTALL);
        m = p.matcher(Info);
        while(m.find()) {
            String shapeInfo = Info.substring(m.start(), m.end());
            shapeAnalysis(shapeInfo);
            shapeNum +=1;
        }
    }

    /**
     * 解析背景配置
     * @param bgInfo
     */
    public void bgAnalysis(String bgInfo){
        Pattern p = Pattern.compile("<col>(.*?)</col>");
        Matcher m = p.matcher(bgInfo);
        if(m.find())
            bgConfig.setColor(m.group(1));

        p = Pattern.compile("<xRange>(.*?)</xRange>");
        m = p.matcher(bgInfo);
        if(m.find())
            bgConfig.setxRange(m.group(1));

        p = Pattern.compile("<yRange>(.*?)</yRange>");
        m = p.matcher(bgInfo);
        if(m.find())
            bgConfig.setyRange(m.group(1));
    }

    /**
     * 截取对x轴和y轴的配置
     * @param scaleInfo
     */
    public void scaleAnalysis(String scaleInfo) {
        Pattern p = Pattern.compile("<direction>(.)</direction>");
        Matcher m = p.matcher(scaleInfo);
        if(m.find()) {
//            System.out.println(m.group(1));
            if(m.group(1).equals("x")) {
                xscaleConfig = setScale(scaleInfo);
//                System.out.println(xscaleConfig.getStep());
            }
            else if(m.group(1).equals("y"))
                yscaleConfig = setScale(scaleInfo);
        }
    }

    /**
     * 配置坐标轴
     * @param scaleInfo
     * @return
     */
    public scale setScale(String scaleInfo) {
//        System.out.println(scaleInfo);
        Pattern p = Pattern.compile("<col>(.*?)</col>");
        Matcher m = p.matcher(scaleInfo);
        scale scaleConfig = new scale();
        if(m.find())
            scaleConfig.setColor(m.group(1));

        p = Pattern.compile("<wid>(.*?)</wid>");
        m = p.matcher(scaleInfo);
        if(m.find())
            scaleConfig.setWid(Integer.parseInt(m.group(1)));

        p = Pattern.compile("<pos>(.*?)</pos>");
        m = p.matcher(scaleInfo);
        if(m.find())
            scaleConfig.setPos(Integer.parseInt(m.group(1)));

        p = Pattern.compile("<from>(.*?)</from>");
        m = p.matcher(scaleInfo);
        if(m.find())
            scaleConfig.setFrom(Double.parseDouble(m.group(1)));

        p = Pattern.compile("<step>(\\d*\\.\\d*)</step>");
        m = p.matcher(scaleInfo);
        if(m.find()) {
            scaleConfig.setStep(Double.parseDouble(m.group(1)));
//            System.out.println(scaleConfig.getStep());
        }

        p = Pattern.compile("<amount>(.*?)</amount>");
        m = p.matcher(scaleInfo);
        if(m.find())
            scaleConfig.setAmount(Integer.parseInt(m.group(1)));

        p = Pattern.compile("<precision>(.*?)</precision>");
        m = p.matcher(scaleInfo);
        if(m.find())
            scaleConfig.setPrecision(Integer.parseInt(m.group(1)));
        return scaleConfig;
    }

    /**
     * 解析点配置信息
     * @return
     */
    public void pointsAnalysis(String pointsInfo) {
        int cnt = pointsNum;
        Pattern p = Pattern.compile("<col>(.*?)</col>");
        Matcher m = p.matcher(pointsInfo);
        points tmp = new points();
        if(m.find()) {
//            System.out.println(m.group(1));
            tmp.setColor(m.group(1));
        }

        p = Pattern.compile("<pad>(.*?)</pad>");
        m = p.matcher(pointsInfo);
        if(m.find())
            tmp.setPad(Boolean.parseBoolean(m.group(1)));

        p = Pattern.compile("<wid>(.*?)</wid>");
        m = p.matcher(pointsInfo);
        if(m.find())
            tmp.setWid(Integer.parseInt(m.group(1)));

        p = Pattern.compile("<radius>(.*?)</radius>");
        m = p.matcher(pointsInfo);
        if(m.find())
            tmp.setRadius(Integer.parseInt(m.group(1)));

        p = Pattern.compile("<list>\n*(.*?)\n*</list>",Pattern.DOTALL);
        m = p.matcher(pointsInfo);
//        System.out.println(m.find());
        if(m.find())
            tmp.setList(m.group(1).split("\n"));
//            System.out.println(m.group(1).split("\n")[0]);

        pointsConfig.add(tmp);
    }

    /**
     * 解析折线配置信息
     * @param linesInfo
     */
    public void linesAnalysis(String linesInfo) {
        int cnt = linesNum;
        Pattern p = Pattern.compile("<col>(.*?)</col>");
        Matcher m = p.matcher(linesInfo);
        lines tmp = new lines();
        if(m.find()) {
//            System.out.println(m.group(1));
            tmp.setColor(m.group(1));
        }

        p = Pattern.compile("<wid>(.*?)</wid>");
        m = p.matcher(linesInfo);
        if(m.find())
            tmp.setWid(Integer.parseInt(m.group(1)));

        p = Pattern.compile("<list>\n*(.*?)\n*</list>",Pattern.DOTALL);
        m = p.matcher(linesInfo);
//        System.out.println(m.find());
        if(m.find()) {
            tmp.setList(m.group(1).split("\n"));
//            System.out.println(m.group(1).split("\n")[0]);
        }
        linesConfig.add(tmp);
    }

    /**
     * 解析射线配置信息
     * @param lineInfo
     */
    public void lineAnalysis(String lineInfo) {
        int cnt = lineNum;
        Pattern p = Pattern.compile("<col>(.*?)</col>");
        Matcher m = p.matcher(lineInfo);
        line tmp = new line();
        if(m.find()) {
//            System.out.println(m.group(1));
            tmp.setColor(m.group(1));
        }

        p = Pattern.compile("<wid>(.*?)</wid>");
        m = p.matcher(lineInfo);
        if(m.find())
            tmp.setWid(Integer.parseInt(m.group(1)));

        p = Pattern.compile("<slope>(.*?)</slope>");
        m = p.matcher(lineInfo);
        if(m.find()) {
            tmp.setSlope(m.group(1));
//            System.out.println(m.group());
        }

        p = Pattern.compile("<point>(.*?)</point>");
        m = p.matcher(lineInfo);
        if(m.find())
            tmp.setPoint(m.group(1));

        lineConfig.add(tmp);
    }

    /**
     * 解析曲线信息
     * @return
     */
    public void curveAnalysis(String curveInfo) {
        int cnt = curveNum;
        Pattern p = Pattern.compile("<col>(.*?)</col>");
        Matcher m = p.matcher(curveInfo);
        curve tmp = new curve();
        if(m.find()) {
//            System.out.println(m.group(1));
            tmp.setColor(m.group(1));
        }

        p = Pattern.compile("<wid>(.*?)</wid>");
        m = p.matcher(curveInfo);
        if(m.find())
            tmp.setWid(Integer.parseInt(m.group(1)));

        p = Pattern.compile("<range>(.*?)</range>");
        m = p.matcher(curveInfo);
        if(m.find())
            tmp.setRange(m.group(1));

        p = Pattern.compile("<amount>(.*?)</amount>");
        m = p.matcher(curveInfo);
        if(m.find())
            tmp.setAmount(Integer.parseInt(m.group(1)));

        p = Pattern.compile("<function>(.*?)</function>");
        m = p.matcher(curveInfo);
        if(m.find())
            tmp.setFunction(m.group(1));

        curveConfig.add(tmp);
    }

    /**
     * 解析椭圆或矩形信息
     * @return
     */
    public void shapeAnalysis(String shapeInfo) {
        int cnt = shapeNum;
        Pattern p = Pattern.compile("<col>(.*?)</col>");
        Matcher m = p.matcher(shapeInfo);
        shape tmp = new shape();
        if(m.find()) {
//            System.out.println(m.group(1));
            tmp.setColor(m.group(1));
        }

        p = Pattern.compile("<wid>(.*?)</wid>");
        m = p.matcher(shapeInfo);
        if(m.find())
            tmp.setWid(Integer.parseInt(m.group(1)));

        p = Pattern.compile("<type>(.*?)</type>");
        m = p.matcher(shapeInfo);
        if(m.find())
            tmp.setType(m.group(1));

        p = Pattern.compile("<pad>(.*?)</pad>");
        m = p.matcher(shapeInfo);
        if(m.find())
            tmp.setPad(Boolean.parseBoolean(m.group(1)));

        p = Pattern.compile("<center>(.*?)</center>");
        m = p.matcher(shapeInfo);
        if(m.find())
            tmp.setCenter(m.group(1));

        p = Pattern.compile("<width>(.*?)</width>");
        m = p.matcher(shapeInfo);
        if(m.find())
            tmp.setWidth(Double.parseDouble(m.group(1)));

        p = Pattern.compile("<height>(.*?)</height>");
        m = p.matcher(shapeInfo);
        if(m.find())
            tmp.setHeight(Double.parseDouble(m.group(1)));

        shapeConfig.add(tmp);
    }

    public bg getBgConfig() {
        return bgConfig;
    }

    public scale getXscaleConfig() {
        return xscaleConfig;
    }
    public scale getYscaleConfig() {
        return yscaleConfig;
    }

    public int getPointsNum() {
        return pointsNum;
    }
    public List<points> getPointsConfig() {
        return pointsConfig;
    }

    public int getLinesNum() {
        return linesNum;
    }
    public List<lines> getLinesConfig() {
        return linesConfig;
    }

    public int getLineNum() {
        return lineNum;
    }
    public List<line> getLineConfig() {
        return lineConfig;
    }

    public int getCurveNum() {
        return curveNum;
    }
    public List<curve> getCurveConfig() {
        return curveConfig;
    }

    public int getShapeNum() {
        return shapeNum;
    }
    public List<shape> getShapeConfig() {
        return shapeConfig;
    }
}
