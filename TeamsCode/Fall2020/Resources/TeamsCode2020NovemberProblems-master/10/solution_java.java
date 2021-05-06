import java.util.Scanner;

public class Solution
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int N = Integer.parseInt(input.nextLine());
        String[] binVals = new String[N];
        for (int i = 0; i < N; i++)
        {
            String[] lineSpl = input.nextLine().split(" ");
            int base = Integer.parseInt(lineSpl[0]);
            int numInBase = Integer.parseInt(lineSpl[1]);
            int base10Val = 0;
            int powVal = 1;
            while (numInBase > 0)
            {
                base10Val += powVal * (numInBase % 10);
                powVal *= base;
                numInBase /= 10;
            }
            binVals[i] = Integer.toBinaryString(base10Val);
        }

        for (String s : binVals)
        {
            System.out.println(s);
        }
    }
}
