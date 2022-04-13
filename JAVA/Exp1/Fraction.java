//package Exp1;
import java.math.BigInteger;
import java.lang.Math;

/**
 * 此类Fraction是一个用于分数表示和运算的类。
 * 该类基于大整数类BigInteger。
 */
public class Fraction implements Comparable<Fraction> {
	private int sign = 0; 
	// 分数的正负号，正数1，负数-1，零0
    private BigInteger numerator = BigInteger.ZERO; 
    // 分数的分子
    private  BigInteger denominator = BigInteger.ZERO; 
    // 分数的分母
    public static final Fraction ZERO = new Fraction(0, 1); 
    // 分数常量 0/1
    public static final Fraction ONE = new Fraction(1, 1); 
    // 分数常量 +1/1
    public static final Fraction NEGATIVE_INFINITY = new Fraction(-1, 0); 
    // 分数常量 -1/0，即负无穷
    public static final Fraction POSITIVE_INFINITY = new Fraction(1, 0); 
    // 分数常量 +1/0，即正无穷
    public static final Fraction NAN = new Fraction(0, 0); 
    // 分数常量，0/0，即：不是一个分数
    
    /**
     * 构造方法：由两个大整数构造一个分数，大整数带正负号，最终的分数的正负号通过计算获得。
     * 需要进行处理，包括符号处理，也包括约分处理。
     * @param primNumerator 输入的分子，最终的构造的分数的分子很可能不是这个输入。
     * @param primDenominator 输入的分母，最终的构造的分数的分母很有可能不是这个输入。
     */
    public Fraction(BigInteger primNumerator, BigInteger primDenominator) {
    	// 0/0
    	if(primNumerator.signum()==0&&primDenominator.signum()==0) {
    		numerator = BigInteger.ZERO;
    		denominator = BigInteger.ZERO; 
    		sign=0;
    	}
    	// 1/0和-1/0
    	else if(primDenominator.signum()==0) {
			numerator=primNumerator.abs();
			denominator = BigInteger.ZERO;
    		sign=primNumerator.signum();
    	}
    	// 0/1
    	else if(primNumerator.signum()==0) {
    		numerator = BigInteger.ZERO;
    		denominator=primDenominator.abs();
    		sign=0;
    	}
    	// 约分
    	else {
    		BigInteger a=primNumerator.abs();
    		BigInteger b=primDenominator.abs();
    		
        	if(b.compareTo(a)==1) {
        		BigInteger t=b;
        		b=a;a=t;
        	}
        	BigInteger r=a.mod(b);
        	while(r!=BigInteger.ZERO) {
        		a=b;b=r;r=a.mod(b);
        	}
        	
    		numerator=primNumerator.abs().divide(b);
    		denominator=primDenominator.abs().divide(b);
    		sign=primNumerator.signum()*primDenominator.signum();
    	}
    }
    
    /**
     * 构造方法：用两个长整型构造一个分数。
     * 需要进行处理，包括符号处理，也包括约分处理。
     * @param lNumerator 输入的长整数分子。
     * @param lDenominator 输入的长整数分母。
     */
    public Fraction(long lNumerator, long lDenominator) {
    	// 0/0
        if(lNumerator==0&&lDenominator==0) {
        	sign=0;
        	numerator=new BigInteger(""+lNumerator);
        	denominator=new BigInteger(""+lDenominator);
        }
        // 0/1
        else if(lNumerator==0) {
        	numerator=BigInteger.ZERO;
        	denominator=new BigInteger(""+Math.abs(lDenominator));
        	sign=0;
        }
        // 1/0或-1/0
        else if(lDenominator==0) {
        	if(lNumerator>0)
        		sign=1;
        	else
        		sign=-1;
        	numerator=new BigInteger(""+Math.abs(lNumerator));
        	denominator=BigInteger.ZERO;
        }
        // 约分
        else {
        	BigInteger BiglNumerator=new BigInteger(""+lNumerator);
        	BigInteger BiglDenominator=new BigInteger(""+lDenominator);
        	
        	BigInteger a=BiglNumerator.abs();
        	BigInteger b=BiglDenominator.abs();
        	if(b.compareTo(a)==1) {
        		BigInteger t=b;
        		b=a;a=t;
        	}
        	BigInteger r=a.mod(b);
        	while(r!=BigInteger.ZERO) {
        		a=b;b=r;r=a.mod(b);
        	}
        	
        	numerator=(BiglNumerator.divide(b)).abs();
        	denominator=(BiglDenominator.divide(b)).abs();
        	sign=BiglNumerator.signum()*BiglDenominator.signum();
        }
    }

