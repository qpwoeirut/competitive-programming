import java.io.*;
import java.util.InputMismatchException;

public class grader {
    
    public static void main(String[] args) throws IOException {
        InputReader in = new InputReader(new FileInputStream("scales.in"));
        OutputWriter out = new OutputWriter(new FileOutputStream("scales.out"));
        lib.out = out;
        int t = in.readInt();
        scales s = new scales();
        s.init(t);
        for (int i = 1; i <= t; ++i) {
            lib.initNewTest(in);
            s.orderCoins();
        }
        out.close();
    }

    static class lib {
        private static final int MAXN = 6;
        private static int[] realC = new int[MAXN];
        private static int[] ind = new int[MAXN];
        private static int numQueries;
        private static int numAnswerCalls;
        static InputReader in;
        static OutputWriter out;

        static void initNewTest(InputReader in) {    
            int i;

            for (i = 0; i < MAXN; i++) {
                realC[i] = in.readInt();
                realC[i]--;
                ind[realC[i]] = i;
            }

            numQueries = 0;
            numAnswerCalls = 0;
        }

        public static void answer(int W[]) {
            int i;

            numAnswerCalls++;
            if (numAnswerCalls > 1) 
                return;
            
            for (i = 0; i < 6; i++)
                out.print((W[i]) + " ");
            out.printLine("");
            out.printLine(Integer.toString(numQueries));
        }

        static void checkQuery(int A, int B, int C, int D) {
            if (D == -1) {
                if (A < 1 || A > 6 || B < 1 || B > 6 || C < 1 || C > 6)
                    System.exit(1);
                if (A == B || B == C || A == C)
                    System.exit(1);
            }
            else {
                if (A < 1 || A > 6 || B < 1 || B > 6 || C < 1 || C > 6 || D < 1 || D > 6)
                    System.exit(1);
                if (A == B || A == C || A == D || B == C || B == D || C == D)
                    System.exit(1);
            }
        }

        public static int getMedian(int A, int B, int C) {
            numQueries++;
            checkQuery(A, B, C, -1);

            A--; B--; C--;

            if (ind[B] < ind[A] && ind[A] < ind[C])
                return A + 1;

            if (ind[C] < ind[A] && ind[A] < ind[B])
                return A + 1;

            if (ind[A] < ind[B] && ind[B] < ind[C])
                return B + 1;

            if (ind[C] < ind[B] && ind[B] < ind[A])
                return B + 1;

            return C + 1;
        }

        public static int getHeaviest(int A, int B, int C) {
            numQueries++;
            checkQuery(A, B, C, -1);    

            A--; B--; C--;

            if (ind[A] > ind[B] && ind[A] > ind[C])
                return A + 1;

            if (ind[B] > ind[A] && ind[B] > ind[C])
                return B + 1;

            return C + 1;
        }

        public static int getLightest(int A, int B, int C) {
            numQueries++;
            checkQuery(A, B, C, -1);

            A--; B--; C--;

            if (ind[A] < ind[B] && ind[A] < ind[C])
                return A + 1;
            
            if (ind[B] < ind[A] && ind[B] < ind[C])
                return B + 1;

            return C + 1;
        }

        public static int getNextLightest(int A, int B, int C, int D) {
            int allLess = 1;    

            numQueries++;
            checkQuery(A, B, C, D);

            A--; B--; C--; D--;

            if (ind[A] > ind[D] || ind[B] > ind[D] || ind[C] > ind[D])
                allLess = 0;

            if (allLess == 1) {
                if (ind[A] < ind[B] && ind[A] < ind[C])
                    return A + 1;
            
                if (ind[B] < ind[A] && ind[B] < ind[C])
                    return B + 1;

                return C + 1;
            }

            if (ind[A] > ind[D]) {
                if ((ind[A] < ind[B] || ind[B] < ind[D]) && (ind[A] < ind[C] || ind[C] < ind[D]))
                    return A + 1;
            }

            if (ind[B] > ind[D]) {
                if ((ind[B] < ind[A] || ind[A] < ind[D]) && (ind[B] < ind[C] || ind[C] < ind[D]))
                    return B + 1;
            }

            return C + 1;
        }
    }



    static class InputReader {
        private InputStream stream;
        private byte[] buf = new byte[1024];
        private int curChar;
        private int numChars;
        private InputReader.SpaceCharFilter filter;

        public InputReader(InputStream stream) {
            this.stream = stream;
        }

        public int read() {
            if (numChars == -1)
                throw new InputMismatchException();
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }
                if (numChars <= 0)
                    return -1;
            }
            return buf[curChar++];
        }

        public int readInt() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            int res = 0;
            do {
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            } while (!isSpaceChar(c));
            return res * sgn;
        }

        public boolean isSpaceChar(int c) {
            if (filter != null)
                return filter.isSpaceChar(c);
            return isWhitespace(c);
        }

        public static boolean isWhitespace(int c) {
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }

        public interface SpaceCharFilter {
            public boolean isSpaceChar(int ch);

        }

    }

    static class IOUtils {
        public static int[] readIntArray(InputReader in, int size) {
            int[] array = new int[size];
            for (int i = 0; i < size; i++)
                array[i] = in.readInt();
            return array;
        }

        public static void readIntArrays(InputReader in, int[]... arrays) {
            for (int i = 0; i < arrays[0].length; i++) {
                for (int j = 0; j < arrays.length; j++)
                    arrays[j][i] = in.readInt();
            }
        }

    }

    static class OutputWriter {
        private final PrintWriter writer;

        public OutputWriter(OutputStream outputStream) {
            writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
        }

        public OutputWriter(Writer writer) {
            this.writer = new PrintWriter(writer);
        }

        public void close() {
            writer.close();
        }

        public void print(String i) {
            writer.print(i);
        }
        public void printLine(String i) {
            writer.println(i);
        }

    }

}
