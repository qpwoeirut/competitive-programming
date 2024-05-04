import java.io.*;

class Solution {
    /**
     * Return the number of times the given person sees the Era Meteor Shower over the course of their life, it it occurs every fifty years.
 * 
     * B: the number of years ago when someone was born
     * L: the lifespan of that person
     * E: the number of years until the next Era Meteor Shower
     */
    static int solve(int B, int L, int E) {
        // YOUR CODE HERE
        return -1;
    }
    
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) {
            String[] temp = in.readLine().split(" ");
            int B = Integer.parseInt(temp[0]), L = Integer.parseInt(temp[1]), E = Integer.parseInt(temp[2]);
            out.println(solve(B, L, E));
        }
        out.flush();
    }
}
