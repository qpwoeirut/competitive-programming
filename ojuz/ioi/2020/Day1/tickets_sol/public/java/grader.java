import java.io.PrintWriter;

public class grader {
	
    private static void check(boolean cond, String message) {
        if (!cond) {
            System.out.println(message);
            System.out.close();
            System.exit(0);
        }
    }
	
    private static boolean called = false;
    private static int x[][], d[][];
    private static int n, m, k;
    public static void allocate_tickets(int[][] _d) {
		check(!called, "allocate_tickets called more than once");
		called = true;
		check(_d.length == n, "allocate_tickets called with parameter of wrong size");
        d = new int[n][m];
        for (int i = 0; i < n; i++) {
			check(_d[i].length == m, "allocate_tickets called with parameter of wrong size");
            for(int j = 0; j < m; j++) {
                d[i][j] = _d[i][j];
            }
        }
    }
    public static void main(String[] args) {
        InputReader inputReader = new InputReader(System.in);
        n = inputReader.readInt();
        m = inputReader.readInt();
        k = inputReader.readInt();
        x = new int[n][m];
        for (int i = 0; i < n; i++) {
            for (int j=0; j < m; j++) {
                x[i][j] = inputReader.readInt();
            }
        }
        inputReader.close();
        tickets solver = new tickets();
        long answer = solver.find_maximum(k, x);
        check(called, "failure to call allocate_tickets");
		PrintWriter out = new PrintWriter(System.out);
        out.println(answer);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j!=0) out.print(' ');
                    out.print(d[i][j]);
            }
            out.print('\n');
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
