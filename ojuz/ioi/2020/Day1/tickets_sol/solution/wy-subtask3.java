class tickets {
	long find_maximum(int k, int[][] d) {
		int c = d.length;
		int s = d[0].length;
		int[][] ret = new int[c][s];

		int minus_day = 0;
		int plus_day = c*k-1;
		int ans = 0;
		int usable0 = 0;
		int usable1 = 0;
		int[] num1 = new int[c];
		int[] num0 = new int[c];
		for (int i = 0; i < c; i++) {
			num1[i] = 0;
			for (int j = 0; j < s; j++) {
				num1[i] += d[i][j];
			}
			num0[i] = Math.min(k, s - num1[i]);
			num1[i] = Math.min(k, num1[i]);
			usable0 += num0[i];
			usable1 += num1[i];
		}
		
		ans = Math.min(c*k/2, Math.min(usable0, usable1));
		if (usable0 < c*k/2) {
			for (int i=0; i<c; i++) {
				num1[i] = k - num0[i];
			}
		} else if (usable1 < c*k/2) {
			for (int i=0; i<c; i++) {
				num0[i] = k - num1[i];
			}
		} else {
			int excess = usable1-c*k/2;
			for (int i=0; i<c; i++) {
				int decr = Math.min(excess, num1[i]+num0[i]-k);
				num1[i] -= decr;
				excess -= decr;
				num0[i] = k - num1[i];
			}
		}
		for(int i=0; i<c; i++) {
			for (int j=0; j<s; j++) {
				if(d[i][j]==1 && num1[i]>0) {
					ret[i][j] = plus_day % k;
					plus_day--;
					num1[i]--;
				} else if(d[i][j]==0 && num0[i]>0) {
					ret[i][j] = minus_day % k;
					minus_day++;
					num0[i]--;
				} else {
					ret[i][j] = -1;
				}
			}
		}
		
		grader.allocate_tickets(ret);
		return ans;
	}
}
