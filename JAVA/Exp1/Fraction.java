//package Exp1;
import java.math.BigInteger;
import java.lang.Math;

/**
 * ����Fraction��һ�����ڷ�����ʾ��������ࡣ
 * ������ڴ�������BigInteger��
 */
public class Fraction implements Comparable<Fraction> {
	private int sign = 0; 
	// �����������ţ�����1������-1����0
    private BigInteger numerator = BigInteger.ZERO; 
    // �����ķ���
    private  BigInteger denominator = BigInteger.ZERO; 
    // �����ķ�ĸ
    public static final Fraction ZERO = new Fraction(0, 1); 
    // �������� 0/1
    public static final Fraction ONE = new Fraction(1, 1); 
    // �������� +1/1
    public static final Fraction NEGATIVE_INFINITY = new Fraction(-1, 0); 
    // �������� -1/0����������
    public static final Fraction POSITIVE_INFINITY = new Fraction(1, 0); 
    // �������� +1/0����������
    public static final Fraction NAN = new Fraction(0, 0); 
    // ����������0/0����������һ������
    
    /**
     * ���췽��������������������һ���������������������ţ����յķ�����������ͨ�������á�
     * ��Ҫ���д����������Ŵ���Ҳ����Լ�ִ���
     * @param primNumerator ����ķ��ӣ����յĹ���ķ����ķ��Ӻܿ��ܲ���������롣
     * @param primDenominator ����ķ�ĸ�����յĹ���ķ����ķ�ĸ���п��ܲ���������롣
     */
    public Fraction(BigInteger primNumerator, BigInteger primDenominator) {
    	// 0/0
    	if(primNumerator.signum()==0&&primDenominator.signum()==0) {
    		numerator = BigInteger.ZERO;
    		denominator = BigInteger.ZERO; 
    		sign=0;
    	}
    	// 1/0��-1/0
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
    	// Լ��
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
     * ���췽���������������͹���һ��������
     * ��Ҫ���д����������Ŵ���Ҳ����Լ�ִ���
     * @param lNumerator ����ĳ��������ӡ�
     * @param lDenominator ����ĳ�������ĸ��
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
        // 1/0��-1/0
        else if(lDenominator==0) {
        	if(lNumerator>0)
        		sign=1;
        	else
        		sign=-1;
        	numerator=new BigInteger(""+Math.abs(lNumerator));
        	denominator=BigInteger.ZERO;
        }
        // Լ��
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
     * ��һ������������һ��������Ĭ�Ϸ����ķ�ĸ��1��
     * @param integerValue ����ĳ������������ֵ�빹�����ɵķ����ķ�����ͬ��
     */
    public Fraction(long integerValue) {
        denominator=BigInteger.ZERO;
        numerator=new BigInteger(""+Math.abs(integerValue));
        if(integerValue==0) sign=0;
        if(integerValue>0) sign=1;
        else sign=-1;
    }
    
    /**
     * ��ȡ�������ķ��ӣ�ע����Ӻ�Ϊ�Ǹ���
     * @return �������ķ��ӡ�
     */
    public BigInteger getNumerator() {
    	return numerator;
    }

    /**
     * ��ȡ�������ķ�ĸ��ע���ĸ��Ϊ�Ǹ���
     * @return �������ķ�ĸ��
     */
    public BigInteger getDenominator() {
        return denominator;
    }

    /**
     * ������������������ַ��������硰-7/2������+1/0���ȵȡ�
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
     * �жϴ˷����Ƿ�Ϊ����������Ҳ�����Ƿ��ǡ�0/0�����͡�
     * @return �����һ������������true�����򷵻�false
     */
    public boolean isNaN() {
    	return this.equals(NAN);
    }

    /**
     * �жϴ˷����Ƿ�Ϊ0��Ҳ�����Ƿ�Ϊ��0/1��������͵ķ�����
     * @return �ǵĻ�����true�����򷵻�false
     */
    public boolean isZero() {
         if(this.numerator.equals(BigInteger.ZERO)) return true;
         else return false;
    }    
    
    /**
     * �жϴ˷����Ƿ������ķ�������Ȼ��������Ҳ�����ķ�����
     * @return �ǵĻ�����true�����򷵻�false��
     */
    public boolean isPositive() {
    	return (sign==1)?true:false;
    }

    /**
     * �жϴ˷����Ƿ�Ϊ���ģ���Ȼ������Ҳ�Ǹ��ġ�
     * @return ����Ǹ��������򷵻�true�����򷵻�false��
     */
    public boolean isNegative() {
    	return (sign==-1)?true:false;
    }

    /**
     * �жϴ˷����Ƿ�Ϊ����󣬰���������͸����
     * @return �����������򷵻�true�����򷵻�false��
     */
    public boolean isInfinite() {
        return (denominator.equals(BigInteger.ZERO))?true:false;
    }

    /**
     * �ѱ�����������ȫ������������һ���µķ������ء�
     * @return ��������һ�����ư汾��
     */
    @Override
    public Fraction clone() {
    	Fraction fra=new Fraction(numerator,denominator);
        fra.sign=this.sign;
        return fra;
    }

    /**
     * �󱾷����ľ���ֵ�����ء�
     * @return �������ľ���ֵ��Ҳ��һ��������
     */
    public Fraction abs() {
        Fraction fra=this.clone();
        if(fra.sign!=0) fra.sign=1;
        return fra;
    }

    /**
     * �󱾷������෴����Ҳ��һ��������
     * @return ���������෴����
     */
    public Fraction opposite() {
        Fraction fra=this.clone();
        fra.sign=-fra.sign;
        return fra;
    }

    /**
     * �󱾷����ĵ�����Ҳ��һ����������������ĵ�������0����0�ĵ����涨Ϊ����������Ǹ����
     * @return �������ĵ�����
     */
    public Fraction reciprocal() {
    	Fraction fra=new Fraction(denominator,numerator);
        if(this.isZero()) fra.sign=1;
        return fra;
    }

    /**
     * ����ֵ�Ƚϴ�С���������ľ���ֵ��that�ľ���ֵ�Ƚϴ�С��
     * ��NaN����0�����������������Ƚ�Ϊ��ȡ�
     * @param that �뱾�������Ƚϵķ�����
     * @return ���������ľ���ֵ��that�ľ���ֵ���ʱ����0������������ֵС��ʱ�򷵻�-1������ֵ���ʱ�򷵻�1��
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
     * ���������Ƚϴ�С��
     * @param that �뱾�������Ƚϵķ�����
     * @return �����������ֵ��ȣ�����0�����������С������-1�����򷵻�1��
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
     * �����Ǹ�������ӡ�
     * @param that �뱾��������ӵķ�����
     * @return ����������ӵĺͣ���Ȼʱһ��������
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
     * �����Ǹ��ķ��������
     * @param smaller ���Ǽ�����������ʱ��������
     * @return �������������Ĳ
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
    * ����������ӡ�
    * @param that �������������Ǳ�������
    * @return ���������ļӺ͡�
    */
   public Fraction add(Fraction that) {
	   Fraction this_abs=this.abs();
	   Fraction that_abs=that.abs();
	   Fraction result;
	   // ����������ͬ����ֱ��ת��Ϊ����ֵ��Ӻ��ٸı����
	   if(this.sign==that.sign) {
		   result=this_abs.positiveAdd(that_abs);
		   result.sign=this.sign;
	   }
	   else {
		   // ��һ��������Ϊ0
		   if(this.sign==0||that.sign==0) 
			   result=(this.sign==0)?that.clone():this.clone();
		   // �������������Ų�ͬ�Ҿ���Ϊ0��that-this / this-that
		   else {
			   if(this.sign==-1) 
				   result=that_abs.positiveSubtract(this_abs);
			   else result=this_abs.positiveSubtract(that_abs);
		   }
	   }
	   return result;
   }

   /**
    * �������������
    * @param that ������
    * @return ��������ȥthat�Ĳ
    */
   public Fraction subtract(Fraction that) {
	   Fraction result=this.add(that.opposite());
	   return result;
   }
   
   /**
    * һ����������һ��������ˡ�
    * @param factor �������������Ǳ�������
    * @return ���������Ļ�����Ȼ��һ��������
    */
   public Fraction multiply(Fraction factor) {
	   BigInteger numerator=this.numerator.multiply(factor.numerator);
	   BigInteger denominator=this.denominator.multiply(factor.denominator);
	   Fraction result=new Fraction(numerator,denominator);
	   return result;
   }

   /**
    * ����������һ�����������ӣ���ȡһ���µķ�����
    * @param ratio ���˵����ӡ�
    * @return �Ŵ���µķ�����
    */
   public Fraction multiply(long ratio) {
	   BigInteger ratioBigInteger=new BigInteger(""+ratio);
	   BigInteger numerator=this.numerator.multiply(ratioBigInteger);
	   Fraction result=new Fraction(numerator,this.denominator);
	   return result;
   }

   /**
    * ��ȡ��������������һ���������̡�
    * @param divisor ������
    * @return �̡�
    */
   public Fraction divide(Fraction divisor) {
	   Fraction divisorReciprocal=divisor.reciprocal();
	   Fraction result=this.multiply(divisorReciprocal);
	   return result;
   }
   
   /**
    * ��ȡ����������һ�����������Ӻ���̡�
    * @param ratio ������һ�����������ӡ�
    * @return �̡�
    */
   public Fraction divide(long ratio) {
	   Fraction ratioFraction=new Fraction(ratio);
	   Fraction result=this.divide(ratioFraction);
	   return  result;
   }
   
   /**
    * һ���򵥵Ĳ��ԡ����� 1/(1*2) + 1/(2*3) + ... + 1/(100*101)
    * ��ʵ�ϣ���ʽ���� (1/1 - 1/2) + (1/2 - 1/3) + ... + (1/100 - 1/101)
    * ���Ľ��Ӧ���� "+100/101"��
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
    * һ�����ӵĲ��ԣ����� [ 1/(1*2) + 1/(2*3) + ... + 1/(2022*2023) ] - [ 1/(1*3) + 1/(3*5) + ... + 1/(2021*2023) ]
    * ���������Ľ���� +2022/2023���������Ľ���� 1011/2023�����յĽ��Ӧ���� 1011/2023��
    * ���ǰ����е������������ȫ�������˳���������� Fraction ��ļ�����ȷ�Ժͼ���������
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

