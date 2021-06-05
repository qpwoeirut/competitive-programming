import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Iterator;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.TreeMap;
import java.util.TreeSet;

public class blackwidow {
	static int n, m;
	static Map<Integer, Double> a;
	static TreeSet<Integer> keys;
	public static void main (String[] args) throws java.lang.Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(in.readLine());
		PrintWriter out = new PrintWriter(System.out);
		a = new TreeMap<Integer, Double>();
		keys = new TreeSet<Integer>();
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(in.readLine());
		for(int i = 1; i <= n; i++) {
			a.put(i, 1.0*Integer.parseInt(st.nextToken()));
			keys.add(i);
		}
//		long s = System.currentTimeMillis();
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(in.readLine());
			int l = Integer.parseInt(st.nextToken());
			int r = Integer.parseInt(st.nextToken());
			//System.out.println("Query: " + l+" "+r);
			double sum = 0;
			Iterator<Integer> it = keys.tailSet(l).iterator();
			while (it.hasNext()) {
				Integer x = it.next();
				if (x > r) break;
				sum += a.get(x);
				it.remove();
				a.remove(x);
			}
			//System.out.println(sum);
			if (l == r) a.put(l, sum);
			else {
				a.put(l, sum * 0.5);
				a.put(r, sum * 0.5);
			}
			//System.out.println(a);
			keys.add(l);
			keys.add(r);
		}
//		long e = System.currentTimeMillis();
//		System.out.println(e-s);
		for(int i = 1; i <= n; i++) {
			if (a.keySet().contains(i)) {
				out.printf("%.7f ", a.get(i));
			} else {
				out.printf("0.0 ");
			}
		}
		out.close();
	}
}
