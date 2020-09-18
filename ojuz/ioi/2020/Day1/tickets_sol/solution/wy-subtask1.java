import java.util.Arrays;

class tickets {

	long find_maximum(int k, int[][] d) {
		int c = d.length;
		int[] values = new int[c];
		
		for (int i = 0; i < c; i++) {
			values[i] = d[i][0];
		}
		Arrays.sort(values);
		long ans = 0;
		for (int i = 0; i < c; i++) {
			ans += Math.abs(values[values.length / 2] - values[i]);
		}
		
		int[][] answer = new int[c][1];
		for (int i = 0; i < c; i++) {
			answer[i][0] = 0;
		}
		grader.allocate_tickets(answer);
		return ans;
	}
}
