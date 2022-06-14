/**
 * @BelongsProject: MiniDatabasa
 * @BelongsPackage: minidatabase
 * @ClassName:Utils
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-26  22:18
 */
package minidatabase;

import java.io.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Properties;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Utils {
    // 检查语句是否格式正确：括号是否匹配
    public static boolean bracketMatch(String sql) {
        // 转化为char方便匹配
        char[] chars = sql.toCharArray();
        int stack = 0;
        for(int i=0;i<chars.length;i++) {
            if(chars[i] == '(')
                stack += 1;
            else if(chars[i] == ')') {
                if (stack <= 0) return false;
                else stack -= 1;
            }
        }
        return true;
    }

    // 检查字符串的引号匹配情况
    public static boolean quotesMatch(String str) {
        char[] chars = str.toCharArray();
        int stack = 0;
        for(int i=0;i<chars.length;i++) {
            if(chars[i] == '\'')
                stack += 1;
        }
        if(stack == 0 || stack % 2 != 0) return false;
        return true;
    }

    // 向ti文件中写入数据表结构信息
    public static void Write2Ti() {
        try {
            FileOutputStream fos = new FileOutputStream("./TableInfo.ti");
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(TableManager.tableInfo);
            oos.flush();
            oos.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    // 读取配置文件，获取数据表目录
    public static String readProperties() {
        Properties properties = new Properties();
        String dbHome = "";
        try {
            properties.load(new FileInputStream("./Config.properties"));
            dbHome = properties.getProperty("dbHome");
        } catch (IOException ioe) { }
        return dbHome;
    }

    // 读取ti文件，获取数据表结构信息
    public static void readTi() {
        try {
            FileInputStream fis = new FileInputStream("./TableInfo.ti");
            ObjectInputStream ois = new ObjectInputStream(fis);
            TableManager.tableInfo = (HashSet<TableInfo>) ois.readObject();
//            System.out.println(TableManager.tableInfo.size());
            ois.close();
        } catch (IOException | ClassNotFoundException e) {
            return;
        }
    }

    // 读取数据表
    public static SqlResult ReadTable(TableInfo info) {
        SqlResult table = new SqlResult();
        int recordNum = 0;
        String Mes = "共有 " + recordNum + " 条记录\n";

        try {
            File tableFile = new File(TableManager.PATH, info.Name + ".midb");
            RandomAccessFile raf = new RandomAccessFile(tableFile, "r");
            int colNum = info.colInfo.size();
            int rowSize = 0;                    // 计算每一行的字节数
            for(int i = 0; i<colNum; i ++) {
                if(info.colInfo.get(i)[1].equals("varchar"))
                    rowSize += Integer.parseInt(info.colInfo.get(i)[2].trim()) * 4;         // 实际长度
                else rowSize += TableManager.Len;
            }
            table.valueLines = new Object[(int)(tableFile.length() / rowSize)][colNum];
            for(long j = 0; j < tableFile.length(); j += rowSize) {
                for (int i = 0; i < colNum; i++)
                    if (info.colInfo.get(i)[1].equals("varchar")) {
                        int sLen = Integer.parseInt(info.colInfo.get(i)[2].trim()) * 4;
                        byte[] bytes = new byte[sLen];
                        raf.readFully(bytes);
                        String s = (new String(bytes));
                        String regex = "('.*')";                                    // 去掉补充的0
                        Pattern pattern = Pattern.compile(regex);
                        Matcher matcher = pattern.matcher(s);
                        if (matcher.find()) s = matcher.group();
                        table.valueLines[recordNum][i] = s;
                    } else {
                        byte[] bytes = new byte[TableManager.Len];
                        raf.readFully(bytes);
                        ByteArrayInputStream bais = new ByteArrayInputStream(bytes);
                        ObjectInputStream ois = new ObjectInputStream(bais);
                        table.valueLines[recordNum][i] = ois.readObject();
                    }
                recordNum += 1;
            }
        } catch (EOFException e) {
            Mes = "共有 " + recordNum + " 条记录\n";
        } catch (FileNotFoundException ex) {
        } catch (IOException e) {
            Mes = "共有 " + recordNum + " 条记录\n";
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
        return table;
    }

    // 判断条件, 某一条记录是否符合条件
    public static boolean isFit(Object[] row, String[] conList, ArrayList<String[]> colInfo) {
        boolean bool = true;
        for(int i = 0; i < conList.length; i ++) {      // 判断每一个条件
            String regex = "([a-zA-Z0-9_]+)([\s><=]*)(.*)";
            Pattern pattern = Pattern.compile(regex);
            Matcher matcher = pattern.matcher(conList[i]);
            String colName = "",op = "", value = "";
            if(matcher.find()) {
                colName = matcher.group(1).trim();
                op = matcher.group(2).trim();
                value = matcher.group(3).trim();
            }
            if(value.endsWith(";"))
                value = value.substring(0, value.length() - 1);
            String type = "";
            int colIdx = 0;
            for(int j = 0; j < colInfo.size(); j ++)
                if(colInfo.get(j)[0].equals(colName)) {
                    type = colInfo.get(j)[1];
                    colIdx = j;
                }
            if(type.equals("")) return true;

            if(op.equals(">")) {
                if(type.trim().equals("int"))
                    bool = (int)row[colIdx] > Integer.parseInt(value);
                else if(type.trim().equals("decimal"))
                    bool = Double.doubleToLongBits((double)row[colIdx]) > Double.doubleToLongBits(Double.parseDouble(value));
                else bool = ((String)row[colIdx]).compareTo(value) > 0;
            } else if(op.equals("<")) {
                if(type.trim().equals("int"))
                    bool = (int)row[colIdx] < Integer.parseInt(value);
                else if(type.trim().equals("decimal"))
                    bool = Double.doubleToLongBits((double)row[colIdx]) < Double.doubleToLongBits(Double.parseDouble(value));
                else bool = ((String)row[colIdx]).compareTo(value) < 0;
            }
            else if(op.equals("<=")) {
                if(type.trim().equals("int"))
                    bool = (int)row[colIdx] <= Integer.parseInt(value);
                else if(type.trim().equals("decimal"))
                    bool = Double.doubleToLongBits((double)row[colIdx]) <= Double.doubleToLongBits(Double.parseDouble(value));
                else bool = ((String)row[colIdx]).compareTo(value) <= 0;
            }
            else if(op.equals(">=")) {
                if(type.trim().equals("int"))
                    bool = (int)row[colIdx] >= Integer.parseInt(value);
                else if(type.trim().equals("decimal"))
                    bool = Double.doubleToLongBits((double)row[colIdx]) >= Double.doubleToLongBits(Double.parseDouble(value));
                else bool = ((String)row[colIdx]).compareTo(value) >= 0;
            }
            else if(op.equals("<>")) {
                if(type.trim().equals("int"))
                    bool = (int)row[colIdx] != Integer.parseInt(value);
                else if(type.trim().equals("decimal"))
                    bool = Double.doubleToLongBits((double)row[colIdx]) != Double.doubleToLongBits(Double.parseDouble(value));
                else bool = ((String)row[colIdx]).compareTo(value) != 0;
            }
            else if(op.equals("=")) {
                if(type.trim().equals("int"))
                    bool = (int)row[colIdx] == Integer.parseInt(value);
                else if(type.trim().equals("decimal"))
                    bool = Double.doubleToLongBits((double)row[colIdx]) == Double.doubleToLongBits(Double.parseDouble(value));
                else bool = ((String)row[colIdx]).compareTo(value) == 0;
            }
            if(!bool) return bool;
        }
        return bool;
    }

    public static  int colIn(TableInfo info, String colNum) {
        int idx = -1;
        for(int i=0;i<info.colInfo.size();i++)
            if(info.colInfo.get(i)[0].equals(colNum))
                idx = i;
        return idx;
    }

    public static int compare(Object[] a, Object[] b, int idx, String type, String req) {
        int res = 0;
        if(type.equals("int")) {
            int inta = (int) a[idx], intb = (int) b[idx];
            res = Integer.compare(inta, intb);
        } else if(type.equals("decimal")) {
            double doua = Double.doubleToLongBits((double) a[idx]), doub = Double.doubleToLongBits((double) b[idx]);
            res = Double.compare(doua, doub);
        } else if(type.equals("varchar")){
            res = ((String) a[idx]).compareTo((String) b[idx]);
        }
        if(req.equals("asc")) res = -res;
//        System.out.println(a[idx] + " " + b[idx] + " " + req + " " + res);
        return res;
    }

    public static String Write2table(String record, TableInfo tableInfo, boolean booll) {
        String Mes = "";
        int colNum = tableInfo.colInfo.size();
        // 需要写入的数据表文件
        String[] s = record.split(",");             // 这里认为字符串中间不含逗号
        // 判断是否符合对应列的数据类型
        if(s.length != tableInfo.colInfo.size())
            return "Error: 输入数据与数据表不符\n";
        for(int i = 0; i < tableInfo.colInfo.size(); i ++) {
            s[i] = s[i].trim();
            if(tableInfo.colInfo.get(i)[1].equals("int")) {
                try{int tmp = Integer.parseInt(s[i]);}
                catch (NumberFormatException e1) {return "Error: 您输入的第 " + (i + 1) + " 个值无法转化为int类型\n";}
            } else if(tableInfo.colInfo.get(i)[1].equals("decimal")) {
                try{double tmp = Double.parseDouble(s[i]);}
                catch (NumberFormatException e2) {return "Error: 您输入的第 " + (i + 1) + " 个值无法转化为decimal类型\n";}
            } else if(tableInfo.colInfo.get(i)[1].equals("varchar")) {
                // 判断是否引号匹配
                boolean bool = Utils.quotesMatch(s[i]);
                if(!bool)
                    return "Error: 第 " + (i + 1) + " 个值为字符串，应该用单引号括起来\n";
                // 判断字符串长度是否合理
                if(s[i].length() > Integer.parseInt(tableInfo.colInfo.get(i)[2].trim()) + 2) {
                    Mes = "Error: 字符串长度大于列宽度\n";
                    return Mes;
                }
            }
        }

        try {
            File tableFile = new File(TableManager.PATH, tableInfo.Name + ".midb");
            FileOutputStream fos = new FileOutputStream(tableFile, booll);;
            for(int j = 0; j < colNum; j++) {
                if (tableInfo.colInfo.get(j)[1].equals("varchar")) {
                    int len = Integer.parseInt(tableInfo.colInfo.get(j)[2].trim());
                    byte[] buf = ((String) s[j]).getBytes();
                    String tmp = (String) s[j];
//                    System.out.println(tmp);
                    while (buf.length < len * 4) {
                        tmp = "0" + tmp;
                        buf = tmp.getBytes();
                    }
                    fos.write(buf);
                }
                else {
                    ByteArrayOutputStream baos = new ByteArrayOutputStream();
                    ObjectOutputStream oos = new ObjectOutputStream(baos);
                    if (tableInfo.colInfo.get(j)[1].equals("decimal")) {
                        double value = Double.parseDouble(s[j].toString());
                        oos.writeObject(value);
                    }
                    else if (tableInfo.colInfo.get(j)[1].trim().equals("int")) {
                        int value = Integer.parseInt(s[j].toString());
                        oos.writeObject(value);
                    }
                    byte[] tmpb = baos.toByteArray();       // 转化为字节数组
                    byte[] bytes = new byte[TableManager.Len];  // 固定长度的字节数组
                    for (int k = 0; k < tmpb.length; k++)
                        bytes[k] = tmpb[k];
                    for (int k = tmpb.length; k < TableManager.Len; k++)
                        bytes[k] = (byte) 0;
                    fos.write(bytes);
                    oos.close();
                    baos.close();
                }
                Mes = "写入数据成功\n";
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return Mes;
    }

    public static String[] getConditionList(String conString) {
        String[] condList = conString.split(",");
        for(int i = 0; i < condList.length; i ++)
            condList[i] = condList[i].trim();
        return condList;
    }
}