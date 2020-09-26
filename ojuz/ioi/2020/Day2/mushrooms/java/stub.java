
public class stub {

	private static final int min_n = 2;
	private static final int max_n = 20000;
	private static final int max_qc = 20000;
	private static final int max_qs = 100000;
	private static final int species_A = 0;
	private static final int species_B = 1;

	private static int n;
	private static int[] species;
	private static int qc, qs;

	private static void error_if(boolean cond, String message) {
		if (cond) {
			System.out.println(message);
			System.exit(0);
		}
	}

	private static void wrong_if(boolean cond, String message) {
		error_if(cond, "Wrong Answer: "+message);
	}

	public static int use_machine(int[] x) {
		final int xs = x.length;
		wrong_if(xs < 2, "Too small array for query.");
		wrong_if(xs > n, "Too large array for query.");
		qc++;
		wrong_if(qc > max_qc, "Too many queries.");
		qs += xs;
		wrong_if(qs > max_qs, "Too many total array sizes as queries.");
		for (int i = 0; i < xs; i++)
			wrong_if(x[i] < 0 || n - 1 < x[i], "Invalid value in the query array.");
		boolean[] used = new boolean[n];
		java.util.Arrays.fill(used, false);
		for (int i = 0; i < xs; i++) {
			wrong_if(used[x[i]], "Duplicate value in the query array.");
			used[x[i]] = true;
		}
		int diffs = 0;
		for (int i = 1; i < xs; i++)
			diffs += (species[x[i]] != species[x[i-1]]) ? 1 : 0;
		return diffs;
	}

	private static void check_input(boolean cond, String messageFmt, Object... messageArgs) {
		String message = String.format(messageFmt, messageArgs);
		error_if(!cond, "Invalid input: "+message);
	}

	private static int read_int(InputReader inputReader, String errorMessageFmt, Object... errorMessageArgs) {
		try {
			return inputReader.readInt();
		} catch (java.util.InputMismatchException e) {
			check_input(false, errorMessageFmt, errorMessageArgs);
			return 0;
		}
	}

	public static void main(String... args) {
		InputReader inputReader = new InputReader(System.in);
		n = read_int(inputReader, "Could not read n.");
		check_input(min_n <= n, "n must not be less than %d, but it is %d.", min_n, n);
		check_input(n <= max_n, "n must not be greater than %d, but it is %d.", max_n, n);
		species = new int[n];
		for (int i = 0; i < n; i++) {
			species[i] = read_int(inputReader, "Could not read species element [%d].", i);
			check_input(species[i]==species_A || species[i] == species_B,
						"Species elements must be %d or %d, but species element [%d] is %d.", species_A, species_B, i, species[i]);
		}
		check_input(species[0] == species_A, "Species element [%d] must be %d.", 0, species_A);
		// Postponed closing standard input in order to allow interactive usage of the grader.

		qc = 0;
		qs = 0;
		mushrooms sol = new mushrooms();
		int answer = sol.count_mushrooms(n);
		System.out.println(answer);
		System.out.println(qc);
		System.out.close();
		inputReader.close();
	}
}


class InputReader implements java.io.Closeable {
	private java.io.InputStream stream;
	private byte[] buf = new byte[1024];
	private int curChar;
	private int numChars;

	public InputReader(java.io.InputStream stream) {
		this.stream = stream;
	}

	@Override
	public void close() {
		try {
			this.stream.close();
		} catch (java.io.IOException e) {
		}
	}

	public int read() {
		if (numChars == -1) {
			throw new java.util.InputMismatchException();
		}
		if (curChar >= numChars) {
			curChar = 0;
			try {
				numChars = stream.read(buf);
			} catch (java.io.IOException e) {
				throw new java.util.InputMismatchException();
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
				throw new java.util.InputMismatchException();
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

	public String readLine() {
		StringBuilder res = new StringBuilder();
		while (true) {
			int c = read();
			if (c == '\n' || c == '\r' || c == -1)
				break;
			if (Character.isValidCodePoint(c))
				res.appendCodePoint(c);
		}
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
