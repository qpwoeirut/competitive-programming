import java.util.*;

public class solution {
  public static void main(String[]args) {
		Scanner s = new Scanner(System.in);
		StringTokenizer st = new StringTokenizer(s.nextLine(), ":");
		int h = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int c = s.nextInt();
		
		System.out.printf("%02d:%02d\n", (h+(m+c)/60)%24, (m+c)%60);
		s.close();
	}
}