    /**
     * 用一个长整数构造一个分数，默认分数的分母是1。
     * @param integerValue 输入的长整数，其绝对值与构造生成的分数的分子相同。
     */
    public Fraction(long integerValue) {
        denominator=BigInteger.ZERO;
        numerator=new BigInteger(""+Math.abs(integerValue));
        if(integerValue==0) sign=0;
        if(integerValue>0) sign=1;
        else sign=-1;
    }
    
    /**
     * 获取本分数的分子，注意分子恒为非负。
     * @return 本分数的分子。
     */
    public BigInteger getNumerator() {
    	return numerator;
    }

    /**
     * 获取本分数的分母。注意分母恒为非负。
     * @return 本分数的分母。
     */
    public BigInteger getDenominator() {
        return denominator;
    }

    /**
     * 用来描述这个分数的字符串，例如“-7/2”，“+1/0”等等。
     * @return
     */
    @Override
    public String toString() {
    	String str=new String();
        if(sign==-1) str="-";
        if(sign==1)  str="+";
        str+=numerator.longValueExact()+"/"+denominator.longValueExact();
        return str;
    }

    /**
     * 判断此分数是否为“非数”，也就是是否是“0/0”类型。
     * @return 如果是一个非数，返回true，否则返回false
     */
    public boolean isNaN() {
    	return this.equals(NAN);
    }

    /**
     * 判断此分数是否为0，也就是是否为“0/1”这各类型的分数。
     * @return 是的话返回true；否则返回false
     */
    public boolean isZero() {
         if(this.numerator.equals(BigInteger.ZERO)) return true;
         else return false;
    }    
    
    /**
     * 判断此分数是否是正的分数；当然，正无穷也是正的分数。
     * @return 是的话返回true，否则返回false。
     */
    public boolean isPositive() {
    	return (sign==1)?true:false;
    }

    /**
     * 判断此分数是否为负的，当然负无穷也是负的。
     * @return 如果是负分数，则返回true，否则返回false。
     */
    public boolean isNegative() {
    	return (sign==-1)?true:false;
    }

    /**
     * 判断此分数是否为无穷大，包括正无穷和负无穷。
     * @return 如果是无穷大，则返回true，否则返回false。
     */
    public boolean isInfinite() {
        return (denominator.equals(BigInteger.ZERO))?true:false;
    }

    /**
     * 把本分数的内容全部拷贝，生成一个新的分数返回。
     * @return 本分数的一个复制版本。
     */
    @Override
    public Fraction clone() {
    	Fraction fra=new Fraction(numerator,denominator);
        fra.sign=this.sign;
        return fra;
    }

    /**
     * 求本分数的绝对值并返回。
     * @return 本分数的绝对值，也是一个分数。
     */
    public Fraction abs() {
        Fraction fra=this.clone();
        if(fra.sign!=0) fra.sign=1;
        return fra;
    }

    /**
     * 求本分数的相反数，也是一个分数。
     * @return 本分数的相反数。
     */
    public Fraction opposite() {
        Fraction fra=this.clone();
        fra.sign=-fra.sign;
        return fra;
    }

    /**
     * 求本分数的倒数，也是一个分数。正负无穷的倒数都是0，但0的倒数规定为正无穷而不是负无穷。
     * @return 本分数的倒数。
     */
    public Fraction reciprocal() {
    	Fraction fra=new Fraction(denominator,numerator);
        if(this.isZero()) fra.sign=1;
        return fra;
    }

