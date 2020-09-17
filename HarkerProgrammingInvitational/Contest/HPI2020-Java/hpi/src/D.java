import java.util.Scanner;

public class D {
	static Scanner scanner = new Scanner(System.in);
	static double N,K;
	public static void main(String[] argv) {
		N = scanner.nextInt();
		K = scanner.nextDouble();
		double sum = 0.0d;
		System.out.println(K);
		for(int n = 0; n < N; n++) {
			sum = sum + K/100d;
			System.out.println(K);

			K = Math.floor(K/2);
		}
		System.out.println(sum*1000);
		
	}
}
