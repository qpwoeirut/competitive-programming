/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
	public static int findWidestMountain(int n, int[] arr) {
		return 0;
	}

	public static void main(String[] args) throws Exception {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.valueOf(reader.readLine()); // read # of test cases
		
		for (int i = 0; i < t; i++) {
			int length = Integer.valueOf(reader.readLine()); // read length of array
			int[] arr = new int[length];
			String input = reader.readLine(); // read array
			String[] str = input.split(" ");
			for (int a = 0; a < length; a++) {
				arr[a] = Integer.valueOf(str[a]);
			}
			int output = findWidestMountain(length, arr);
			System.out.println(output);
		}

	}
}
