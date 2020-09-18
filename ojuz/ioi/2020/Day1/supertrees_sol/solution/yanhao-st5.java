import java.util.ArrayList;
import java.util.Arrays;

class supertrees {
	int n;
	int construct(int[][] p) {
		n = p.length;
		ArrayList<ArrayList<Integer>> components1 = new ArrayList<>();
		ArrayList<ArrayList<Integer>> components2 = new ArrayList<>();
		for(int i=0; i<n; i++) components1.add(new ArrayList<>());
		for(int i=0; i<n; i++) components2.add(new ArrayList<>());

		int[] parent1 = new int[n];
		int[] parent2 = new int[n];
		for(int i=0; i<n; i++) {
			parent1[i] = i;
			parent2[i] = i;
		}
		
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				if(p[i][j]==1) {
					parent1[i] = j;
					components1.get(j).add(i);
					break;
				}
			}
		}
		for(int i=0; i<n; i++) {
			if(parent1[i]!=i) continue;
			for(int j=0; j<n; j++) {
				if(parent1[j]!=j) continue;
				if(p[i][j]==2 || i==j) {
					parent2[i] = j;
					components2.get(j).add(i);
					break;
				}
			}
		}
		int[][] b = new int[n][n];
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				b[i][j] = 0;
			}
		}
		for(int i=0; i<n; i++) {
			ArrayList<Integer> cmp = components1.get(i);
			// impossiblility check for 1s
			for(int j=1; j<cmp.size(); j++) {
				if(!Arrays.equals(p[cmp.get(j)], p[cmp.get(0)])) {
					return 0;
				}
				b[cmp.get(j)][cmp.get(0)] = 1;
				b[cmp.get(0)][cmp.get(j)] = 1;
			}
			// impossibility check for 2s
			cmp = components2.get(i);
			if(cmp.size()==2) {
				return 0;
			}
			if(cmp.size()<2) continue;
			for(int j=0; j<cmp.size(); j++) {
				for(int k=0; k<j; k++) {
					if(p[cmp.get(j)][cmp.get(k)]!=2) {
						return 0;
					}
				}
			}
			for(int j=1; j<cmp.size(); j++) {
				b[cmp.get(j)][cmp.get(j-1)] = 1;
				b[cmp.get(j-1)][cmp.get(j)] = 1;
			}
			b[cmp.get(0)][cmp.get(cmp.size()-1)] = 1;
			b[cmp.get(cmp.size()-1)][cmp.get(0)] = 1;
		}
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				if(p[i][j]==1 && parent1[i]!=parent1[j]) return 0;
				if(p[i][j]==2 && parent2[parent1[i]]!=parent2[parent1[j]]) return 0;
			}
		}
		grader.build(b);
		return 1;
	}
}