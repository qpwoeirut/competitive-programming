import java.io.*;

class Main {
    static BufferedReader br;
    /**
     * Phase 1: Initialize N.
     * 
     * Return a string of digits denoting the initial persistent value.
     */
    static String start() { 
        // YOUR CODE HERE
        return "";
    }

    /**
     * Phase 2: Observe each brick.
     * 
     * N: a digit string denoting the persistent value from the previous run
     * color: a letter ("B", "S", or "G") denoting the color of the current
     * brick
     * 
     * Return a string of digits denoting the updated persistent value for the
     * next run. This string must have the same length as the given N.
     */
    static String observe(String N, String color) {
        // YOUR CODE HERE
        return "";
    }

    /**
     * Phase 3: Submit the final answer.
     * 
     * N: a digit string denoting the persistent value from the previous run
     * 
     * Return a string of length 3 containing each of the characters "B", "S",
     * and "G" exactly once, denoting the types from least to most frequent. For
     * example, if silver was the least frequent, gold was in the middle, and
     * bronze was the most frequent, then you should output 'SGB'
     */
    static String answer(String N) {
        // YOUR CODE HERE
        return "";
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        String phase = br.readLine();
        if (phase.equals("START")) {
            out.println(start());
        } else if (phase.equals("OBSERVE")) {
            String N = in.readLine();
            String color = in.readLine();
            out.println(observe(N, color));
        } else {
            String N = in.readLine();
            out.println(answer(N));
        }
    }
}
