import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
import java.util.Arrays; 
public class Packing {
    // Before submitting, make sure the main method hasn't been changed!
    // DO NOT MODIFY BELOW THIS LINE
    
    public static void main(String[] args) throws IOException {
        Scanner fileInput = new Scanner(new FileReader("PackingIN.txt"));
        int tests = Integer.parseInt(fileInput.nextLine());
        for(int i = 0; i < tests; i++) {
            String[] row = fileInput.nextLine().split(" ");
            int n = Integer.parseInt(row[0]);
            int m = Integer.parseInt(row[1]);
            int[] x = new int[n];
            row = fileInput.nextLine().split(" ");
            for(int j = 0; j < n; j++) {
                x[j] = Integer.parseInt(row[j]);
            }
            int[] c = new int[m+1];
            row = fileInput.nextLine().split(" ");
            c[0] = 0;
            for(int j = 1; j <= m; j++) {
                c[j] = Integer.parseInt(row[j]);
            }
            System.out.println(solve(n, m, x, c));
        }
        fileInput.close();
    }   
    
    // DO NOT MODIFY ABOVE THIS LINE
    
    // Fill out the body of this method
    public static int solve(int n, int m, int[] x, int[] c) {
        for(int i = m - 1; i > 0; i--) c[i] = Math.min(c[i], c[i+1]);
        Arrays.sort(x);
        int[] dp = new int[n];
        for(int i = 1; i < n; i++) dp[i] = 0;
        dp[0] = c[1];
        for(int i = 1; i < n; i++) {
            dp[i] = c[x[i]-x[0]+1];
            for(int j = 0; j < i; j++) {
                dp[i] = Math.min(dp[i], dp[j] + c[x[i] - x[j+1] +1]);
            }
        }
        return dp[n-1];
    }
}
