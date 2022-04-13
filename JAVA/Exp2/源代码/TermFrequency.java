// 用于从text文件中读取关键字
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;

// 存储信息的数据结构
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;

// 对Excel文件进行操作
import jxl.Sheet;
import jxl.Workbook;
import jxl.read.biff.BiffException;
import jxl.write.Label;
import jxl.write.WritableSheet;
import jxl.write.WritableWorkbook;
import jxl.write.WriteException;
import jxl.write.biff.RowsExceededException;

public class TermFrequency {
	// 存储合并后的股票关键词信息
	private HashSet<StockWordCount> StockSet = new HashSet<StockWordCount>();
	
	// 将全部的股票关键词信息按照股票代码升序排序
	private ArrayList<StockWordCount> StockList = new ArrayList<StockWordCount>();
	
	// 股票支数
	private int StockNum = 0;
	
	// 将股票关键字信息输出到Excel中时的表头
	public static String[] Header = {"股票代号","文本长度","关键词个数","关键词长度","关键词密度","关键词列表"};
	
	// 存储TEXT文件中的关键字目录
	public static List<String> keywords = null;
	
	// 关键字目录的长度
	public static int keywordsTotNum = 0;
	
	/**
	 * 无参构造函数
	 */
	public TermFrequency() {};
	
	/**
	 * 返回存储无序存储股票信息的哈希表
	 * @return
	 */
	public HashSet<StockWordCount> getStockSet() {
		return StockSet;
	}
	
	/**
	 * 返回存储有序股票关键字信息的列表
	 * @return
	 */
	public ArrayList<StockWordCount> getArrayList() {
		return StockList;
	}
	
	/**
	 * 返回股票总数
	 * @return
	 */
	public int getStockNum() {
		return StockNum;
	}
	
	/**
	 * 从TEXT文件中读取所有的关键字
	 * @param Keywordsfilename 文件的相对路径/绝对路径
	 */
	public static void DefineKeywords(String Keywordsfilename) {
		try {
			keywords = Files.readAllLines(Paths.get(Keywordsfilename), StandardCharsets.UTF_8);
		} catch (IOException e) {
			e.printStackTrace();
		}
		keywordsTotNum = keywords.size();
	}
	
	/**
	 * 直接使用字符串数组作为关键字列表
	 * @param Keywords 存储所有关键字的字符串数组
	 */
	public static void DefineKeywords(List<String> Keywords) {
		TermFrequency.keywords = Keywords;
	}
	
	/**
	 * 将Excel中读取的信息中相同股票代码合并，如果已经存储该股票的信息则合并，否则添加
	 */
	public void HashAdd(StockWordCount cntStock) {
		for(StockWordCount Stock:StockSet) {
			if(Stock.getStockCode().compareTo(cntStock.getStockCode()) == 0) {
				Stock.AddedTo(cntStock);
				return ;
			}
		}
		StockSet.add(cntStock);
		StockNum ++;
	}

	/**
	 * 利用ArrayList根据股票代码对提取出的信息排序
	 */
	public void SortedByCode() {
		for(StockWordCount Stock : StockSet) {
			StockList.add(Stock);
		}
		Collections.sort(StockList);
	}
	
