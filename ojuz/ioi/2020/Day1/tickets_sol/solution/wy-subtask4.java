import java.util.Arrays;

class tickets {
	int c,s;
	int count = 0; // how many times does the median appear in the first half of array
	int get_median(int[][] arr) {
		int[] sorted = new int[c*s];
		for(int i=0; i<c; i++) {
			for(int j=0; j<s; j++) {
				sorted[i*s+j] = arr[i][j];
			}
		}
		Arrays.sort(sorted);
		for(int a=0; a<c*s/2; a++) {
			if(sorted[a] == sorted[c*s/2]) count++;
		}
		return sorted[c*s/2];
	}
	
	long find_maximum(int _k, int[][] d) {
		c = d.length;
		s = d[0].length;

		int median = get_median(d);
		long ans = 0;
		
		int minus_day = 0;
		int plus_day = c*s-1;
		int[][] ret = new int[c][s];
		
		for(int i=0; i<c; i++) {
			for(int j=0; j<s; j++) {
				ret[i][j] = -1;
			}
		}
		
		for(int i=0; i<c; i++) {
			for(int j=0; j<s; j++) {
				if(d[i][j]<median) {
					ret[i][j] = minus_day % s;
					minus_day++;
					ans -= d[i][j];
				}
				if(d[i][j]==median && count>0) {
					ret[i][j] = minus_day % s;
					minus_day++;
					ans -= d[i][j];
					count--;
				}
			}
			for(int j=0; j<s; j++) {
				if(d[i][j]>=median && ret[i][j]==-1) {
					ret[i][j] = plus_day % s;
					plus_day--;
					ans += d[i][j];
				}
			}
		}
		grader.allocate_tickets(ret);
		return ans;
	}
}