class tickets {
	long find_maximum(int _k, int[][] d) {
		int c = d.length;
		int s = d[0].length;
		int[][] ret = new int[c][s];

		for(int i=0; i<c; i++) {
			for(int j=0; j<s; j++) {
				ret[i][j] = -1;
			}
		}
		grader.allocate_tickets(ret);
		return 0;
	}
}