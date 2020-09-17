import java.util.HashSet;

public class a {
    public static void main(String[] args) {
        long a = 2, b = 4;
        HashSet<Long> set = new HashSet<>();

        int ops = 0;
        set.add(a);
        while (a != b) {
            boolean f = false;
            if (a < b) {
                for (int i=8; i>=2; i/=2) {
                    if (a*i <= b) {
                        a *= i;
                        if (set.contains(a)) {
                            System.out.println(-1);
                            return;
                        }
                        f = true;
                        ops++;
                        set.add(a);
                        break;
                    }
                }
            }
            else {
                for (int i=8; i>=2; i/=2) {
                    if (a % i == 0 && a/i >= b) {
                        a /= i;
                        if (set.contains(a)) {
                            System.out.println(-1);
                            return;
                        }
                        f = true;
                        ops++;
                        set.add(a);
                        break;
                    }
                }
            }
            if (!f) {
                System.out.println(-1);
                return;
            }
        }
        System.out.println(ops);
    }
}
