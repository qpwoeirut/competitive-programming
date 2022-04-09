import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {
    public static String danceCommand(String s, int[] arr) {
        return "";
    }

    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.valueOf(reader.readLine()); // read # of test cases

        for (int i = 0; i < t; i++) {
            String s = reader.readLine();
            int length = Integer.valueOf(reader.readLine()); // read number of shifts
            int[] arr = new int[length];
            String input = reader.readLine(); // read array
            String[] str = input.split(" ");
            for (int a = 0; a < length; a++) {
                arr[a] = Integer.valueOf(str[a]);
            }
            String output = danceCommand(s, arr);
            System.out.println(output);
        }

    }
  
}