class tickets {
	long find_maximum(int k, int[][] d) {
		int c = d.length;
		int s = d[0].length;
		long[][] dp = new long[c][c*k+1];
		long[][] rewards = new long[c][k+1];
		for(int i=0; i<c; i++) {
			rewards[i][0] = 0;
			for(int j=0; j<k; j++) {
				rewards[i][0] -= d[i][j];
			}
			for(int j=1; j<=k; j++) {
				rewards[i][j] = rewards[i][j-1] + d[i][s-j]
								+ d[i][k-j];
			}
		}
		for(int i=0; i<c; i++) {
			for(int l=0; l<=c*k; l++) {
				dp[i][l] = (long)(-1e18);
			}
		}
		int[][] from = new int[c][c*k/2+1];
		for(int j=0; j<=k; j++) {
			dp[0][j] = rewards[0][j];
			from[0][j] = j;
		}
		for(int i=1; i<c; i++) {
			for(int j=0; j<=k; j++) {
				for(int l=0; l+j<=c*k/2; l++) {
					if(dp[i-1][l] + rewards[i][j] > dp[i][l+j]) {
						dp[i][l+j] = dp[i-1][l] + rewards[i][j];
						from[i][l+j] = j;
					}
				}
			}
		}
		int[][] ret = new int[c][s];
		for(int i=0; i<c; i++) {
			for(int j=0; j<s; j++) {
				ret[i][j] = -1;
			}
		}
		int current = c*k/2; // the dp state
		int minus_day = 0;
		int plus_day = c*k-1;
		for(int i=c-1; i>=0; i--) {
			for(int j=0; j<k-from[i][current]; j++) {
				ret[i][j] = minus_day % k;
				minus_day++;
			}
			for(int j=s-from[i][current]; j<s; j++) {
				ret[i][j] = plus_day % k;
				plus_day--;
			}
			current -= from[i][current];
		}
		grader.allocate_tickets(ret);
		return dp[c-1][c*k/2];
	}
}
