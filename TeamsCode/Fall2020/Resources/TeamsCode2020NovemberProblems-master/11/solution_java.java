import java.util.*;
import java.io.*;

public class program
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        String[] l1 = input.readLine().split(" ");
        int N = Integer.parseInt(l1[0]);
        int M = Integer.parseInt(l1[1]);
        String[] l2 = input.readLine().split(" ");
        int[] pSum = new int[N];
        int[] answers = new int[M];
        for (int i = 0; i < N; i++)
        {
            int cur = Integer.parseInt(l2[i]);
            pSum[i] = i == 0 ? cur : pSum[i - 1] + cur;
        }
        for (int i = 0; i < M; i++)
        {
            answers[i] = pSum[Integer.parseInt(input.readLine()) - 1];
        }
        for (int i = 0; i < M; i++)
        {
            System.out.println(answers[i]);
        }
        System.out.println("\n");
    }
}
