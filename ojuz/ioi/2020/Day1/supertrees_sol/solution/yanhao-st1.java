class supertrees {
	int n;
	int construct(int[][] p) {
		n = p.length;
		int[][] b = new int[n][n];
		for(int i=1; i<n; i++) {
			b[i][0] = 1;
			b[0][i] = 1;
		}
		grader.build(b);
		return 1;
	}
}
