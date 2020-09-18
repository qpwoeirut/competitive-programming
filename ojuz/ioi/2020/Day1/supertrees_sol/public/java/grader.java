import java.io.PrintWriter;

class grader {
    private static int n;
    private static int[][] p;
    private static int[][] b;
    private static boolean called = false;
    private static PrintWriter out;

    private static void check(boolean cond, String message) {
        if (!cond) {
            out.println(message);
            out.close();
            System.exit(0);
        }
    }

    public static void build(int[][] _b) {
        check(!called, "build is called more than once");
        called = true;
        check(_b.length == n, "Invalid number of rows in b");
        for (int i = 0; i < n; i++) {
            check(_b[i].length == n, "Invalid number of columns in b");
        }
        b = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                b[i][j] = _b[i][j];
            }
        }
    }

    public static void main(String[] args) {
        InputReader inputReader = new InputReader(System.in);
        n = inputReader.readInt();
        p = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                p[i][j] = inputReader.readInt();
            }
        }
        inputReader.close();

        out = new PrintWriter(System.out);
        supertrees solver = new supertrees();
        int possible = solver.construct(p);

        check(possible == 0 || possible == 1, "Invalid return value of construct");
        if (possible == 1) {
            check(called, "construct returned 1 without calling build");
        } else {
            check(!called, "construct called build but returned 0");
        }

        out.println(possible);
        if (possible == 1) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (j != 0) {
                        out.print(" ");
                    }
                    out.print(b[i][j]);
                }
                out.println();
            }
        }
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