	/**
	 * 将按照股票代码升序排序的股票关键字信息写入Excel文件中
	 * @param ResultFilename 指定输出文件名
	 * @param SheetName Excel中保存结果的Sheet名称
	 * @throws RowsExceededException
	 * @throws WriteException
	 */
	public void WriteToExcel(String ResultFilename, String SheetName) throws RowsExceededException, WriteException {
		File ResultExcel = new File(ResultFilename);
		WritableWorkbook wbExcel = null;
		try {
			wbExcel = Workbook.createWorkbook(ResultExcel);
		} catch (IOException e) {
			e.printStackTrace();
		}
		WritableSheet ResultSheet = wbExcel.createSheet(SheetName, 0);
		
		int Rows = StockNum;
		int Columns = 6;
		for(int col = 0; col < Columns; col ++) 
			ResultSheet.addCell(new Label(col, 0, Header[col]));
		
		for(int row = 1; row <= Rows; row ++) 
			for(int col = 0; col <= Columns; col ++) {
				if(col == 0) ResultSheet.addCell(new Label(col, row, StockList.get(row-1).getStockCode()));
				if(col == 1) ResultSheet.addCell(new Label(col, row, String.valueOf(StockList.get(row-1).getTextLen())));
				if(col == 2) ResultSheet.addCell(new Label(col, row, String.valueOf(StockList.get(row-1).getKeywordsNum())));
				if(col == 3) ResultSheet.addCell(new Label(col, row, String.valueOf(StockList.get(row-1).getKeywordsLen())));
				if(col == 4) ResultSheet.addCell(new Label(col, row, String.valueOf(StockList.get(row-1).getKeywordsDensity())));
				if(col == 5) {
					String Keywords = "";
					List<String> cntKeywordsList = StockList.get(row-1).getKeywordsList();
					for(String words : cntKeywordsList) 
						Keywords += words + ',';
					if(Keywords.length() != 0)
						Keywords = Keywords.substring(0, Keywords.length()-1);
					ResultSheet.addCell(new Label(col, row, Keywords));
				}
			}
		try {
			wbExcel.write();
		} catch (IOException e) {
			e.printStackTrace();
		}
		try {
			wbExcel.close();
		} catch (WriteException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
	
	/**
	 * 从Excel中读取股票审计信息并提取关键字
	 * @param Sourcefilename 存储股票审计信息的文件
	 */
	public void LoadData(String Sourcefilename) {
		File SourceExcel = new File(Sourcefilename);
		try {
			InputStream isExcel = new FileInputStream(SourceExcel.getAbsolutePath());
			Workbook wbExcel = Workbook.getWorkbook(isExcel);
			int ExcelSheetNum = wbExcel.getNumberOfSheets();
			for(int index = 0; index < ExcelSheetNum; index ++) {
				Sheet ExcelSheet = wbExcel.getSheet(index);
				int SheetRows = ExcelSheet.getRows();
				int SheetColumns = ExcelSheet.getColumns();
				for(int i = 1; i < SheetRows; i ++) {
					String StockCode = ExcelSheet.getCell(0, i).getContents();
					String StockText = "";
					for(int j = 2; j < SheetColumns; j ++) 
						StockText += ExcelSheet.getCell(j, i).getContents();
					StockWordCount Stock = new StockWordCount(StockCode, StockText, keywords);
					HashAdd(Stock);
				}
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
        } catch (BiffException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
	}
	
	/**
	 * 从Excel中读取存储股票审计信息，并统计关键词。从TEXT中读取关键词目录
	 * 将处理后的信息写入Excel文件中
	 * @param Sourcefilename 存储审计信息的Excel路径
	 * @param Keywordsfilename 存储关键字目录的TEXT路径
	 * @throws WriteException 
	 * @throws RowsExceededException 
	 */
	public static void Analysis(String Sourcefilename, String Keywordsfilename,String Resultfilename, String SheetName) throws RowsExceededException, WriteException {
		TermFrequency.DefineKeywords(Keywordsfilename);
		TermFrequency TermFre = new TermFrequency();
		TermFre.LoadData(Sourcefilename);
		TermFre.SortedByCode();
		TermFre.WriteToExcel(Resultfilename, SheetName);
	}
	
	/**
	 * 主函数
	 * @param args 接收存储股票审计信息的文件名、Excel中的Sheet名称，输出结果文件命名和Sheet名称
	 * @throws RowsExceededException
	 * @throws WriteException
	 */
	public static void main(String[] args) throws RowsExceededException, WriteException {
		Analysis(args[0], "../Keywords.txt",args[2],args[3]);
	}
}