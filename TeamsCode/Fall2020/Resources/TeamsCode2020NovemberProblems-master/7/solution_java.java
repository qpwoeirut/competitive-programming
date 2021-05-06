import java.util.*;

public class program {
	public static void main(String[]args) {
		Scanner s = new Scanner(System.in);
		int N = s.nextInt();
		int M = s.nextInt();
		int[] arr = new int[N];
		for(int i=0; i<M; i++)
			arr[s.nextInt()-1] += s.nextInt();
		for(int i=0; i<N; i++)
			System.out.printf("%d ", arr[i]);
		System.out.println();
		s.close();
	}
}
