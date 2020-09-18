class plants {
	int[] prefix_sum;
	int n;
	void init(int k, int[] r) {
		n = r.length;
		prefix_sum = new int[n+1];
		prefix_sum[0] = 0;
		for(int i=0; i<n; i++) {
			prefix_sum[i+1] = prefix_sum[i] + r[i];
		}
	}

	int compare_plants(int x, int y) {
		if(x>y) return -compare_plants(y,x);
		if(prefix_sum[x]==prefix_sum[y]) return 1;
		if(prefix_sum[y]==prefix_sum[n] && prefix_sum[0]==prefix_sum[x]) return -1;
		if(prefix_sum[x]-x==prefix_sum[y]-y) return -1;
		if(prefix_sum[y]-y==prefix_sum[n]-n && prefix_sum[0]==prefix_sum[x]-x) return 1;
		return 0;
	}
}
