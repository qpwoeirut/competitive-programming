/* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

public class scarletwitch
{
	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(in.readLine());
		String t = in.readLine();
		StringBuilder sb = new StringBuilder();
		sb.append('0');
		sb.append(t.charAt(0));
		for (int i = 1; i < n; i++) {
			if (t.charAt(i) != t.charAt(i-1)) {
				sb.append(t.charAt(i));
			}
		}
		sb.append('1');
		String s = sb.toString();
		int cnt = 0;
		for (int i = 1; i < s.length()-1; i++) {
			if (s.charAt(i) == '1' && s.charAt(i-1) == '0' && s.charAt(i+1) == '0') {
				cnt++;
			}
		}
		System.out.println(cnt);
	}
}
