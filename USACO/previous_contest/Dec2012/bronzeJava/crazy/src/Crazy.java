
/*
 *  Looked at solution
 *  Copied ideas
 */

import java.io.*;
import java.util.*;

class Item {
	int x, y;
	int group;

	Item(int x, int y) {
		this.x = x;
		this.y = y;
	}
}

public class Crazy {
	public static void main(String[] args) throws IOException {
		Scanner sc = new Scanner(new File("crazy.in"));
		int fenceCount = sc.nextInt();
		int cowCount = sc.nextInt();

		int[] fencePosX = new int[fenceCount * 2];
		int[] fencePosY = new int[fenceCount * 2];
		LinkedList<Integer> sortedPosX = new LinkedList<Integer>();
		LinkedList<Integer> sortedPosY = new LinkedList<Integer>();
		sortedPosX.add(0); // Add 2 extra rows and columns
		sortedPosX.add(1000001);
		sortedPosY.add(0);
		sortedPosY.add(1000001);
		for (int i = 0; i < fenceCount * 2; i++) {
			fencePosX[i] = sc.nextInt();
			fencePosY[i] = sc.nextInt();
			sortedPosX.add(fencePosX[i]);
			sortedPosY.add(fencePosY[i]);
		}

		int[] cowPosX = new int[cowCount];
		int[] cowPosY = new int[cowCount];
		for (int i = 0; i < cowCount; i++) {
			cowPosX[i] = sc.nextInt();
			cowPosY[i] = sc.nextInt();
			sortedPosX.add(cowPosX[i]);
			sortedPosY.add(cowPosY[i]);
		}
		sc.close();

		Collections.sort(sortedPosX);
		Collections.sort(sortedPosY);
		removeDuplicates(sortedPosX);
		removeDuplicates(sortedPosY);

		int maxX = (sortedPosX.size() * 2) + 1;
		int maxY = (sortedPosY.size() * 2) + 1;

		int tmp1, tmp2, x1, y1, x2, y2;
		byte[][] grid = new byte[maxX][maxY];
		for (int i = 0; i < fenceCount * 2; i += 2) {
			tmp1 = sortedPosX.indexOf(fencePosX[i]) * 2;
			tmp2 = sortedPosX.indexOf(fencePosX[i + 1]) * 2;
			x1 = Math.min(tmp1, tmp2);
			x2 = Math.max(tmp1, tmp2);
			tmp1 = sortedPosY.indexOf(fencePosY[i]) * 2;
			tmp2 = sortedPosY.indexOf(fencePosY[i + 1]) * 2;
			y1 = Math.min(tmp1, tmp2);
			y2 = Math.max(tmp1, tmp2);
			
			if (x1 == x2) {
				y1 = Math.min(y1, y2);
				y2 = Math.max(y1, y2);
				while (y1 <= y2) {
					grid[x1][y1] = 1;
					y1++;
				}
			} else {
				x1 = Math.min(x1, x2);
				x2 = Math.max(x1, x2);
				while (x1 <= x2) {
					grid[x1][y1] = 1;
					x1++;
				}
			}
		}

		int x, y;
		for (int i = 0; i < cowCount; i++) {
			x = sortedPosX.indexOf(cowPosX[i]) * 2;
			y = sortedPosY.indexOf(cowPosY[i]) * 2;
			grid[x][y] = 2;
		}

		byte[] chX = { 0, -1, 0, 1 };
		byte[] chY = { -1, 0, 1, 0 };

		boolean[][] visited = new boolean[maxX][maxY];
		short[] groupSizes = new short[500];
		Queue<Item> Q = new LinkedList<Item>();
		Item cur;
		int nextX, nextY;
		int groupIdx = 0;
		for (int i = 0; i < maxX; i++) {
			for (int j = 0; j < maxY; j++) {
				if (visited[i][j] == false && grid[i][j] == 0) {
					Q.add(new Item(i, j));
					while (Q.size() > 0) {
						cur = Q.poll();
						for (int dir = 0; dir < 4; dir++) {
							nextX = cur.x + chX[dir];
							nextY = cur.y + chY[dir];

							if (nextX < 0 || nextX >= maxX || nextY < 0 || nextY >= maxY
									|| visited[nextX][nextY] == true || grid[nextX][nextY] == 1) {
								continue;
							}

							visited[nextX][nextY] = true;
							if (grid[nextX][nextY] == 2) {
								groupSizes[groupIdx]++;
							}
							Q.add(new Item(nextX, nextY));
						}
					}
					groupIdx++;
				}
			}
		}

		PrintStream fout = new PrintStream("crazy.out");
		int largestGroup = 0;
		for (int i = 0; i < groupIdx; i++) {
			largestGroup = Math.max(largestGroup, groupSizes[i]);
		}
		fout.println(largestGroup);
		fout.close();
	}

	static void removeDuplicates(LinkedList<Integer> list) {
		int idx = 1;
		while (idx < list.size()) {
			if (list.get(idx) == list.get(idx - 1)) {
				list.remove(idx);
			} else {
				idx++;
			}
		}
	}
}
