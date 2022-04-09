import java.io.*;
import java.util.ArrayList;

public class Main {
    
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int cases = Integer.parseInt(br.readLine());
        for (int j = 0; j < cases; j++) {
            String str = br.readLine();
            String[] splitStr = str.trim().split("\\s+");   
            int n = Integer.parseInt(splitStr[0]);
            int m = Integer.parseInt(splitStr[1]);
            int q = Integer.parseInt(splitStr[2]);
            String[] islands = new String[n];
            int[] queries = new int[q];
            for (int i = 0; i < n; i++) {
                String s = br.readLine();
                islands[i] = s;
            }
            for (int i = 0; i < q; i++) {
                String s = br.readLine();
                queries[i] = Integer.parseInt(s);
            }
            ArrayList<String> results = tubeAdventures(n, m, q, islands, queries);
            for (String s : results) {
                System.out.println(s);
            }
        }
            br.close();
    }
    // DO NOT MODIFY THE CODE ABOVE THIS LINE
    
    public static void tubeAdventures(int n, int m, int q, String[] islands, int[] queries){
      // your code here
}

}