class Pack {
    static public void main(String[] args) {
	// unpacking example
	byte[] b = {-2, -1, -1, -1};
	int i = (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | (b[0] << 0);
	System.out.println(Integer.toHexString(i));

	// packing example
	byte[] u = {0, 0, 0, 0};
	u[0] = (byte)((i>>0) );
	u[1] = (byte)((i>>8) );
	u[2] = (byte)((i>>16));
	u[3] = (byte)((i>>24));
	System.out.println(u[0]);
	System.out.println(u[1]);
	System.out.println(u[2]);
	System.out.println(u[3]);
    }
}
