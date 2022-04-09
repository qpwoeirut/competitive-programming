import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    public static int[][] shiftingSands(int[][] sands, String[] moves) {

    }

    // Do not modify below this line
    public static void main(String args[]) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.valueOf(reader.readLine());

        for (int i = 0; i < t; i++) {
            int[][] sands = new int[5][5];

            for (int j = 0; j < 4; j++) {

                String line = reader.readLine();
                String[] elems = line.split(" ");
                for (int k = 0; k < 4; k++)
                    sands[j][k] = Integer.valueOf(elems[k]);
            }

            String[] moves = reader.readLine().split(" ");
            int[][] output = shiftingSands(sands, moves);

            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    System.out.print(output[j][k] + " ");
                }
                System.out.println();
            }
        }
    }
}