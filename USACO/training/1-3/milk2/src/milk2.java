/*
ID: zhongbr1
LANG: JAVA
TASK: milk2
 */

import java.io.*;
import java.util.*;

public class milk2 {
	static class Event implements Comparable<Event>{
		int time;
		int cow;
		
		public Event(int time, int cow) {
			this.time = time;
			this.cow = cow;
		}

		@Override
		public int compareTo(Event e) {
			return this.time  - e.time;
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("milk2.in"));	
		int cowCount = Integer.parseInt(fin.readLine());

		Queue<Event> start = new PriorityQueue<Event> ();
		Queue<Event> end = new PriorityQueue<Event> ();
		for (int i=0; i<cowCount; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			start.add(new Event(Integer.parseInt(st.nextToken()), i));
			end.add(new Event(Integer.parseInt(st.nextToken()), i));
		}
		fin.close();
		
		int longestMilkingTime = 0;
		int longestIdleTime = 0;
		int lastChange = start.peek().time;
		TreeSet<Integer> milking = new TreeSet<Integer> ();
		Event cur;
		while (end.isEmpty() == false) {
			if (start.isEmpty() == false && start.peek().time <= end.peek().time) {
				cur = start.poll();
				
				milking.add(cur.cow);
				
				if (milking.size() == 1) {
					longestIdleTime = Math.max(longestIdleTime, cur.time - lastChange);
					lastChange = cur.time;
				}
			}
			else {
				cur = end.poll();
				
				milking.remove(cur.cow);
				
				if (milking.size() == 0) {
					longestMilkingTime = Math.max(longestMilkingTime, cur.time - lastChange);
					lastChange = cur.time;
				}
			}
		}
		
		PrintStream fout = new PrintStream("milk2.out");
		fout.println(longestMilkingTime + " " + longestIdleTime);
		fout.close();
	}

}
