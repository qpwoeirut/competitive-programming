//import java.io.*;
//
//public class Main {
//    public static int maxPoints(String s, String t) {
//        int N = s.length();
//        int M = t.length();
//        int[][] dp = new int[2][M+1];
//        for (int i=1; i<=N; ++i) {
//            for (int j=1; j<=M; ++j) {
//                dp[i&1][j] = Math.max(
//                        (s.charAt(i-1) == t.charAt(j-1) ? 1 : -1) + dp[(i&1)^1][j-1],
//                Math.max(dp[(i&1)^1][j] - 2,
//                         dp[i&1][j-1] - 2));
//            }
//        }
//
//        return dp[N&1][M];
//    }
//
//    // Do not modify below this line
//    public static void main(String[] args) throws Exception {
//        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//        int tests = Integer.parseInt(br.readLine());
//        for (int i = 0; i < tests; i++) {
//            String s = br.readLine();
//            String t = br.readLine();
//            System.out.println(maxPoints(s, t));
//        }
//        br.close();
//    }
//}
