/*
ID: zhongbr1
TASK: palsquare
LANG: JAVA
 */

import java.io.*;

public class palsquare {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("palsquare.in"));
		int base = Integer.parseInt(fin.readLine());
		fin.close();
		
		PrintStream fout = new PrintStream(new File("palsquare.out"));
		String converted;
		for (int i=1; i<=300; i++) {
			converted = Integer.toString(i*i, base);
			if (isPalin(converted)) {
				fout.println(Integer.toString(i, base).toUpperCase() + " " + converted.toUpperCase());
			}
		}
		fout.close();
	}
	
	static boolean isPalin(String str) {
		for (int i=0; i<Math.floor(str.length()); i++) {
			if (str.charAt(i) != str.charAt(str.length() - i - 1)) {
				return false;
			}
		}
		return true;
	}
}