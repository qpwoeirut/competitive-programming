import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
import java.io.*;

public class Main {
    public static double[] terrifyingTetra(double[][] ps) {
        double[] pt = new double[3];
	  return pt;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.valueOf(reader.readLine());
        for (int i = 0; i < t; i++) {
            double[][] points = new double[4][3];
            for (int j = 0; j < 4; j++) {
                String point = reader.readLine();
                String[] split = point.split(" ");
                for (int a = 0; a < 3; a++) {
                    points[j][a] = Double.valueOf(split[a]);
                }
            }
            double[] output = terrifyingTetra(points);
            for (int j = 0; j < output.length; j++) {
                System.out.print((Math.round(output[j] * 10.0) / 10.0) + " ");
            }
            System.out.println();
        }
    }
}