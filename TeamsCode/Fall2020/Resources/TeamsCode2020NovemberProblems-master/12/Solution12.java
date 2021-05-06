import java.util.Scanner;

public class Solution12
{
    public static void main(String[] args)
    {
        int[] s = new int[105];
        int[] w = new int[105];
        int[] v = new int[105];
        int[][] dp = new int[505][505];
        int n, ms, mw;
        Scanner sc = new Scanner(System.in);
        n = Integer.parseInt(sc.next());
        ms = Integer.parseInt(sc.next());
        mw = Integer.parseInt(sc.next());
        for (int i = 1; i <= n; i++)
        {
            v[i] = Integer.parseInt(sc.next());
            s[i] = Integer.parseInt(sc.next());
            w[i] = Integer.parseInt(sc.next());
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = ms; j >= s[i]; j--)
            {
                for (int k = mw; k >= w[i]; k--)
                {
                    dp[j][k] = Math.max(dp[j][k], dp[j - s[i]][k - w[i]] + v[i]);
                }
            }
        }
        System.out.println(dp[ms][mw]);
    }
}
