/*
ID: zhongbr1
TASK: namenum
LANG: JAVA
 */

import java.io.*;
import java.util.*;

public class namenum {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("namenum.in"));
		String num = fin.readLine();
		fin.close();
		
		BufferedReader nameFile = new BufferedReader(new FileReader("dict.txt"));
		TreeSet<String> names = new TreeSet<String> ();
		String tmp;
		boolean valid;
		while (nameFile.ready()) {
			valid = true;
			tmp = nameFile.readLine();
			if (tmp.length() == num.length()) {
				System.out.println(tmp);
				for (int i=0; i<tmp.length(); i++) {
					if (check(Character.getNumericValue(num.charAt(i)), tmp.charAt(i)) == false) {
						valid = false;
						break;
					}
				}
				if (valid) {
					names.add(tmp);
				}
			}
		}
		nameFile.close();
		
		PrintStream fout = new PrintStream(new File("namenum.out"));
		if (names.size() == 0) {
			fout.println("NONE");
		}
		else {
			for (String name: names) {
				fout.println(name);
			}
		}
		
		
	}
	static boolean check(int digit, char c) {
		double asciiVal = c;
		asciiVal -= 64;
		if (asciiVal >= 17) {
			asciiVal--;
		}
		
		System.out.println("Digit, c, asciiVal/3, val: " + digit + ", " + c + ", " + asciiVal/3 + ", " + Math.ceil(asciiVal / 3));
		if (digit-1 == Math.ceil(asciiVal / 3)) {
			System.out.println("true");
			return true;
		}
		System.out.println("false");
		return false;
	}
}
