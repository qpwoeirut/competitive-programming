import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int tests = Integer.parseInt(br.readLine());
        for (int i = 0; i < tests; i++) {
            int n = Integer.parseInt(br.readLine());
            int[][] pvals = new int[n][2];
            int[] nout = new int[n];
            for (int j = 0; j < n; j++) {
                String[] tmp = br.readLine().split(" ");
                pvals[j][0] = Integer.parseInt(tmp[0]);
                pvals[j][1] = Integer.parseInt(tmp[1]);
            }
            for (int j = 0; j < n; j++) {
                nout[j] = Integer.parseInt(br.readLine());
            }
            System.out.println(unbeatable(n, pvals, nout));
        }
        br.close();
    }
    // Do not modify above this line

    public static int unbeatable(int N, int[][] A, int[] adj) {
        for (int i=0; i<N; ++i) {
            adj[i] -= 1;
        }
        int ans = N;
        boolean[] vis = new boolean[N];
        int[] stk = new int[N+1];
        int stk_i = 0;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) vis[j] = false;
            vis[adj[i]] = true;
            stk[stk_i++] = adj[i];
            while (stk_i > 0) {
                final int u = stk[--stk_i];
//                System.out.println("i,u: " + i + " " + u);
                if (i != u && A[u][0] >= A[i][0] && A[u][1] >= A[i][1]) {
                    --ans;
//                    System.out.println("i: " + i);
                    stk_i = 0;
                    break;
                }
                if (!vis[adj[u]]) {
                    vis[adj[u]] = true;
                    stk[stk_i++] = adj[u];
                }
            }
        }

        return ans;
    }
}

/*
3
3
1 2
3 4
5 6
2
3
1
4
1 1
3 3
4 2
2 2
2
3
1
2
7
4 5
2 9
2 0
8 4
1 7
2 3
6 9
4
1
1
2
2
3
3
 */