import java.util.Scanner;

public class Solution5
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int n, t;
        t = Integer.parseInt(sc.nextLine());
        while (t > 0)
        {
            n = Integer.parseInt(sc.nextLine());
            int ans = 0;
            while (n > 0) {
                ans += n % 10;
                n /= 100;
            }
            System.out.printf("%d\n", ans);
            t--;
        }
    }
}
