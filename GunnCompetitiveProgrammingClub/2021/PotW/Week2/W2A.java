import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        FastScanner in = new FastScanner();
        out = new PrintWriter(System.out);

        int N = in.nextInt();
        int M = in.nextInt();
        Pair[] A = new Pair[M];
        for (int i=0; i<M; ++i) {
            int a = in.nextInt();
            int b = in.nextInt();
            A[i] = new Pair(b, a);
        }

        Arrays.sort(A, Collections.reverseOrder());

        int ans = 0;
        for (int i=0; i<M; ++i) {
            int use = Math.min(A[i].second, N);
            N -= use;
            ans += use * A[i].first;
        }

        out.println(ans);
        out.close();
    }

    static class Pair implements Comparable<Pair> {
        public int first, second;
        public Pair(int fi, int se) {
            this.first = fi;
            this.second = se;
        }
        public int compareTo(Pair o) {
            if (this.first == o.first) {
                return this.second - o.second;
            }
            return this.first - o.first;
        }
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
