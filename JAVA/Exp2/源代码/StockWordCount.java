import java.util.LinkedList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class StockWordCount implements Comparable<StockWordCount>{
	private String StockCode = "";
	// 股票代码
	
	private List<String> KeywordsList =new LinkedList<String> ();
	// 文本中含有的关键字列表
	
	private int TextLen = 0;
	// 文本总长度
	
	private int KeywordsNum = 0;
	// 关键词数量
	
	private int KeywordsLen = 0;
	// 关键词总长度
	
	private double KeywordsDensity = 0;
	// 股票关键词密度
	
	/**
	 * 无参构造函数
	 */
	public StockWordCount() {};
	
	/**
	 * 根据文本和关键词列表提取信息
	 * @param StockCode 股票代码
	 * @param StockText 股票审计信息文本
	 * @param keywords 关键词目录
	 */
	public StockWordCount(String StockCode, String StockText, List<String> keywords) {
		this.StockCode = StockCode;
		TakenKeywords(StockText, keywords);
	}
	
	/**
	 * 从审计信息文本中提取关键词信息
	 * @param Text	审计信息文本
	 * @param keywords 关键词目录
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
	 * 重写compareTo方法，用于ArrayList根据股票代码排序
	 */
	@Override
	public int compareTo(StockWordCount cntStock) {
		return ((this.getStockCode().compareTo(cntStock.getStockCode()) < 0 ) ? (-1)
                : (((this.getStockCode().compareTo(cntStock.getStockCode()) == 0)? 0 : 1)));
	}
	
	/**
	 * 合并俩个具有相同股票代码的关键词信息
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
	 * 获取股票代码
	 * @return
	 */
	public String getStockCode() {
		return StockCode;
	}
	
	/**
	 * 获取关键词长度
	 * @return
	 */
	public int getKeywordsLen() {
		return KeywordsLen;
	}
	
	/**
	 * 获取关键词个数
	 * @return
	 */
	public int getKeywordsNum() {
		return KeywordsNum;
	}
	
	/**
	 * 获取文本总长度
	 * @return
	 */
	public int getTextLen() {
		return TextLen;
	}
	
	/**
	 * 获取关键词密度
	 * @return
	 */
	public double getKeywordsDensity() {
		return KeywordsDensity;
	}
	
	/**
	 * 获取审计信息文本中出现的关键词列表
	 * @return
	 */
	public List<String> getKeywordsList() {
		return KeywordsList;
	}
}
