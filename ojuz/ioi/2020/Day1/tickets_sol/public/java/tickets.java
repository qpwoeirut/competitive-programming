public class tickets {
	long find_maximum(int k, int[][] x) {
		int n = x.length;
		int m = x[0].length;
		int[][] answer = new int[n][m];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (j < k) {
					answer[i][j] = j;
				} else {
					answer[i][j] = -1;
				}
			}
		}
		grader.allocate_tickets(answer);
		return 1;
	}

}

