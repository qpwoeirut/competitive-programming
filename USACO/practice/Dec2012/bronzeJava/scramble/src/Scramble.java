import java.io.*;
import java.util.*;

public class Scramble {
	public static void main(String[] args) throws IOException {
		Scanner sc = new Scanner(new File("scramble.in"));
		int nameCount = sc.nextInt();
		sc.nextLine();

		String tmpStr;
		LinkedList<Name> names = new LinkedList<Name>();
		char[] tmpArray;
		for (int i = 0; i < nameCount; i++) {
			tmpStr = sc.nextLine();
			
			tmpArray = tmpStr.toCharArray();
			Arrays.sort(tmpArray);
			tmpStr = new String(tmpArray);
			names.add(new Name(tmpStr, i, false));
			
			tmpStr = new StringBuffer(tmpStr).reverse().toString();
			names.add(new Name(tmpStr, i, true));
		}
		sc.close();
		
		Collections.sort(names);

		PrintStream fout = new PrintStream("scramble.out");
		int[] sorted_pos = new int[50000];
		int[] reversed_pos = new int[50000];
		int sorted_count = 0, reversed_count = 0;
		ListIterator<Name> listIter = names.listIterator();
		Name cur;
		do {
			cur = listIter.next();
			if (cur.reversed == false) {
				sorted_count++;
				sorted_pos[cur.idx] = reversed_count + 1;
			}
			else {
				reversed_count++;
				reversed_pos[cur.idx] = sorted_count;
				// Don't add 1 to account for the sorted counterpart
			}
		}
		while (listIter.hasNext());

		for (int i=0; i<nameCount; i++) {
			fout.println(sorted_pos[i] + " " + reversed_pos[i]);
		}
		fout.close();
	}

	static class Name implements Comparable<Name> {
		String val;
		int idx;
		boolean reversed;
		
		Name (String val, int idx, boolean reversed) {
			this.val = val;
			this.idx = idx;
			this.reversed = reversed;
		}

		public int compareTo(Name n) {
			return this.val.compareTo(n.val);
		}

	}
}