    /**
     * 绝对值比较大小。本分数的绝对值和that的绝对值比较大小。
     * 把NaN当作0处理；正无穷和正无穷比较为相等。
     * @param that 与本分数待比较的分数。
     * @return 当本分数的绝对值和that的绝对值相等时返回0；本分数绝对值小的时候返回-1，绝对值大的时候返回1。
     */
    @SuppressWarnings("unused")
	private int absCompareTo(Fraction that) {
		Fraction that_abs=that.abs();
		Fraction this_abs=this.abs();
		if(this.isNaN()||this.isZero()) {
			if(that.isNaN()||that.isZero()) return 0;
			else return -1;
		}
		else if(this_abs.isInfinite()) {
			if(that_abs.isInfinite())
				return 0;
			else return 1;
		}
		else {
			if(that_abs.isNaN()||that_abs.isZero()) return 1;
			if(that_abs.isInfinite()) return -1;
		}
		 
		BigInteger numerator_that=that_abs.numerator.multiply(this_abs.denominator);    
		BigInteger numerator_this=this_abs.numerator.multiply(that_abs.denominator);
		 
		int flag=0;
		if(numerator_that.max(numerator_this).equals(numerator_this)&&numerator_that.max(numerator_this).equals(numerator_that))
			flag=0;
		else if(numerator_that.max(numerator_this).equals(numerator_this))
			flag=1;
		else flag=-1;
		return flag;
    }
    
    /**
     * 两个分数比较大小。
     * @param that 与本分数待比较的分数。
     * @return 如果两个分数值相等，返回0；如果本分数小，返回-1；否则返回1。
     */
    @Override
    public int compareTo(Fraction that) {
    	int flag=1;
        if(this.sign>that.sign) flag=1;
        else if(this.sign==0&&that.sign==0) flag=0;
        else if(this.sign<that.sign) flag=-1;
        else {
        	flag=this.absCompareTo(that);
        	if(this.sign<0&&that.sign<0)
        		flag=-flag;
        }
        return flag;
    }

    /**
     * 两个非负分数相加。
     * @param that 与本分数待相加的分数。
     * @return 两个分数相加的和，仍然时一个分数。
     */
    @SuppressWarnings("unused")
	private Fraction positiveAdd(Fraction that) {
    	Fraction fra;
    	if(that.isNaN()||that.isZero()) fra=this.clone();
    	else if(that.isInfinite()||this.isInfinite()) fra=this.POSITIVE_INFINITY;
    	else {
    		BigInteger numerator=this.numerator.multiply(that.denominator).add(that.numerator.multiply(this.denominator));
    		BigInteger denominator=this.denominator.multiply(that.denominator);
    		fra=new Fraction(numerator,denominator);
    	}
    	return fra;
    }

    /**
     * 两个非负的分数相减。
     * @param smaller 这是减数，本分数时被减数。
     * @return 返回两个分数的差。
     */
    @SuppressWarnings("unused")
	private Fraction positiveSubtract(Fraction smaller) {
    	Fraction fra;
    	if(smaller.isNaN()||smaller.isZero()) fra=this.clone();
    	else if(smaller.isInfinite()) {
    		if(this.isInfinite())
    			fra=new Fraction(this.numerator.subtract(smaller.numerator),this.denominator);
    		else fra=this.NEGATIVE_INFINITY;
    	}
    	else {
    		BigInteger numerator=this.numerator.multiply(smaller.denominator).subtract(smaller.numerator.multiply(this.denominator));
    		BigInteger denominator=this.denominator.multiply(smaller.denominator);
    		fra=new Fraction(numerator,denominator);
    	}
    	return fra;
    }

    /**
    * 两个分数相加。
    * @param that 加数。本分数是被加数。
    * @return 两个分数的加和。
    */
   public Fraction add(Fraction that) {
	   Fraction this_abs=this.abs();
	   Fraction that_abs=that.abs();
	   Fraction result;
	   // 两数符号相同，可直接转化为绝对值相加后再改变符号
	   if(this.sign==that.sign) {
		   result=this_abs.positiveAdd(that_abs);
		   result.sign=this.sign;
	   }
	   else {
		   // 有一个操作数为0
		   if(this.sign==0||that.sign==0) 
			   result=(this.sign==0)?that.clone():this.clone();
		   // 两个操作数符号不同且均不为0：that-this / this-that
		   else {
			   if(this.sign==-1) 
				   result=that_abs.positiveSubtract(this_abs);
			   else result=this_abs.positiveSubtract(that_abs);
		   }
	   }
	   return result;
   }

