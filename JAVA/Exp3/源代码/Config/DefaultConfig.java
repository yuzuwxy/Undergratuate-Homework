package Config;

public class DefaultConfig {
    public static String Message =
            "<!--\n" +
            "【1】配置文件用xml格式，注释采用标准的xml注释格式。\n" +
            "【2】有8类设定：\n" +
            "（1）<bg>：用于设定画布的背景颜色及横向和纵向坐标范围；\n" +
            "（2）<points>：用于画一个或多个点，可以对点的颜色和填充等进行配置；\n" +
            "（3）<lines>：用于画折线，可以对折线的颜色和粗细进行配置：\n" +
            "（4）<line>：根据提供的单个点和斜率，画射线；\n" +
            "（5）<curve>：用于画曲线，画出采用公式描述的曲线；\n" +
            "（6）<shape>：用于画矩形和椭圆，能够对填充颜色进行配置；\n" +
            "（7）<xScale>：用于画x轴刻度；\n" +
            "（8）<yScale>：用于画y轴刻度。\n" +
            "【3】与颜色相关的标签中，均可以采用两种方式之一设定：\n" +
            "（1）用名称颜色，名称颜色共10种：\n" +
            "black, blue, cyan, gray, green, \n" +
            "orange, pink, red, white, yellow\n" +
            "（2）用RGB颜色，例如：\n" +
            "255.0.155\n" +
            "【4】其它设定包括：\n" +
            "（1）所有与线的粗细有关的设定都默认为1；\n" +
            "（2）所有与颜色相关的设定的默认值都为黑色（0,0,0)；背景为白色；\n" +
            "（3）画曲线时，默认离散点的数量为500；\n" +
            "（4）画刻度时，默认间隔数量<amount>为10.\n" +
            "【5】以下为各种设置示例：\n" +
            "-->\n" +
            "\n" +
            "<bg>\n" +
            "<col> 255,255,255 </col>\n" +
            "<xRange> -0.1, 1.1 </xRange>\n" +
            "<yRange> -0.1, 1.1 </yRange>\n" +
            "</bg>\n" +
            "\n" +
            "<points>\n" +
            "<pad> true </pad>\n" +
            "<col> red </col>\n" +
            "<wid> 2 </wid>\n" +
            "<radius> 6 </radius>\n" +
            "<list>\n" +
            "0.2, 0.2\n" +
            "0.2, 0.5\n" +
            "0.2, 0.8\n" +
            "0.5, 0.8\n" +
            "0.8, 0.8\n" +
            "0.8, 0.5\n" +
            "0.8, 0.2\n" +
            "0.5, 0.2\n" +
            "</list>\n" +
            "</points>\n" +
            "\n" +
            "<lines>\n" +
            "<col> orange </col>\n" +
            "<wid> 3 </wid>\n" +
            "<list>\n" +
            "0.2, 0.2\n" +
            "0.2, 0.5\n" +
            "0.2, 0.8\n" +
            "0.5, 0.8\n" +
            "0.8, 0.8\n" +
            "0.8, 0.5\n" +
            "0.8, 0.2\n" +
            "0.5, 0.2\n" +
            "0.5, 0.5\n" +
            "</list>\n" +
            "</lines>\n" +
            "\n" +
            "<line>\n" +
            "<col>  </col>\n" +
            "<wid> 1 </wid>\n" +
            "<point> 0.3, 0.3 </point>\n" +
            "<slope> inf </slope>\n" +
            "</line>\n" +
            "\n" +
            "<curve>\n" +
            "<col> 0,0,255 </col>\n" +
            "<wid> 3 </wid>\n" +
            "<range> 0, 1 </range>\n" +
            "<amount> 500 </amount>\n" +
            "<function> Math.pow(x,2)-0.05 </function>\n" +
            "</curve>\n" +
            "\n" +
            "<shape>\n" +
            "<col> 180,180,180 </col>\n" +
            "<wid> 1 </wid>\n" +
            "<type> oval </type>\n" +
            "<!-- type includes oval & rect -->\n" +
            "<pad> true </pad>\n" +
            "<center> 0.6, 0.8 </center>\n" +
            "<width> 0.3 </width>\n" +
            "<height> 0.2 </height>\n" +
            "</shape>\n" +
            "\n" +
            "<shape>\n" +
            "<col> 180,180,180 </col>\n" +
            "<wid> 5 </wid>\n" +
            "<type> rect </type>\n" +
            "<!-- type includes oval & rect -->\n" +
            "<pad> false </pad>\n" +
            "<center> 0.3, 0.4 </center>\n" +
            "<width> 0.3 </width>\n" +
            "<height> 0.2 </height>\n" +
            "</shape>\n" +
            "\n" +
            "<scale>\n" +
            "<col> black </col>\n" +
            "<wid> 1 </wid>\n" +
            "<direction> x </direction>\n" +
            "<pos> 0 </pos>\n" +
            "<from> 0 </from>\n" +
            "<step> 0.1 </step>\n" +
            "<amount> 10 </amount>\n" +
            "<precision> 1 </precision>\n" +
            "</scale>\n" +
            "\n" +
            "<scale>\n" +
            "<col> black </col>\n" +
            "<wid> 1 </wid>\n" +
            "<direction> y </direction>\n" +
            "<pos> 0 </pos>\n" +
            "<from> 0 </from>\n" +
            "<step> 0.1 </step>\n" +
            "<amount> 10 </amount>\n" +
            "<precision> 1 </precision>\n" +
            "</scale>\n";
}
