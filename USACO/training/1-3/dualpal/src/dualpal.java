
/*
ID: zhongbr1
TASK: dualpal
LANG: JAVA
 */

import java.io.*;
import java.util.*;

public class dualpal {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("dualpal.in"));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int remaining = Integer.parseInt(st.nextToken());
		int cur = Integer.parseInt(st.nextToken()) + 1;
		fin.close();

		PrintStream fout = new PrintStream(new File("dualpal.out"));

		int palinsFound;
		while (remaining > 0) {
			palinsFound = 0;
			for (int base = 2; base <= 10 && palinsFound < 2; base++) {
				if (isPalin(Integer.toString(cur, base)) == true) {
					palinsFound++;
					System.out.println(cur + " " + Integer.toString(cur, base) + " " + base);
				}
			}

			if (palinsFound >= 2) {
				fout.println(cur);
				remaining--;
			}
			cur++;
		}
	}

	static boolean isPalin(String str) {
		for (int i = 0; i < Math.floorDiv(str.length(), 2); i++) {
			if (str.charAt(i) != str.charAt(str.length() - i - 1)) {
				return false;
			}
		}
		return true;
	}
}
