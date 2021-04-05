public class scales {
	public void init(int T) {
	}

	public void orderCoins() {
		int[] W = new int[6];
		for (int i = 0; i < 6; i++) {
			W[i] = i + 1;
		}
		grader.lib.answer(W);
	}
}