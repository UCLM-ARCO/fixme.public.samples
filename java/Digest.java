class Digest {
    public static byte digest(int len, byte[] str) {
	int sum = 0;
	for (int i = 0; i < len; ++i)
	    sum ^= ( ((str[i]&0xf)<<4) | ((str[i]>>4)&0xf) );
	return (byte)sum;
    }

    public static byte digest1(byte sum, byte c) {
	return (byte)(sum ^ ( ((c&0xf)<<4) | ((c>>4)&0xf) ));
    }

    static public void main(String[] args) {
	byte[] str = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	byte sum = 0;
	for (int i = 0; i<str.length; ++i)
	    sum = digest1(sum, str[i]);
	byte sum2 = digest(str.length, str);
	System.out.println((int)(sum & 0xff));
	System.out.println((int)(sum2 & 0xff));
    }
}
