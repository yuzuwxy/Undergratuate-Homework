import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

import Config.DefaultConfig;
import Config.ConfigSoup;
import Config.Shape.*;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;

public class ConfigurableDrawing {
    //	窗口中的主要部件
    private JFrame frame = new JFrame("可配置绘图软件");
    final int HEIGHT = 700;
    final int WIDTH = 1000;
    private JTextArea textarea = new JTextArea();
    private MyCanvas canvas = new MyCanvas();
    private JButton config = new JButton("配置");
    private JButton draw = new JButton("绘图");

    protected ConfigSoup soup;          // 图形配置信息

    boolean drawing = false;

    /**
     * 组装界面
     */
    public void init() {
        frame.setSize(WIDTH, HEIGHT);
        frame.setLocation(200, 100);
        // 分割面板
        JSplitPane sp = new JSplitPane();
        sp.setContinuousLayout(true);
        sp.setDividerLocation(700);
        sp.setDividerSize(7);
        sp.setLeftComponent(canvas);
        sp.setVisible(true);

        Box ConfigArea = new Box(BoxLayout.Y_AXIS);
        JPanel btnPanel = new JPanel();
        btnPanel.setMaximumSize(new Dimension(300, 80));
        btnPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
        config.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                textarea.setText(DefaultConfig.Message);
            }
        });
        draw.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                soup = new ConfigSoup(textarea.getText());
                drawing = true;
                canvas.setBackground(soup.getBgConfig().getColor());
                canvas.repaint();
