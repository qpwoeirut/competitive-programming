import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.InputMismatchException;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.TreeMap;

public class stub {
  private static int max_label = 0;
  private static int r, n, k, q;
  private static int[] u, v, labels;
  private static ArrayList<Integer> answers;
  private static TreeMap<Integer, Integer> reverse_labels;
  private static ArrayList<ArrayList<Integer>> adjlist;
  private static int s, t, w;
  private static int[] c;

	public static void main(String[] args) {
		InputReader inputReader = new InputReader(System.in);
		r = inputReader.readInt();
		stations solver = new stations();
		answers = new ArrayList<>();
	  for (int tc = 0; tc < r; tc++) {
	    n = inputReader.readInt();
	    k = inputReader.readInt();
	    u = new int[n - 1];
	    v = new int[n - 1];
	    adjlist = new ArrayList<>();
	    for (int i = 0; i < n; i++) {
	      adjlist.add(new ArrayList<>());
	    }
  		for (int i = 0; i < n - 1; i++) {
  		  u[i] = inputReader.readInt();
  		  v[i] = inputReader.readInt();
  			adjlist.get(u[i]).add(v[i]);
  			adjlist.get(v[i]).add(u[i]);
  		}
		  labels = solver.label(n, k, u, v);
  		if (labels == null || labels.length != n) {
  			System.out.println("Number of labels not equal to " + n);
				System.exit(0);
  		}
  		reverse_labels = new TreeMap<>();
  		for (int i = 0; i < n; i++) {
  			if (labels[i] < 0 || labels[i] > k) {
  				System.out.println("Label not in range 0 to " + k);
  			  System.exit(0);
  			}
  			if (reverse_labels.get(labels[i]) != null) {
					System.out.println("Labels not unique");
					System.exit(0);
  			}
  			reverse_labels.put(labels[i], i);
  			if (labels[i] > max_label) {
  				max_label = labels[i];
  			}
  		}
  		q = inputReader.readInt();
  		for (int i = 0; i < q; i++) {
    		s = inputReader.readInt();
    		t = inputReader.readInt();
    		w = inputReader.readInt();
    		c = new int[adjlist.get(s).size()];
  			for (int j = 0; j < adjlist.get(s).size(); j++) {
  				c[j] = labels[adjlist.get(s).get(j)];
  			}
  			Arrays.sort(c);
  			int answer = solver.find_next_station(labels[s], labels[t], c);
  			if (Arrays.binarySearch(c, answer) < 0) {
					System.out.println("Label " + answer + " returned by find_next_station not found in c");
					System.exit(0);
  			}
  			answers.add(reverse_labels.get(answer));
  		}
	  }
  	System.out.println(max_label);
  	for (int index : answers) {
  		System.out.println(index);
  	}
  	System.exit(0);
	}
}

class InputReader {
	private InputStream stream;
	private byte[] buf = new byte[1024];
	private int curChar;
	private int numChars;

	public InputReader(InputStream stream) {
		this.stream = stream;
	}

	public int read() {
		if (numChars == -1) {
			throw new InputMismatchException();
		}
		if (curChar >= numChars) {
			curChar = 0;
			try {
				numChars = stream.read(buf);
			} catch (IOException e) {
				throw new InputMismatchException();
			}
			if (numChars <= 0) {
				return -1;
			}
		}
		return buf[curChar++];
	}

	public int readInt() {
		int c = eatWhite();
		int sgn = 1;
		if (c == '-') {
			sgn = -1;
			c = read();
		}
		int res = 0;
		do {
			if (c < '0' || c > '9') {
				throw new InputMismatchException();
			}
			res *= 10;
			res += c - '0';
			c = read();
		} while (!isSpaceChar(c));
		return res * sgn;
	}

	public String readString() {
		int c = eatWhite();
		StringBuilder res = new StringBuilder();
		do {
			if (Character.isValidCodePoint(c))
				res.appendCodePoint(c);
			c = read();
		} while (!isSpaceChar(c));
		return res.toString();
	}

	private int eatWhite() {
		int c = read();
		while (isSpaceChar(c)) {
			c = read();
		}
		return c;
	}
	
	public static boolean isSpaceChar(int c) {
		return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
	}
}
