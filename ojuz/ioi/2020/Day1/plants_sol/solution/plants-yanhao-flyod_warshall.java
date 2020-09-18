import java.util.*;

class plants {
	final int n_max = 310;
	boolean[][] adj = new boolean[n_max][n_max];
	int[] permutation = new int[n_max];
	boolean[] visited = new boolean[n_max];
	int[] lt = new int[n_max];
	int[] rg = new int[n_max];

	void init(int k, int[] r) {
		int n = r.length;
		for(int i=0; i<n; i++) {
			lt[i] = -1;
			rg[i] = -1;
		}
		for(int i=0; i<n; i++) {
			int streak = -n-1;
			for(int j=n-1; j>=0; j--) {
				if(r[j]==0) {
					streak = 0;
				} else {
					streak++;
				}
				if(streak==k-1) {
				   for(int l=j; l<j+k-1; l++) {
						r[l]--;
				   }
				   r[j+k-1] = 1<<20;
				   permutation[j+k-1] = i;
				   break;
				}
				if(j==0) {
					for(int l=0; l<=streak; l++) {
						r[l]--;
					}
					for(int l=n-k+streak+1; l<n; l++) {
						r[l]--;
					}
					r[streak] = 1<<20;
					permutation[streak] = i;
				}
			}
		}

		for(int i=0; i<n; i++) {
			for(int j=(i+n-k+1)%n; j!=i; j=(j+1)%n) {
				if(permutation[i]<permutation[j]) {
					adj[i][j] = true;
				} else {
					adj[j][i] = true;
				}
			}
		}

		for(int l=0; l<n; l++) {
			for(int i=0; i<n; i++) {
				for(int j=0; j<n; j++) {
					adj[i][j] = adj[i][j] || (adj[i][l] && adj[l][j]);
				}
			}
		}
	}

	int compare_plants(int x, int y) {
		if(adj[x][y]) return 1;
		if(adj[y][x]) return -1;
		return 0;
	}
}
