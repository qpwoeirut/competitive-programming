class supertrees {
	int n;
	int construct(int[][] p) {
		n = p.length;
		boolean used[] = new boolean[n];
		int[][] b = new int[n][n];
		int[] parent = new int[n];
		
		for(int i=0; i<n; i++) {
			parent[i] = i;
		}
		
		for(int i=0; i<n; i++) {
			for(int j=0; j<i; j++) {
				if(p[i][j]==1) {
					parent[j] = i;
				}
			}
		}
		
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				if(p[i][j]==1 && parent[i]!=parent[j]) {
					return 0;
				}
				if(p[i][j]==0 && parent[i]==parent[j]) {
					return 0;
				}
			}
		}

		for(int i=0; i<n; i++) {
			if(parent[i]!=i) {
				b[i][parent[i]] = 1;
				b[parent[i]][i] = 1;
			}
		}
		grader.build(b);
		return 1;
	}
}
