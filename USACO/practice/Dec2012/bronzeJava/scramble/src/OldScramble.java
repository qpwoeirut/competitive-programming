import java.io.*;
import java.util.*;

public class OldScramble {
	public static void main(String[] args) throws IOException {
		Scanner sc = new Scanner(new File("scramble.in"));
		int nameCount = sc.nextInt();
		String[] sortedNames = new String[nameCount];
		String[] reversedNames = new String[nameCount];
		sc.nextLine();

		String tmpStr;
		char[] tmpArray;
		TreeSet<String> sortedNameSet = new TreeSet<String>();
		TreeSet<String> reversedNameSet = new TreeSet<String>();
		for (int i = 0; i < nameCount; i++) {
			tmpStr = sc.nextLine();
			tmpArray = tmpStr.toCharArray();
			Arrays.sort(tmpArray);
			sortedNames[i] = new String(tmpArray);
			reversedNames[i] = new StringBuffer(sortedNames[i]).reverse().toString();
			sortedNameSet.add(sortedNames[i]);
			reversedNameSet.add(reversedNames[i]);
		}
		sc.close();

		PrintStream fout = new PrintStream("scramble.out");
		int lowPos, highPos;
		for (int i = 0; i < nameCount; i++) {
			sortedNameSet.remove(sortedNames[i]);
			sortedNameSet.add(reversedNames[i]);
			reversedNameSet.remove(reversedNames[i]);
			reversedNameSet.add(sortedNames[i]);

			lowPos = Arrays.binarySearch(reversedNameSet.toArray(), sortedNames[i]) + 1;
			highPos = Arrays.binarySearch(sortedNameSet.toArray(), reversedNames[i]) + 1;
			fout.println(lowPos + " " + highPos);

			sortedNameSet.remove(reversedNames[i]);
			sortedNameSet.add(sortedNames[i]);
			reversedNameSet.remove(sortedNames[i]);
			reversedNameSet.add(reversedNames[i]);
		}
		fout.close();
	}
}
