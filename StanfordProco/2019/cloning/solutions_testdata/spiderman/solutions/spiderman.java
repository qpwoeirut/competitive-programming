/* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
public class spiderman
{
	static int n, k, a[], prev[];
	static long f1[], f2[];
	static HashMap<Integer, Integer> idx;
	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(in.readLine());
		n = Integer.parseInt(st.nextToken());
		k = Integer.parseInt(st.nextToken());
		a = new int[n+1];
		prev = new int[n+1];
		f1 = new long[n+1];
		f2 = new long[n+1];
		idx = new HashMap<Integer, Integer>();
		st = new StringTokenizer(in.readLine());
		for (int i = 1; i <= n; i++) {
			a[i] = Integer.parseInt(st.nextToken());
			if (idx.keySet().contains(a[i])) {
				prev[i] = idx.get(a[i]);
			} else {
				prev[i] = -1;
			}
			idx.put(a[i], i);
		}
		for (int i = 1; i <= k; i++) {
			for (int j = 1; j <= n; j++) {
				f1[j] = Math.max(f1[j-1], f1[j]);
			}
			for (int j = 1; j <= n; j++) {
				long x = (prev[j] <= 0) ? 0 : f2[prev[j]];
				f2[j] = 1 + Math.max(f1[j-1], x);
			}
			for (int j = 1; j <= n; j++) {
				f1[j] = f2[j];
			}
		}
		long ans = 0;
		for (int i = 0; i <= n; i++) {
			ans = Math.max(ans, f1[i]);
		}
		System.out.println(n - ans);
		
	}
}
