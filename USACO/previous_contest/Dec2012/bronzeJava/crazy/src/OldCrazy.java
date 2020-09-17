import java.io.*;
import java.util.*;

public class OldCrazy {
	static Fence[] fences = new Fence[500];
	static Cow[] cows = new Cow[500];
	public static void notMain(String[] args) throws IOException {
		Scanner sc = new Scanner(new File("crazy.in"));
		int fenceCount = sc.nextInt();
		int cowCount = sc.nextInt();

		Fence tmpFence;
		LinkedList<Integer> pointX = new LinkedList<Integer>();
		LinkedList<Integer> pointY = new LinkedList<Integer>();
		for (int i = 0; i < fenceCount; i++) {
			tmpFence = new Fence();
			tmpFence.x1 = sc.nextInt();
			tmpFence.y1 = sc.nextInt();
			tmpFence.x2 = sc.nextInt();
			tmpFence.y2 = sc.nextInt();
			fences[i] = tmpFence;

			pointX.add(i);
			pointY.add(i);
		}

		Cow tmpCow;
		for (int i = 0; i < cowCount; i++) {
			tmpCow = new Cow();
			tmpCow.x = sc.nextInt();
			tmpCow.y = sc.nextInt();
			tmpCow.community = -1;
			cows[i] = tmpCow;
			pointX.add(cows[i].x);
			pointY.add(cows[i].y);
		}
		sc.close();

		Collections.sort(pointX);
		Collections.sort(pointY);
		int minX = pointX.peekFirst();
		int maxX = pointX.peekLast();
		int minY = pointY.peekFirst();
		int maxY = pointY.peekLast();
	}
	
	static class Fence {
		int x1, y1, x2, y2;
	}
	
	static class Cow {
		int x, y;
		int community;
	}

	class XPoint implements Comparable<XPoint> {
		char type;
		boolean firstPoint;
		int idx;
	
		@Override
		public int compareTo(XPoint o) {
			int val1, val2;
			if (this.type == 'F') {
				if (this.firstPoint == true) {
					val1 = fences[this.idx].x1;
				}
				else {
					val1 = fences[this.idx].x2;
				}
				
			}
			else {
				val1 = cows[this.idx].x;
			}
			
			if (o.type == 'F') {
				if (o.firstPoint == true) {
					val2 = fences[o.idx].x1;
				}
				else {
					val2 = fences[o.idx].x2;
				}
				
			}
			else {
				val2 = cows[o.idx].x;
			}
			
			return val1 - val2;
		}
	}
	
	class YPoint implements Comparable<YPoint> {
		char type;
		boolean firstPoint;
		int idx;
	
		@Override
		public int compareTo(YPoint o) {
			int val1, val2;
			if (this.type == 'F') {
				if (this.firstPoint == true) {
					val1 = fences[this.idx].y1;
				}
				else {
					val1 = fences[this.idx].y2;
				}
				
			}
			else {
				val1 = cows[this.idx].y;
			}
			
			if (o.type == 'F') {
				if (o.firstPoint == true) {
					val2 = fences[o.idx].y1;
				}
				else {
					val2 = fences[o.idx].y2;
				}
				
			}
			else {
				val2 = cows[o.idx].y;
			}
			
			return val1 - val2;
		}
	}
}
