import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;

public class XOR {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("XORIN.txt"));
        String[] data = br.readLine().split(" ");
        int testCases = Integer.parseInt(data[0]);
        for( ; testCases > 0; testCases--) {
            int n = Integer.parseInt(br.readLine());
            int[] arr = new int[n];
            for (int i = 0; i < n; i++) {
                arr[i] = Integer.parseInt(br.readLine());
            }
            System.out.println(solve(n, arr));
        }
        br.close();
    }
    
    public static long solve(int n, int[] arr) {
        HashMap<Integer, ArrayList<Integer>> prefix = new HashMap<>();
        int[] prefixxor = new int[n];
        prefixxor[0] = arr[0];
        ArrayList<Integer> l0 = new ArrayList<>();
        ArrayList<Integer> l1 = new ArrayList<>();
        long total = 0;
        if (prefixxor[0] == 0) {
            l0.add(-1);
            l0.add(0);
            prefix.put(0, l0);
        } else {
            l0.add(0);
            l1.add(-1);
            prefix.put(prefixxor[0], l0);
            prefix.put(0, l1);
        }
        for (int i = 1; i < n; i++) {
            prefixxor[i] = prefixxor[i - 1] ^ arr[i];
            if (prefix.containsKey(prefixxor[i])) {
                prefix.get(prefixxor[i]).add(i);
            } else {
                ArrayList<Integer> l = new ArrayList<>();
                l.add(i);
                prefix.put(prefixxor[i], l);
            }
        }
        Set<Integer> keyset = prefix.keySet();
        for (Integer i : keyset) {
            ArrayList<Integer> l = prefix.get(i);
            int size = l.size();
            int count = - size + 1;
            for (int j = 0; j < size; j++) {
                total += ((long) l.get(j)) * ((long) count);
                count += 2;
            }
            total -= (((long) size) * ((long) (size - 1))) / 2L;
        }
        return total;
    }

}
