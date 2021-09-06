import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int Q = sc.nextInt();
        
        HashSet<Integer> set = new HashSet<Integer>();
        for (int i=0; i<N; ++i) {
            set.add(sc.nextInt());
        }
        
        for (int i=0; i<Q; ++i) {
            int t = sc.nextInt();
            if (t == 3) {
                System.out.println(set.size());
                continue;
            }
            
            int x = sc.nextInt();
            if (t == 1) {
                set.add(x);
            } else if (t == 2) {
                set.remove(x);
            } else if (t == 4) {
                System.out.println(set.contains(x) ? 1 : 0);
            }
        }
    }
}

