import java.io.*;

class Solution {
    /**
     * Return the probability of your Pokemon fainting after being hit with Population Bomb.
     * If the probability is p/q, return p * q^-1 mod 1000000007
     * 
     * H: Your Pokemon's HP
     * N: Number of times that Population Bomb hits
     * M: Number of damage rolls
     * R: List of the M damage rolls
     */
    static int solve(int H, long N, int M, int[] R) {
        // YOUR CODE HERE
        return -1;
    }
    
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());
        for (int tc = 0; tc < T; tc++) {
            String[] temp = in.readLine().split(" ");
            int H = Integer.parseInt(temp[0]);
            long N = Long.parseLong(temp[1]);
            int M = Integer.parseInt(temp[2]);
            temp = in.readLine().split(" ");
            int[] R = new int[M];
            for (int i = 0; i < M; ++i) {
                R[i] = Integer.parseInt(temp[i]);
            }
            out.println(solve(H, N, M, R));
        }
        out.flush();
    }
}
