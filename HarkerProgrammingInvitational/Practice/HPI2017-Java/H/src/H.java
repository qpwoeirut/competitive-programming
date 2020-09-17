import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class H {
	static final int[] chr = { 1, 1, 1, 0, 0, -1, -1, -1 };
	static final int[] chc = { 1, 0, -1, 1, -1, 1, 0, -1 };
	static boolean input[][];

	static ArrayList<Integer> size = new ArrayList<Integer>();
	int d = 0;

	static int floodFill(int x, int y, int currentCluster) {
		int ret = 1;
		if (x < 0 || x >= input.length || y < 0 || y >= input[0].length || !input[x][y]) {
			return 0;
		}
		input[x][y] = false;

		for (int i = 0; i < 8; i++) {
			ret += floodFill(x + chr[i], y + chc[i], currentCluster);
		}
		return ret;
	}

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);

		int C = s.nextInt();
		int R = s.nextInt();
		input = new boolean[R][C];
		for (int i = 0; i < R; i++) {
			String d = s.next();
			for (int j = 0; j < C; j++) {
				if (d.toCharArray()[j] != 'x') {
					input[i][j] = false;
				} else {
					input[i][j] = true;
				}
			}
		}

		int currentCluster = 0;
		for (int x = 0; x < input.length; x++) {
			for (int y = 0; y < input[0].length; y++) {
				if (input[x][y]) {
					size.add(floodFill(x, y, currentCluster));
					currentCluster++;
				}
			}
		}
		System.out.println(size.size());
		Collections.sort(size);
		for (int i = size.size() - 1; i >= 0; i--) {
			System.out.println(size.get(i));
		}
	}
}