import java.util.*;

public class solution {
	public static void main(String[]args) {
		Scanner s = new Scanner(System.in);
		int N = s.nextInt();
		int M = s.nextInt();
		int[][] arr = new int [N][M];
		for(int i=0; i<N; i++)
			for(int j=0; j<M; j++)
				arr[i][j] = s.nextInt();
		
		for(int j=0; j<M; j++){
		  for(int i=0; i<N; i++)
				System.out.printf("%d ", arr[i][j]);
			System.out.println();
		s.close();
		}
	}
}
