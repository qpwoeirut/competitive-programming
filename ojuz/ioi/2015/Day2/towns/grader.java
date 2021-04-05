import java.io.*;
import java.util.InputMismatchException;

public class grader {

    private static int N;
    
    public static void main(String[] args) throws IOException {
        InputReader in = new InputReader(new FileInputStream("towns.in"));
        OutputWriter out = new OutputWriter(new FileOutputStream("towns.out"));
        int subtask = in.readInt();
        int ncase = in.readInt();
        for (int i = 0; i < ncase; i++) {
            N = in.readInt();
            lib.ini_query(subtask, in);
            int R = new towns().hubDistance(N, subtask);
            out.printLine(R);
        }
        out.close();
    }

    public static class lib {
        private static int[][] dist;
        private static int quota, user_query;

        static void ini_query(int k, InputReader in) {
            int i,j;
            dist = new int[N][];
            for (i = 0; i < N; i++) {
                dist[i] = IOUtils.readIntArray(in, N);
            }
            if (k == 1 || k == 3) quota = N * (N - 1) / 2;
            else if (k == 2 || k == 4 || k == 6) quota= (7 * N + 1) / 2;
            else quota = 5 * N;
            user_query = 0;
        }


        public static int getDistance(int i, int j) {
        	  user_query++;
            if (user_query > quota) {
                System.exit(0);
            }
            if (i < 0 || i >= N) return 0;
            if (j < 0 || j >= N) return 0;
            return dist[i][j];
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

        public void printLine(int i) {
            writer.println(i);
        }

    }

}
