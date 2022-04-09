import java.io.*;
import java.util.*;

public class Main {
	public static int superhero(int n, int[] bff) {
		return 0;
	}
	

	// Do not modify below this line
	public static void main(String[] args) throws Exception {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.valueOf(reader.readLine());
		for (int i = 0; i < t; i++) {
			int n = Integer.valueOf(reader.readLine());
			int[] bff = new int[n];
			for (int j = 0; j < n; j++) {
			    bff[j] = Integer.valueOf(reader.readLine());
			}
			int output = superhero(n, bff);
			System.out.println(output);
		}
	}
	
	
}