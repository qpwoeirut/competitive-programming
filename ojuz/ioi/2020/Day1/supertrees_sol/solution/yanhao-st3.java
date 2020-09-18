import java.util.ArrayList;
import java.util.Arrays;

class supertrees {
	int n;
	int construct(int[][] p) {
		n = p.length;
		boolean used[] = new boolean[n];
		int[][] b = new int[n][n];
		int[] parent = new int[n];
		for (int i=0; i<n; i++) {
			ArrayList<Integer> l = new ArrayList<>();
			if(!used[i]) {
				for(int j=0; j<n; j++) {
					if(p[i][j]==2) {
						l.add(j);
						used[i] = true;
						used[j] = true;
					}
				}
				if(l.size() == 1) return 0;
			
				if(l.size() >= 2) {
					for(int j=0; j+1<l.size(); j++) {
						b[l.get(j)][l.get(j+1)] = 1;
						b[l.get(j+1)][l.get(j)] = 1;
					}
					b[l.get(0)][i] = 1;
					b[i][l.get(0)] = 1;
					b[l.get(l.size()-1)][i] = 1;
					b[i][l.get(l.size()-1)] = 1;
				}
			}
		}
		
		for(int i=0; i<n; i++) {
			parent[i] = i;
		}
		
		for(int i=0; i<n; i++) {
			for(int j=0; j<i; j++) {
				if(p[i][j]==2) {
					parent[j] = i;
				}
			}
		}
		
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				if(p[i][j]==2 && parent[i]!=parent[j]) {
					return 0;
				}
				if(p[i][j]==0 && parent[i]==parent[j]) {
					return 0;
				}
			}
		}

		grader.build(b);
		return 1;
	}
}