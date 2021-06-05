import java.util.Scanner;

public class groot {
	//each index corresponds to a spot in our delta arrays
	public static int [] dx = {0, 1, 0, -1};
	public static int [] dy = {1, 0, -1, 0};
	public static int ex, ey, ed;
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
		// 0 = N, 1 = E, 2 = S, 3 = W
		String dir = "NESW";
		
		int n = in.nextInt();
		ex = in.nextInt();
		ey = in.nextInt();
		ed = dir.indexOf(in.next());

		char [] ins = in.next().toCharArray();
		String pot = "FBLR";
		
		//brute force each instruction
		if(go(ins)) {
			System.out.println(0);
			return;
		}
		
		for (int i = 0; i < ins.length; i++) {
			//try changing this instruction
			for (int j = 0; j < pot.length(); j++) {
				if(pot.charAt(j) == ins[i]) continue;
				char prev = ins[i];
				ins[i] = pot.charAt(j);
				if(go(ins)) {
					System.out.println(i+1 + " " + ins[i]);
					return;
				}
				ins[i] = prev;
			}
		}
		
		System.out.println(-1);
		
	}
	public static boolean go(char [] ins) {		
		int x = 0;
		int y = 0;
		int d = 0;
		
		for (int i = 0; i < ins.length; i++) {
			if(ins[i] == 'F') {
				x += dx[d];
				y += dy[d];
			}
			else if(ins[i] == 'B') {
				x -= dx[d];
				y -= dy[d];
			} else if(ins[i] == 'L') {
				d -= 1;
				d += 4;
				d %= 4;
			} else {
				d += 1;
				d %= 4;
			}
		}
		
		return x == ex && y == ey && d == ed;
	}
}
