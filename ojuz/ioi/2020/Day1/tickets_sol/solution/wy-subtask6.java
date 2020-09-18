class tickets {
	int c,k,s;

	long find_maximum(int _k, int[][] d) {
		k = _k;
		c = d.length;
		s = d[0].length;

		int[] plus = new int[c];
		// for ck/2 times, promote the one with the largest sums
		for(int i=0; i<c*k/2; i++) {
			int best = -1;
			long best_sum = 0;
			for(int j=0; j<c; j++) {
				if(plus[j] < k && d[j][k-1-plus[j]] + d[j][s-1-plus[j]] > best_sum) {
					best_sum = d[j][k-1-plus[j]] + d[j][s-1-plus[j]];
					best = j;
				}
			}
			plus[best]++;
		}
		
		long ans = 0;
		
		int minus_day = 0;
		int plus_day = c*k-1;
		int[][] ret = new int[c][s];

		for(int i=c-1; i>=0; i--) {
			for(int j=0; j<k-plus[i]; j++) {
				ret[i][j] = minus_day % k;
				minus_day++;
				ans -= d[i][j];
			}
			for(int j=k-plus[i]; j<s-plus[i]; j++) {
				ret[i][j] = -1;
			}
			for(int j=s-plus[i]; j<s; j++) {
				ret[i][j] = plus_day % k;
				plus_day--;
				ans += d[i][j];
			}
		}

		grader.allocate_tickets(ret);
		return ans;
	}
}
