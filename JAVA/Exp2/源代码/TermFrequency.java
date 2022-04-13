// ���ڴ�text�ļ��ж�ȡ�ؼ���
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;

// �洢��Ϣ�����ݽṹ
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;

// ��Excel�ļ����в���
import jxl.Sheet;
import jxl.Workbook;
import jxl.read.biff.BiffException;
import jxl.write.Label;
import jxl.write.WritableSheet;
import jxl.write.WritableWorkbook;
import jxl.write.WriteException;
import jxl.write.biff.RowsExceededException;

public class TermFrequency {
	// �洢�ϲ���Ĺ�Ʊ�ؼ�����Ϣ
	private HashSet<StockWordCount> StockSet = new HashSet<StockWordCount>();
	
	// ��ȫ���Ĺ�Ʊ�ؼ�����Ϣ���չ�Ʊ������������
	private ArrayList<StockWordCount> StockList = new ArrayList<StockWordCount>();
	
	// ��Ʊ֧��
	private int StockNum = 0;
	
	// ����Ʊ�ؼ�����Ϣ�����Excel��ʱ�ı�ͷ
	public static String[] Header = {"��Ʊ����","�ı�����","�ؼ��ʸ���","�ؼ��ʳ���","�ؼ����ܶ�","�ؼ����б�"};
	
	// �洢TEXT�ļ��еĹؼ���Ŀ¼
	public static List<String> keywords = null;
	
	// �ؼ���Ŀ¼�ĳ���
	public static int keywordsTotNum = 0;
	
	/**
	 * �޲ι��캯��
	 */
	public TermFrequency() {};
	
	/**
	 * ���ش洢����洢��Ʊ��Ϣ�Ĺ�ϣ��
	 * @return
	 */
	public HashSet<StockWordCount> getStockSet() {
		return StockSet;
	}
	
	/**
	 * ���ش洢�����Ʊ�ؼ�����Ϣ���б�
	 * @return
	 */
	public ArrayList<StockWordCount> getArrayList() {
		return StockList;
	}
	
	/**
	 * ���ع�Ʊ����
	 * @return
	 */
	public int getStockNum() {
		return StockNum;
	}
	
	/**
	 * ��TEXT�ļ��ж�ȡ���еĹؼ���
	 * @param Keywordsfilename �ļ������·��/����·��
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
	 * ֱ��ʹ���ַ���������Ϊ�ؼ����б�
	 * @param Keywords �洢���йؼ��ֵ��ַ�������
	 */
	public static void DefineKeywords(List<String> Keywords) {
		TermFrequency.keywords = Keywords;
	}
	
	/**
	 * ��Excel�ж�ȡ����Ϣ����ͬ��Ʊ����ϲ�������Ѿ��洢�ù�Ʊ����Ϣ��ϲ����������
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
	 * ����ArrayList���ݹ�Ʊ�������ȡ������Ϣ����
	 */
	public void SortedByCode() {
		for(StockWordCount Stock : StockSet) {
			StockList.add(Stock);
		}
		Collections.sort(StockList);
	}
	
	/**
	 * �����չ�Ʊ������������Ĺ�Ʊ�ؼ�����Ϣд��Excel�ļ���
	 * @param ResultFilename ָ������ļ���
	 * @param SheetName Excel�б�������Sheet����
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
	 * ��Excel�ж�ȡ��Ʊ�����Ϣ����ȡ�ؼ���
	 * @param Sourcefilename �洢��Ʊ�����Ϣ���ļ�
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
	 * ��Excel�ж�ȡ�洢��Ʊ�����Ϣ����ͳ�ƹؼ��ʡ���TEXT�ж�ȡ�ؼ���Ŀ¼
	 * ����������Ϣд��Excel�ļ���
	 * @param Sourcefilename �洢�����Ϣ��Excel·��
	 * @param Keywordsfilename �洢�ؼ���Ŀ¼��TEXT·��
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
	 * ������
	 * @param args ���մ洢��Ʊ�����Ϣ���ļ�����Excel�е�Sheet���ƣ��������ļ�������Sheet����
	 * @throws RowsExceededException
	 * @throws WriteException
	 */
	public static void main(String[] args) throws RowsExceededException, WriteException {
		Analysis(args[0], "../Keywords.txt",args[2],args[3]);
	}
}