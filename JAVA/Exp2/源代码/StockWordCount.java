import java.util.LinkedList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class StockWordCount implements Comparable<StockWordCount>{
	private String StockCode = "";
	// ��Ʊ����
	
	private List<String> KeywordsList =new LinkedList<String> ();
	// �ı��к��еĹؼ����б�
	
	private int TextLen = 0;
	// �ı��ܳ���
	
	private int KeywordsNum = 0;
	// �ؼ�������
	
	private int KeywordsLen = 0;
	// �ؼ����ܳ���
	
	private double KeywordsDensity = 0;
	// ��Ʊ�ؼ����ܶ�
	
	/**
	 * �޲ι��캯��
	 */
	public StockWordCount() {};
	
	/**
	 * �����ı��͹ؼ����б���ȡ��Ϣ
	 * @param StockCode ��Ʊ����
	 * @param StockText ��Ʊ�����Ϣ�ı�
	 * @param keywords �ؼ���Ŀ¼
	 */
	public StockWordCount(String StockCode, String StockText, List<String> keywords) {
		this.StockCode = StockCode;
		TakenKeywords(StockText, keywords);
	}
	
	/**
	 * �������Ϣ�ı�����ȡ�ؼ�����Ϣ
	 * @param Text	�����Ϣ�ı�
	 * @param keywords �ؼ���Ŀ¼
	 */
	public void TakenKeywords(String Text, List<String> keywords) {
		int KeywordsTot = keywords.size();
		
		String regStartSpace = "^[ ]*";
		String regEndSpace = "[ ]*$";
		String regFeed = "\\\\s*|\\t|\\r|\\n";
		
		Text = Text.replaceAll(regStartSpace, "").replaceAll(regEndSpace, "");
		Text = Text.replaceAll(regFeed, "");
		int TextTot = Text.length();
		TextLen = Text.length();
		int[] OccurStart = new int[TextTot + 3];;
		
		for(int i = 0; i < KeywordsTot; i ++) {
			String keyword = keywords.get(i);
			Pattern p = Pattern.compile(keyword);
			Matcher m = p.matcher(Text);
			
			while(m.find()) {
				int WordStart = m.start();
				if(OccurStart[WordStart] <= keyword.length())
					OccurStart[WordStart] = keyword.length();
			}
		}
		for(int i = 0; i < TextTot; i ++) {
			if(OccurStart[i] != 0) 
				for(int j = 1; j < OccurStart[i]; j ++) {
					if(OccurStart[i + j] > OccurStart[i]) OccurStart[i] = 0;
					else OccurStart[i + j] = 0;
				}
		}
		for(int i = 0; i < TextTot; i ++) {
			if(OccurStart[i] != 0) {
				KeywordsNum ++;
				KeywordsLen += OccurStart[i];
				KeywordsList.add(Text.substring(i, i + OccurStart[i]));
			}
		}
		KeywordsDensity = (double)KeywordsLen / (double)TextLen;
	}
	
	/**
	 * ��дcompareTo����������ArrayList���ݹ�Ʊ��������
	 */
	@Override
	public int compareTo(StockWordCount cntStock) {
		return ((this.getStockCode().compareTo(cntStock.getStockCode()) < 0 ) ? (-1)
                : (((this.getStockCode().compareTo(cntStock.getStockCode()) == 0)? 0 : 1)));
	}
	
	/**
	 * �ϲ�����������ͬ��Ʊ����Ĺؼ�����Ϣ
	 * @param cntStock
	 */
	public void AddedTo(StockWordCount cntStock) {
		KeywordsLen += cntStock.KeywordsLen;
		KeywordsList.addAll(cntStock.KeywordsList);
		KeywordsNum += cntStock.KeywordsNum;
		TextLen += cntStock.TextLen;
		KeywordsDensity = (double)KeywordsLen / (double)TextLen;
	}
	
	/**
	 * ��ȡ��Ʊ����
	 * @return
	 */
	public String getStockCode() {
		return StockCode;
	}
	
	/**
	 * ��ȡ�ؼ��ʳ���
	 * @return
	 */
	public int getKeywordsLen() {
		return KeywordsLen;
	}
	
	/**
	 * ��ȡ�ؼ��ʸ���
	 * @return
	 */
	public int getKeywordsNum() {
		return KeywordsNum;
	}
	
	/**
	 * ��ȡ�ı��ܳ���
	 * @return
	 */
	public int getTextLen() {
		return TextLen;
	}
	
	/**
	 * ��ȡ�ؼ����ܶ�
	 * @return
	 */
	public double getKeywordsDensity() {
		return KeywordsDensity;
	}
	
	/**
	 * ��ȡ�����Ϣ�ı��г��ֵĹؼ����б�
	 * @return
	 */
	public List<String> getKeywordsList() {
		return KeywordsList;
	}
}
