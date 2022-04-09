import java.io.*;
import java.util.ArrayList;

public class Main {

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String str = br.readLine();
        String[] splitStr = str.trim().split("\\s+");
        int n = Integer.parseInt(splitStr[0]);
        int q = Integer.parseInt(splitStr[1]);

        ArrayList<ArrayList<Integer>> trees = new ArrayList<>();
        int[][] queries = new int[q][2];
        for (int i = 0; i < n; i++) {
            splitStr = str.trim().split("\\s+");
            int s = Integer.parseInt(splitStr[0]);
            trees.add(new ArrayList<>());
            trees.get(i).add(s);
            for (int j = 0; j < s; j++) {
                trees.get(i).add(Integer.parseInt(splitStr[j + 1]));
            }
        }

        for (int i = 0; i < q; i++) {
            splitStr = str.trim().split("\\s+");
            queries[i][0] = Integer.parseInt(splitStr[0]);
            queries[i][1] = Integer.parseInt(splitStr[1]);
        }
        ArrayList<Integer> results = vacation(n, q, trees, queries);
        for (int s : results) {
            System.out.println(s);
        }
        br.close();
    }
    // DO NOT MODIFY THE CODE ABOVE THIS LINE

    public static ArrayList<Integer> vacation(int n, int m,
                                      ArrayList<ArrayList<Integer>> trees, int[][] queries){
        // your code here
        return null;
    }

}