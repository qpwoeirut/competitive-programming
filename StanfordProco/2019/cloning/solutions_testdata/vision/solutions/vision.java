/* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
public class vision
{
	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int r = Integer.parseInt(in.readLine());
		
		for (int i = 0; i < r; i++) {
			long n = 1;
			long m = 1;
			long x = Long.parseLong(in.readLine());
			for (long j = 2; j * j * j <= x; j++) {
				long base = 1;
				if (x % (j * j * j) == 0) {
					int cnt = 0;
					while (x % j == 0) {
						x /= j;
						cnt++;
						if (cnt % 3 == 0) {
							base *= j;
						}
					}
					assert(cnt >= 3);
					if (cnt % 3 == 0) {
						n *= base;
					} else if (cnt % 3 == 1) {
						n *= base * j;
						m *= j;
					} else {
						n *= base * j * j;
						m *= j * j;
					}
				}
			}
			if (n == 1) {
				n = x * 4;
				m = x * 8;
			} else {
				n *= x;
				m *= x;
			}
			System.out.println(n + " " + m);
		}
		
	}
}
