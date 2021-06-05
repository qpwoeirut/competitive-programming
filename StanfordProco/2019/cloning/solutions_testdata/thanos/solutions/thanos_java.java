import java.util.Scanner;

public class thanos {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
		int n = in.nextInt();
		int [] t = new int[n];
		for (int i = 0; i < t.length; i++) {
			t[i] = in.nextInt();
		}
		
		//compute each D
		frac [] d = new frac[n-1];
		for (int i = 0; i < d.length; i++) {
			long num = t[0] * t[i+1];
			long denom = Math.abs(t[i+1] - t[0]);
			long g = gcd(num, denom);
			num/=g;
			denom/=g;
			d[i] = new frac(num, denom);
		}
		
		//now take the lcm of the list
		//lcm(a/b, p/q) = lcm(a,p)/gcd(b,q)
		
		frac res = d[0];
		for (int i = 1; i < d.length; i++) {
			long newnum = lcm(res.numer, d[i].numer);
			long newdenom = gcd(res.denom, d[i].denom);
			res = new frac(newnum, newdenom);
		}
		
		//let's make sure our fraction is simplified
		long g = gcd(res.numer, res.denom);
		System.out.println(res.numer/g + " " + (res.denom/g));
		
	}
	public static long gcd(long a, long b) {
		return b == 0L ? a : gcd(b, a % b);
	}
	public static long lcm(long a, long b) {
		return (a * b) / gcd(a, b);
	}
	static class frac{
		long numer;
		long denom;
		public frac(long a, long b) {
			numer = a;
			denom = b;
		}
	}
}