//                drawing = false;
            }
        });
        btnPanel.add(draw);
        btnPanel.add(config);
        ConfigArea.add(btnPanel);

        JScrollPane scrollPane = new JScrollPane(textarea);
        textarea.setEditable(true);
        textarea.setLineWrap(true);
        ConfigArea.add(scrollPane);

        sp.setRightComponent(ConfigArea);

        frame.add(sp);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }

    /**
     * 自定义内部类，继承Canvas类，重写paint方法完成绘图
     */
    class MyCanvas extends Canvas{
//        @Override
        public void update(Graphics g) {
            if(drawing == true) {
                // 绘制x轴
                Graphics2D g2d = (Graphics2D)g;
                g2d.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING,RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
                g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
                double xstart = soup.getXscaleConfig().getFrom();
                double xstep = soup.getXscaleConfig().getStep();
//                System.out.println(soup.getXscaleConfig().getStep());
                double xamount = soup.getXscaleConfig().getAmount();
                int base = 50;       // ”坐标原点“在画布中的实际位置
                int xactgap = (canvas.getWidth() - 2*base) / ((int) xamount);        // 坐标轴单位长度的实际长度
                g2d.setStroke(new BasicStroke(soup.getXscaleConfig().getWid()));
                g2d.drawLine(50, canvas.getHeight()-base,
                        canvas.getWidth() - base, canvas.getHeight()-base);
                g2d.setFont(new Font("宋体", 0, 12));
                Integer prec = soup.getXscaleConfig().getPrecision();
                String sp = "%"+"."+prec.toString()+"f";
                for(int i = 0; i<=xamount; i ++) {
                    g2d.drawString(String.format(sp,(xstart+i*xstep)), 50+i*xactgap-5, canvas.getHeight()-base+12);
                    g2d.drawLine(50+i*xactgap, canvas.getHeight()-base, 50+i*xactgap, canvas.getHeight()-base-3);
//                    System.out.println(50+i*xactgap);
                }

                // 绘制y轴
                double ystart = soup.getYscaleConfig().getFrom();
                double ystep = soup.getYscaleConfig().getStep();
                double yamount = soup.getYscaleConfig().getAmount();
//                System.out.println(yamount);
                int yactgap = xactgap;       // 坐标轴单位长度的实际长度
                g2d.setStroke(new BasicStroke(soup.getYscaleConfig().getWid()));
                g2d.drawLine(50, canvas.getHeight()-base,
                        50, (int)(canvas.getHeight()- 50 - yactgap * yamount - 3));
                g2d.setFont(new Font("宋体", 0, 10));
                prec = soup.getYscaleConfig().getPrecision();
                sp = "%"+"."+prec.toString()+"f";
                for(int i = 0; i<=yamount; i ++) {
                    g2d.drawString(String.format(sp,(ystart+i*ystep)), 30, canvas.getHeight()-base-(i*yactgap));
                    g2d.drawLine(50, canvas.getHeight()-base-(i*yactgap), 53, canvas.getHeight()-base-i*yactgap);
                }

                // 绘制点
                for(int i = 0;i< soup.getPointsNum();i++) {
//                    System.out.println(soup.getPointsNum());
                    int wid = soup.getPointsConfig().get(i).getWid();
                    int radius = soup.getPointsConfig().get(i).getRadius();
                    g.setColor(soup.getPointsConfig().get(i).getColor());
//                    System.out.println(soup.getPointsConfig().get(i).getColor());
                    String[] pointList = soup.getPointsConfig().get(i).getList();
                    int pointNum = pointList.length;
//                    System.out.println(pointNum);
                    for(int j = 0;j<pointNum;j++) {
                        double x = Double.parseDouble(pointList[j].split(",")[0]);
                        double y = Double.parseDouble(pointList[j].split(",")[1]);
//                        System.out.println(x);
                        x = (50+(x/xstep)*xactgap)-radius/2;
//                        System.out.println(x);
                        y = (canvas.getHeight()-base-((y/ystep)*yactgap))-radius/2;
                        g.fillOval((int)x, (int)y, radius, radius);
                    }
                }

                // 绘制折线
                for(int i = 0;i< soup.getLinesNum();i++) {
//                    System.out.println(soup.getLinesNum());
                    int wid = soup.getLinesConfig().get(i).getWid();
//                    System.out.println(wid);
                    g2d.setColor(soup.getLinesConfig().get(i).getColor());
                    g2d.setStroke(new BasicStroke(wid));
//                    System.out.println(soup.getPointsConfig().get(i).getColor());
                    String[] nodeList = soup.getLinesConfig().get(i).getList();
                    int nodeNum = nodeList.length;
//                    System.out.println(nodeNum);
                    for(int j = 1;j<nodeNum;j++) {
                        double x1 = Double.parseDouble(nodeList[j-1].split(",")[0]);
                        double y1 = Double.parseDouble(nodeList[j-1].split(",")[1]);
                        double x2 = Double.parseDouble(nodeList[j].split(",")[0]);
                        double y2 = Double.parseDouble(nodeList[j].split(",")[1]);
//                        System.out.println(x1);
                        x1 = (50+(x1/xstep)*xactgap);
                        y1 = (canvas.getHeight()-base-((y1/ystep)*yactgap));
                        x2 = (50+(x2/xstep)*xactgap);
                        y2 = (canvas.getHeight()-base-((y2/ystep)*yactgap));
                        g2d.drawLine((int)x1, (int)y1, (int)x2, (int)y2);
                    }
                }

                // 根据斜率和点绘制射线
                for(int i=0;i<soup.getLineNum();i++) {
                    g2d.setStroke(new BasicStroke(soup.getLineConfig().get(i).getWid()));
                    g2d.setColor(soup.getLineConfig().get(i).getColor());
                    line tmpLine = soup.getLineConfig().get(i);
//                    System.out.println(Color.BLACK);
//                    System.out.println(tmpLine.getColor());
                    double x = Double.parseDouble(tmpLine.getPoint().split(",")[0]);
                    double y = Double.parseDouble(tmpLine.getPoint().split(",")[1]);

                    if(tmpLine.getSlope().equals("inf")){
                        x = (50+(x/xstep)*xactgap);
                        y = (canvas.getHeight()-base-((y/ystep)*yactgap));
                        g2d.drawLine((int)x, canvas.getHeight(), (int)x, 0);
                    }
                    else{
                        double k = Double.parseDouble(tmpLine.getSlope());
                        double x1 = x - xamount*xstep;
                        double x2 = x + xamount*xstep;
                        double y1 = y - yamount * ystep * k;
                        double y2 = y + yamount * ystep * k;
//                        System.out.println(x1+" "+y1+" "+x2+" "+y2);
                        x1 = (50+(x1/xstep)*xactgap);
                        x2 = (50+(x2/xstep)*xactgap);
                        y1 = (canvas.getHeight()-base-((y1/ystep)*yactgap));
                        y2 = (canvas.getHeight()-base-((y2/ystep)*yactgap));
                        g2d.drawLine((int)x2, (int)y2, (int)x1, (int)y1);
                    }

                }

                // 绘制曲线
                for(int i=0;i<soup.getCurveNum();i++) {
                    curve cntCurve = soup.getCurveConfig().get(i);
                    g2d.setColor(cntCurve.getColor());
                    g2d.setStroke(new BasicStroke(cntCurve.getWid()));
                    int amount = cntCurve.getAmount();
                    double s = Double.parseDouble(cntCurve.getRange().split(",")[0]);
                    double e = Double.parseDouble(cntCurve.getRange().split(",")[1]);
                    String function = cntCurve.getFunction();

                    double step = ((e - s) / amount);
                    for(double j = s; j <= e; j += step) {
                        ScriptEngineManager manager = new ScriptEngineManager();
                        ScriptEngine engine = manager.getEngineByName("js");
                        String newFunction = function.replace("x", Double.toString(j));
                        try{
                            Double curveY = (Double)engine.eval(newFunction);
                            int actx = (int)(50+(j/xstep)*xactgap);
                            int acty = (int)(canvas.getHeight()-base-((curveY/ystep)*yactgap));
                            g2d.fillOval(actx, acty, 3,3);
                        } catch (ScriptException ex) {
                            throw new RuntimeException(ex);
                        }
                    }
                }

                // 绘制形状
                for(int i=0;i<soup.getShapeNum();i++) {
                    shape cntShape = soup.getShapeConfig().get(i);
                    g2d.setColor(cntShape.getColor());
                    g2d.setStroke(new BasicStroke(cntShape.getWid()));

                    double x = Double.parseDouble(cntShape.getCenter().split(",")[0]);
                    double y = Double.parseDouble(cntShape.getCenter().split(",")[1]);
                    double width = cntShape.getWidth();
                    double height = cntShape.getHeight();

                    x = x - width/2;
                    y = y + height/2;
//                    System.out.println(width +" "+height);

                    x = (50+(x/xstep)*xactgap);
                    y = (canvas.getHeight()-base-((y/ystep)*yactgap));
                    width = (width/xstep)*xactgap;
                    height = ((height/ystep)*yactgap);
                    boolean pad = cntShape.isPad();

                    if(cntShape.getType().equals("oval")){
                        if(pad)
                            g2d.fillOval((int)x, (int)y, (int)width, (int)height);
                        else
                            g2d.drawOval((int)x, (int)y, (int)width, (int)height);
                    }
                    if(cntShape.getType().equals("rect")){
                        if(pad)
                            g2d.fillRect((int)x, (int)y, (int)width, (int)height);
                        else
                            g2d.drawRect((int)x, (int)y, (int)width, (int)height);
                    }
                }
            }
        }

    }

    //	主程序
    public static void main(String[] args)  {
        new ConfigurableDrawing().init();
    }
}
