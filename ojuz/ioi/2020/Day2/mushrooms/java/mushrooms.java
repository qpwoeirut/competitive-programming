public class mushrooms {

	public int count_mushrooms(int n) {
		int[] m = new int[n];
		for (int i = 0; i < n; i++)
			m[i] = i;
		int c1 = stub.use_machine(m);
		m = new int[] {0, 1};
		int c2 = stub.use_machine(m);
		return c1+c2;
	}
}
