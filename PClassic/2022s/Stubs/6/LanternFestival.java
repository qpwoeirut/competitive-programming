import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    public static int[] lanternFestival(int n, int[][] prefs) {
        return new int[];
    }


    // Do not modify below this line
    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.valueOf(reader.readLine());

        for (int i = 0; i < t; i++) {
            String inputNodes = reader.readLine();
            int n = Integer.valueOf(inputNodes);
            String edgeNum = reader.readLine();
            int k = Integer.valueOf(edgeNum);
            int[][] prefs = new int[k][2];
            for (int z = 0; z < k; z++) {
                String inputEdges = reader.readLine();
                String[] inputE = inputEdges.split(" ");
                prefs[z][0] = Integer.valueOf(inputE[0]);
                prefs[z][1] = Integer.valueOf(inputE[1]);
            }

            int [] output = lanternFestival(n, prefs);
            for (Integer e: output) {
                System.out.println(e);
            }

        }
    }
}