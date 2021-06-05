 /* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

public class titan
{
	static int n;
	static double x[], y[], z[];
	static Double minH[][];
	static double eps = 1e-6;
	static TreeMap<Double, Integer> edges;
	static int p[], r[];
	public static void main (String[] args) throws java.lang.Exception
	{
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.parseInt(in.readLine());
		minH = new Double[n][n];
		x = new double[n];
		y = new double[n];
		z = new double[n];
		p = new int[n];
		r = new int[n];
		for (int i = 0; i < n; i++) p[i] = i;
		edges = new TreeMap<Double, Integer>();
		for (int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			double a = Math.toRadians(Double.parseDouble(st.nextToken()));
			//System.out.println(Math.toDegrees(a));
			String ns = st.nextToken();
			if (ns.equals("N")) {
				z[i] = Math.sin(a);
			} else {
				z[i] = -Math.sin(a);
			}
			double b = Math.toRadians(Double.parseDouble(st.nextToken()));
			String ew = st.nextToken();
			if (ew.equals("E")) {
				x[i] = Math.sin(b) * Math.cos(a);
				y[i] = Math.cos(b) * Math.cos(a);
			} else {
				x[i] = -Math.sin(b) * Math.cos(a);
				y[i] = Math.cos(b) * Math.cos(a);
			}
			//System.out.println(x[i] + " " + y[i] + " " + z[i]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				double dot = x[i] * x[j] + y[i] * y[j] + z[i] * z[j];
				double ang = Math.acos(dot);
				if (ang <= eps) {
					minH[i][j] = Double.MAX_VALUE;
				} else {
					minH[i][j] = 1.0/Math.cos(ang/2.0);
				}
				edges.put(minH[i][j], i*n + j);
			}
		}
		int cmp = n;
		for (double d : edges.keySet()) {
			int enc = edges.get(d);
			int i = enc/n;
			int j = enc%n;
			if (find(i) != find(j)) {
				merge(i,j);
				cmp--;
			}
			if (cmp == 1) {
				System.out.println(d-1);
				return;
			}
		}
		//System.out.println(minH[1][2]);
	}
	static int find(int x) {
		if (x != p[x]) {
			p[x] = find(p[x]);
		}
		return p[x];
	}
	
	static void merge(int x, int y) {
		int px = p[x];
		int py = p[y];
		if (r[px] > r[py]) p[py] = px;
		else p[px] = py;
		if (r[px] == r[py]) r[py]++;
	}
}
