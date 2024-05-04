import java.io.*;

class Solution {
    /**
     * Return the maxmimum number of diamonds that Steve can mine before exiting the lava pit.
     * 
     * N: number of rows in the lava pit
     * M: number of columns in the lava pit
     * G: description of the lava pit
     */
    static int solve(int N, int M, String[] G) {
        // YOUR CODE HERE
        return 0;
    }
    
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());
        for (int tc = 0; tc < T; tc++) {
            String[] temp = in.readLine().split(" ");
            int N = Integer.parseInt(temp[0]), M = Integer.parseInt(temp[1]);
            String[] G = new String[N];
            for (int i = 0; i < N; ++i) {
                G[i] = in.readLine();
            }
            out.println(solve(N, M, G));
        }
        out.flush();
    }
}
