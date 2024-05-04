import java.io.*;

class Solution {
    /**
     * Return the maximum number of players that can make it across the TNT bridge.
     * If infinitely many players can complete the course, return -1
     * 
     * N: number of blocks in the course
     * K: maximum jump distance of every player
     * S: description of the TNT bridge
     */
    static int solve(int N, int K, String S) {
        // YOUR CODE HERE
        return -1;
    }
    
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) {
            String[] temp = in.readLine().split(" ");
            int N = Integer.parseInt(temp[0]), K = Integer.parseInt(temp[1]);
            String[] temp1 = in.readLine().split(" ");
            String S = temp1[0];
            out.println(solve(N, K, S));
        }
        out.flush();
    }
}
