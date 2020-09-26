public class stations {
  int[] label(int n, int k, int[] u, int[] v) {
  	int[] labels = new int[n];
  	for (int i = 0; i < n; i++) {
  	  labels[i] = i;
  	}
  	return labels;
  }

  int find_next_station(int s, int t, int[] c) {
    return c[0];
  }
}
