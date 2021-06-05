import java.util.PriorityQueue;
import java.util.Scanner;

public class hawkeye {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        PriorityQueue<Integer> q = new PriorityQueue<>(n);
        for (int i = 0; i < n; i++) {
            q.add(scanner.nextInt());
        }
        scanner.close();
        int t = 0;
        while (q.size() > 1) {
            int a = q.poll();
            int b = q.poll();
            t += a + b;
            q.add(a + b);
        }
        System.out.println(t);

    }
}
