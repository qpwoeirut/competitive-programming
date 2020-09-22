import java.io.*;
import java.util.*;

class Move {
	byte dir;
	int len;
}

public class Greetings {
	public static void main(String args[]) throws IOException {
		Scanner sc = new Scanner(new File("greetings.in"));
		int bCount = sc.nextInt();
		int eCount = sc.nextInt();
		Queue<Move> bMoves = new LinkedList<Move>();
		Queue<Move> eMoves = new LinkedList<Move>();
		for (int i = 0; i < bCount; i++) {
			Move tmp = new Move();
			tmp.len = sc.nextInt();
			if (sc.next().charAt(0) == 'L') {
				tmp.dir = -1;
			} else {
				tmp.dir = 1;
			}
			bMoves.add(tmp);
		}
		for (int i = 0; i < eCount; i++) {
			Move tmp = new Move();
			tmp.len = sc.nextInt();
			if (sc.next().charAt(0) == 'L') {
				tmp.dir = -1;
			} else {
				tmp.dir = 1;
			}
			eMoves.add(tmp);
		}
		sc.close();
		
		int meetings = 0;
		int bDistLeft = 0, eDistLeft = 0;
		int bPos = 0, ePos = 0;
		byte bDir = 0, eDir = 0;
		byte relation = 0;
		Move bMove, eMove;
		while (!bMoves.isEmpty() || !eMoves.isEmpty()) {
			if (bDistLeft == 0 && !bMoves.isEmpty()) {
				bMove = bMoves.poll();
				bDistLeft = bMove.len;
				bDir = bMove.dir;
			}
			if (eDistLeft == 0 && !eMoves.isEmpty()) {
				eMove = eMoves.poll();
				eDistLeft = eMove.len;
				eDir = eMove.dir;
			}

			if (bDistLeft >= eDistLeft) {
				if (eDistLeft > 0) {
					bPos += eDistLeft * bDir;
					ePos += eDistLeft * eDir;
					bDistLeft -= eDistLeft;
					eDistLeft = 0;
				} else {
					bPos += bDistLeft * bDir;
					bDistLeft = 0;
				}
			} else {
				if (bDistLeft > 0) {
					bPos += bDistLeft * bDir;
					ePos += bDistLeft * eDir;
					eDistLeft -= bDistLeft;
					bDistLeft = 0;
				} else {
					ePos += eDistLeft * eDir;
					eDistLeft = 0;
				}
			}

			if (bPos < ePos) {
				if (relation == 1) {
					meetings++;
				}
				relation = -1;
			} else if (bPos == ePos) {
				if (relation != 0) {
					meetings++;
				}
				relation = 0;
			} else {
				if (relation == -1) {
					meetings++;
				}
				relation = 1;
			}
		}

		PrintStream fout = new PrintStream("greetings.out");
		fout.print(meetings);
		fout.flush();
		fout.close();
	}
}
