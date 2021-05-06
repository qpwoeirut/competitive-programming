import java.util.*;

public class program {
	
	public static void main(String[]args) {
		
		Scanner s = new Scanner(System.in);
		String str = s.nextLine();
		s.close();

		for(int i=0; i<str.length()-2; i+=3) {
			switch(str.substring(i, i+3)) {
				case "LLL": System.out.print("A"); break;
				case "SSL": System.out.print("T"); break;
				case "SLL": System.out.print("G"); break;
				case "SLS": System.out.print("C"); break;
			}
		}
        System.out.print("\n");
	}
}
