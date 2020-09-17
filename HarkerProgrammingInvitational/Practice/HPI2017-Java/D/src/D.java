import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class D {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		
		ArrayList<Float> list = new ArrayList<Float>();
		float n = (float)scanner.nextInt(); // cast to float
		for(int i = 0; i < n; i++) {
			list.add((float)(scanner.nextInt() / scanner.nextInt()));
		}
		System.out.println(list.indexOf(Collections.max(list)) + 1);
	}
}