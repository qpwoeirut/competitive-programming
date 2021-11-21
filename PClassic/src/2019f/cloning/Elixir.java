import java.util.*;
import java.io.*;
import java.math.*;

public class Elixir {
    
    char[][] m;
    int[][][] sm;
    int sr;
    int sc;
    
    public void run() throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("ElixirIN.txt"));
        int n = Integer.parseInt(br.readLine());
        while (n-->0) {
            String s = br.readLine();
            String[] sa = s.split(" ");
            int r = Integer.parseInt(sa[0]);
            int c = Integer.parseInt(sa[1]);
            char[][] m = new char[r][c];
            for (int i = 0; i < r; i++) {
                m[i] = br.readLine().toCharArray();
            }
            int result = solve(m);
            if (result < 0) {
                System.out.println("Can't escape!");
            }
            else {
                System.out.println("Escaped in " + result + " steps.");
            }
        }
    }
    
    public int solve(char[][] m) {
        this.m = m;
        int r = m.length;
        int c = m[0].length;
        sm = new int[r][c][4];
        sr = -1;
        sc = -1;
        int er = -1;
        int ec = -1;
        for (int i = 0; i < r ; i++) {
            for (int j = 0; j < c; j++) {
                Arrays.fill(sm[i][j], Integer.MAX_VALUE);
                if (m[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                if (m[i][j] == 'E') {
                    er = i;
                    ec = j;
                }
            }
        }
        solve2(sr, sc, 0, 0);
        int ans = Integer.MAX_VALUE;
        for (int i = 0; i < 4; i++) {
            ans = Math.min(ans, sm[er][ec][i]);
        }
        if (ans != Integer.MAX_VALUE) {
            return ans;
        } else {
            return -1;
        }
    }
    
    public void solve2(int r, int c, int steps, int dir) {
        if (r < 0 || r >= m.length || c < 0 || c >= m[r].length || m[r][c] == 'G' || sm[r][c][dir] <= steps) {
            return;
        }
        if (m[r][c] == 'E') {
            sm[r][c][dir] = steps;
            return;
        }
        if (caught(r, c, dir)) {
            return;
        }
        sm[r][c][dir] = steps;
        int newdir = (dir + 1) % 4;
        solve2(r, c, steps+1, newdir);
        solve2(r+1, c, steps+1, newdir);
        solve2(r-1, c, steps+1, newdir);
        solve2(r, c+1, steps+1, newdir);
        solve2(r, c-1, steps+1, newdir);
    }
    
    //dir = 0, 1, 2, 3 aka N, E, S, W
    public boolean caught(int r, int c, int dir) {
        switch(dir) {
        case 0 : //north
            for (int i = r; i < m.length; i++) {
                if (m[i][c] == 'G') {
                    return true;
                }
            }
            break;
        case 1 : //east
            for (int i = c; i >= 0; i--) {
                if (m[r][i] == 'G') {
                    return true;
                }
            }
            break;
        case 2 : //south
            for (int i = r; i >= 0; i--) {
                if (m[i][c] == 'G') {
                    return true;
                }
            }
            break;
        case 3 : //west
            for (int i = c; i < m.length; i++) {
                if (m[r][i] == 'G') {
                    return true;
                }
            }
            break;
        }
        return false;
    }
    
    
    public static void main (String[] args) throws Exception {
        new Elixir().run();
    }
}