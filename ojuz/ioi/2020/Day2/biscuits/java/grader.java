import java.io.PrintWriter;

public class grader {
	public static void main(String[] args) {
		InputReader inputReader = new InputReader(System.in);
		int q = inputReader.readInt();
		int[] k = new int[q];
		long[] x = new long[q];
		long[][] a = new long[q][];
		for (int t = 0; t < q; t++) {
			k[t] = inputReader.readInt();
			x[t] = inputReader.readLong();
			a[t] = new long[k[t]];
			for (int i = 0; i < k[t]; i++) {
				a[t][i] = inputReader.readLong();
			}
		}
		inputReader.close();
		
		long[] results = new long[q];
		biscuits solver = new biscuits();
		for (int t = 0; t < q; t++) {
			results[t] = solver.count_tastiness(x[t], a[t]);
		}
		PrintWriter out = new PrintWriter(System.out);
		for (int i = 0; i < q ; i++) {
			out.println(results[i]);
		}
		out.flush();
		out.close();
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

	public long readLong() {
		int c = eatWhite();
		long sgn = 1;
		if (c == '-') {
			sgn = -1;
			c = read();
		}
		long res = 0;
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
