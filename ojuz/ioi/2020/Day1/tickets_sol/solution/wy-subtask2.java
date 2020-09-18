import java.util.Arrays;

class tickets {
	long[] diffs;
	int[] picked;
	
	long combine(int x, int y) {
		return (((long)x << 32) | y);
	}
	int getx(long a) {
		return (int)(a>>32);
	}
	int gety(long a) {
		return (int)(a&((1<<31)-1));
	}
	
	long find_maximum(int k, int[][] d) {
		int c = d.length;
		int s = d[0].length;
		diffs = new long[c];
		picked = new int[c];
		
		for (int i = 0; i < c; i++) {
			diffs[i] = combine(d[i][0] + d[i][s-1], i);
		}
		Arrays.sort(diffs);
		for (int i = 0; i < c; i++) {
			if (i < c/2) {
				picked[gety(diffs[i])] = 0;
			} else {
				picked[gety(diffs[i])] = s-1;
			}
		}
		
		long ans = 0;
		for (int i = 0; i < c; i++) {
			ans += Math.abs(d[i][picked[i]] - getx(diffs[c/2])/2);
		}
		
		int[][] answer = new int[c][s];
		for(int i=0; i<c; i++) {
			for(int j=0; j<s; j++) {
				answer[i][j] = -1;
			}
			answer[i][picked[i]] = 0;
		}
		
		grader.allocate_tickets(answer);
		return ans;
	}
}
