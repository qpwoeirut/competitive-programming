import java.util.*;

public class solution {
	
	static int[][] matrix;
	static int[] rows, cols;
	static int diag1, diag2;
	static boolean[] count;
	static Scanner s = new Scanner(System.in);
	
	public static void main(String[]args) {
		int Q = s.nextInt();
		for(int i=0; i<Q; i++){
			System.out.println(check());
		}
	}
	
	public static int check() {
		int N = s.nextInt();
		matrix = new int[N][N];
		rows = new int[N];
		cols = new int[N];
		
		for(int i=0; i<N; i++) 
			for(int j=0; j<N; j++)
				matrix[i][j] = s.nextInt();
		
		for(int i=0; i<N; i++) {
			rows[i] = 0;
			cols[i] = 0;
			diag1 = diag2 = 0;
		}
		
		for(int i=0; i<N; i++) {
			diag1 += matrix[i][i];
			diag2 += matrix[i][N-i-1];
		}
		if(diag1 != diag2) return 0; 
		
		for (int i=0; i<N; i++)
	        for (int j=0; j<N; j++)
	        {
	            rows[i] += matrix[i][j];
	            cols[j] += matrix[i][j];
	        }

		for (int i=0; i<N; i++)
	        if (rows[i] != diag1 || cols[i] != diag1)
	            return 0;
	
		return 1;
	}
}
