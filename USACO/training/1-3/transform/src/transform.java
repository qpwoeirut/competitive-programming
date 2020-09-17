/*
ID: zhongbr1
LANG: JAVA
TASK: transform
 */

import java.io.*;
import java.util.*;

public class transform {
	static boolean[][] result = new boolean[10][10];
	static int size;
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("transform.in"));
		size = Integer.parseInt(fin.readLine());
		boolean[][] original = new boolean[10][10];
		boolean[][] reflected = new boolean[10][10];
		String line = new String();
		for (int i = 0; i < size; i++) {
			line = fin.readLine();
			for (int j = 0; j < size; j++) {
				if (line.charAt(j) == '@') {
					original[i][j] = false;
					reflected[i][size-j-1] = false;
				} else {
					original[i][j] = true;
					reflected[i][size-j-1] = true;
				}
			}
		}
		for (int i = 0; i < size; i++) {
			line = fin.readLine();
			for (int j = 0; j < size; j++) {
				if (line.charAt(j) == '@') {
					result[i][j] = false;
				} else {
					result[i][j] = true;
				}
			}
		}
		fin.close();

		byte ans = 7;

		if (check(original, false, true, true) == true) {
			ans = 1;
		}
		else if (check(original, true, true, false) == true) {
			ans = 2;
		}
		else if (check(original, true, false, true) == true) {
			ans = 3;
		}
		else if (Arrays.deepEquals(result, reflected)) {
			ans = 4;
		}
		else if (check(reflected, false, true, true) == true ||
				 check(reflected, true, true, false) == true ||
				 check(reflected, true, false, true) == true) {
			ans = 5;
		}
		
		else if (Arrays.deepEquals(original, result)) {
			ans = 6;
		}
		
		PrintStream fout = new PrintStream(new File("transform.out"));
		fout.println(ans);
		fout.close();
	}
	
	static boolean check(boolean pattern[][], boolean changeI, boolean changeJ, boolean swap) {
		boolean stop = false;
		for (int i=0; i<size; i++) {
			for (int j=0; j<size; j++) {
				if (swap) {
					if (pattern[changeJ ? size-j-1 : j][changeI ? size-i-1 : i] != result[i][j]) {
						stop = true;
//						break;
					}
				}
				else {
					if (pattern[changeI ? size-i-1 : i][changeJ ? size-j-1 : j] != result[i][j]) {
						stop = true;
//						break;
					}
				}
			}
		}
		
		return !stop;
	}
}