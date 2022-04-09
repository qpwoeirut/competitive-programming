import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
    
    public static String[][] fillMosaic(int gridWidth, int gridHeight) {
        String[][] grid = new String[1][1];
        grid[0][0] = ".";
        return grid;
    }
    
 // Do not modify below this line
    public static void printMosaic(String[][] grid) {
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                System.out.print(grid[i][j]);
            }
            System.out.println();
        }
    }
    
    public static void main (String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        while (n-->0) {
            String[] sa = br.readLine().split(" ");
            printMosaic(fillMosaic(Integer.parseInt(sa[0]),Integer.parseInt(sa[1])));
        }
    }
}