   /**
    * 两个分数相减。
    * @param that 减数。
    * @return 本分数减去that的差。
    */
   public Fraction subtract(Fraction that) {
	   Fraction result=this.add(that.opposite());
	   return result;
   }
   
   /**
    * 一个分数和另一个分数相乘。
    * @param factor 乘数。本分数是被乘数。
    * @return 两个分数的积，仍然是一个分数。
    */
   public Fraction multiply(Fraction factor) {
	   BigInteger numerator=this.numerator.multiply(factor.numerator);
	   BigInteger denominator=this.denominator.multiply(factor.denominator);
	   Fraction result=new Fraction(numerator,denominator);
	   return result;
   }

   /**
    * 本分数乘以一个长整数因子，获取一个新的分数。
    * @param ratio 待乘的因子。
    * @return 放大后新的分数。
    */
   public Fraction multiply(long ratio) {
	   BigInteger ratioBigInteger=new BigInteger(""+ratio);
	   BigInteger numerator=this.numerator.multiply(ratioBigInteger);
	   Fraction result=new Fraction(numerator,this.denominator);
	   return result;
   }

   /**
    * 获取本分数除以另外一个分数的商。
    * @param divisor 除数。
    * @return 商。
    */
   public Fraction divide(Fraction divisor) {
	   Fraction divisorReciprocal=divisor.reciprocal();
	   Fraction result=this.multiply(divisorReciprocal);
	   return result;
   }
   
   /**
    * 获取本分数除以一个长整数因子后的商。
    * @param ratio 除数，一个长整数因子。
    * @return 商。
    */
   public Fraction divide(long ratio) {
	   Fraction ratioFraction=new Fraction(ratio);
	   Fraction result=this.divide(ratioFraction);
	   return  result;
   }
   
   /**
    * 一个简单的测试。计算 1/(1*2) + 1/(2*3) + ... + 1/(100*101)
    * 事实上，上式等于 (1/1 - 1/2) + (1/2 - 1/3) + ... + (1/100 - 1/101)
    * 最后的结果应该是 "+100/101"。
    */
   public static void testSimple() {
       Fraction sum = ZERO;
       for (int i=1; i<=200; i++) {
           int denominator = i * (i+1);
           Fraction addend = new Fraction(1, denominator);
           sum = sum.add(addend);
       }
       System.out.println(sum);
   }

   /**
    * 一个复杂的测试：计算 [ 1/(1*2) + 1/(2*3) + ... + 1/(2022*2023) ] - [ 1/(1*3) + 1/(3*5) + ... + 1/(2021*2023) ]
    * 被减数最后的结果是 +2022/2023，减数最后的结果是 1011/2023，最终的结果应该是 1011/2023。
    * 我们把所有的项存起来，完全随机打乱顺序，用来测试 Fraction 类的计算正确性和计算能力。
    */
   public static void testComplex() {
       java.util.ArrayList<Fraction> al = new java.util.ArrayList<Fraction>();
       int quantity = 2022;
       for (int i=1; i<=quantity; i++) {
           int denominator = i * (i+1);
           Fraction addend = new Fraction(1, denominator);
           al.add(addend);  
       }
       for (int i=1; i<=quantity-1; i+=2) {
           int denominator = i * (i+2);
           Fraction addend = new Fraction(1, denominator);
           al.add(addend.opposite());
       }
       int size = al.size();
       Fraction[] fractions = new Fraction[size];
       al.toArray(fractions);
       for (int i=0; i<size; i++) {
           int pos = (int)(Math.random() * size);
           Fraction temp = fractions[i];
           fractions[i] = fractions[pos];
           fractions[pos] = temp;
       }
       Fraction sum = Fraction.ZERO;
       for (int i=0; i<size; i++) {
           sum = sum.add(fractions[i]);
       }
       System.out.println(sum);
   }
   
   public static void main(String[] args) {
	   testSimple();
       testComplex();
   }
}

