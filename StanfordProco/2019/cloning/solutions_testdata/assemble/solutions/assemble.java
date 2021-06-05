import java.util.Scanner;

public class assemble {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
		String s = in.next();
		int [] f = new int[26];
		
		for (int i = 0; i < s.length(); i++) {
			f[s.charAt(i) - 'a']++;
		}
		int max = 0;
		int word = 0;
		for (int i = 0; i < f.length; i++) {
			if(f[i] > max) {
				max = f[i];
				word = i;
			}
		}
		
		System.out.println((char)(word + 'a'));
		System.out.println(s);
		
	}
}
