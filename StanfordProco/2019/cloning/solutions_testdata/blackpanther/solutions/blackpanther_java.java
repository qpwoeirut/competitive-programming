import java.util.ArrayList;
import java.util.Scanner;

public class blackpanther {
	public static double bestVal = Integer.MIN_VALUE/3;
	public static char [] operations;
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
		int n = in.nextInt();
		int [] nums = new int[n];
		operations = new char[n];
		
		for (int i = 0; i < nums.length; i++) {
			nums[i] = in.nextInt();
		}
		//clear the buffer
		in.nextLine();
		
		//read in operations
		operations = in.nextLine().replaceAll(" ", "").toCharArray();
		
		int [] perm = new int[n];
		boolean [] used = new boolean[n];
		int on = 0;
		go(perm, nums, used, on);
		
		System.out.printf("%.6f \n",bestVal);		
	}
	public static void go(int[] perm, int [] vals, boolean[] used, int k) {
		if (k == perm.length) {
			//compute our current result
			double curRes = perm[0];
			int pos = 1;
			String prevop = "";
			boolean flag = true;
			for (int i = 0; i < operations.length && pos < perm.length; i++, pos++) {
				if(prevop.equals("/")) {
					if(perm[pos] == 0) flag = false;
				}
				if (operations[i] == '+') {
					curRes += perm[pos];
				}
				else if (operations[i] == '-') {
					curRes -= perm[pos];
				}
				else if (operations[i] == '/') {
					curRes /= perm[pos];
				}
				else if (operations[i] == '*') {
					curRes *= perm[pos];
				}
			}

			//update our answer if we need to
			if(flag) bestVal = Math.max(bestVal, curRes);
			return;
		}
		for (int i=0; i<perm.length; i++) {
			if (!used[i]) {
				perm[k] = vals[i];
				used[i] = true;
				go(perm, vals, used, k+1);
				used[i] = false;
			}
		}
	}
}
