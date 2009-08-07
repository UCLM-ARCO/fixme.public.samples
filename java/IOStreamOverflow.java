import java.io.*;

class IOStreamOverflow {
    static public void main(String[] args) {
	try {
	    FileOutputStream out = new FileOutputStream("/tmp/kk");
	    out.write((byte)250);
	    out.write((byte)-1);
	    out.write((byte)127);
	    out.close();

	    FileInputStream in = new FileInputStream("/tmp/kk");
	    for (;;) {
		int ret = in.read();
		if (ret < 0)
		    break;
		System.out.println((byte)ret);
	    }
	}
	catch(Exception e) {
	}
    }
};
