import java.io.*;
import java.util.*;

public class Main {
    public static final int MN = 400005;
    public static void main(String[] args) {
        FastScanner in = new FastScanner();
        out = new PrintWriter(System.out);

        int N = in.nextInt();
        int[] A = new int[N];
        long[] sum = new long[MN * 2];
        for (int i=0; i<N; ++i) {
            A[i] = in.nextInt();
            sum[MN + A[i] - i] += A[i];
        }

        long ans = 0;
        for (int i=0; i<MN*2; ++i) {
            ans = Math.max(ans, sum[i]);
        }

        out.println(ans);
        out.close();
    }

    public static PrintWriter out;
    public static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        public FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() { return Integer.parseInt(next()); }
        long nextLong() { return Long.parseLong(next()); }
        double nextDouble() { return Double.parseDouble(next()); }
        String nextLine() {
            String s = "";
            try {
                s = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return s;
        }
    }
}
