import java.io.*;

class Solution {
    /**
     * Output YES if it is possible for the player to run on the course such that it
     * consists of blocks and banned otherwise.
     * 
     * N: the number of blocks in the course.
     * S: the list of starting blocks
     * E: the list of ending blocks
     */
    static void solve(int N, char[] S, char[] E) {
        return;
    }
    
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) {
            int N = Integer.parseInt(in.readLine());
            char[] S = new char[N];
            String temp = in.readLine();
            for (int j = 0; j < N; j++) {
                S[j] = temp.charAt(j);
            }
            char[] E = new char[N];
            temp = in.readLine();
            for (int j = 0; j < N; j++) {
                E[j] = temp.charAt(j);
            }
            solve(N, S, E);
        }
        out.flush();
    }
}
