// TODO!!!!
import java.io.*;

class Solution {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    /**
     * Return the CALICOncatenation of A.
     *
     * A: a string of representing a single word 
     */
    static void solve(String S, String T) {
        return;
    }

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) {
            String S = in.readLine();
            String P = in.readLine();
            out.println(solve(S, T));
        }
        out.flush();
    }
}

