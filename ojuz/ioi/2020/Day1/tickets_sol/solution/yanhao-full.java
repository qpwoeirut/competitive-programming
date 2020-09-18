class tickets {
	int c,k,s;

	int count_lower(int[] x, int target) {
		int low = -1;
		int high = x.length;
		while(high-low>1) {
			int mid = (low+high)/2;
			if(x[mid] < target) {
				low = mid;
			} else {
				high = mid;
			}
		}
		return high;
	}
	
	int count = 0;
	int get_median(int[][] arr) {
		int low = -1;
		int high = (int)2e9;
		int target = -1;
		int bigger = 0;
		int smaller = 0;
		while(high-low>1) {
			smaller = 0;
			bigger = 0;
			target = low + (high-low)/2;
			for(int i=0; i<arr.length; i++) {
				smaller += count_lower(arr[i], target);
				bigger += count_lower(arr[i], target+1);
			}
			if(smaller > c*k/2) {
				high = target;
			} else if(bigger < c*k/2) {
				low = target;
			} else {
				break;
			}
		}
		count = smaller; 
		return target;
	}
	
	long find_maximum(int _k, int[][] d) {
		k = _k;
		c = d.length;
		s = d[0].length;
		int[][] sums = new int[c][k];
		for(int i=0; i<c; i++) {
			for(int j=0; j<k; j++) {
				sums[i][j] = d[i][j] + d[i][s-k+j];
			}
		}
		int median = get_median(sums);
		long ans = 0;
		
		int minus_day = 0;
		int plus_day = c*k-1;
		int[][] ret = new int[c][s];

		for(int i=0; i<c; i++) {
			int j=0;
			for(;j<k && sums[i][j]<median; j++) {
				ret[i][j] = minus_day % k;
				minus_day++;
				ans -= d[i][j];
			}
			for(;j<k && sums[i][j] == median && count < c*k/2; j++) {
				ret[i][j] = minus_day % k;
				minus_day++;
				count++;
				ans -= d[i][j];	
			}
			for(int l=j; l<s-k+j; l++) {
				ret[i][l] = -1;
			}
			for(j=s-k+j; j<s; j++) {
				ret[i][j] = plus_day % k;
				plus_day--;
				ans += d[i][j];
			}
		}

		grader.allocate_tickets(ret);
		return ans;
	}
}