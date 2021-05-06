import java.util.*;

public class solution {
	public static void main(String[]args) {
		Scanner s = new Scanner(System.in);
		char c = s.next().charAt(0);
		String str = s.nextLine();
		s.close();
		
		int sum = 0;
		for(int i=0; i<str.length(); i++)
			if(str.charAt(i)==c) sum++;
		System.out.println(sum);
	}
}
