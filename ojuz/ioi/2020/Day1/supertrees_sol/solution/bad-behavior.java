public class supertrees {

	private void build(int[][] b) {
		grader.build(b);
	}

	int construct(int[][] p) {
		int n = p.length;
		if (n == 4) {
			return 2;
		}
		if (n == 2 && p[0][1] == 0) {
			return 1;
		}
		if (n == 2 && p[0][1] == 3) {
			build(p);
			return 0;
		}
		if (n == 5) {
			build(p);
			build(p);
			return 0;
		}
		if (n == 10) {
			p = new int[n+1][n];
			build(p);
			return 0;
		}
		if (n == 200) {
			p = new int[n][n+1];
			build(p);
			return 0;
		}
		return -1;
	}
}
