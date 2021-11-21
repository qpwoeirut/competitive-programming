//import java.util.*;
//import java.io.*;
//
//public class Main {
//
//    // Do not modify below this line
//    public static void main(String[] args) throws Exception {
//        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//        int tests = Integer.parseInt(br.readLine());
//        for (int i = 0; i < tests; i++) {
//            int n = Integer.parseInt(br.readLine());
//            int[][] rectangles = new int[n][4];
//            for (int j = 0; j < n; j++) {
//                String[] currRect = br.readLine().split(" ");
//                int[] newRect = new int[4];
//                for (int k = 0; k < 4; k++) {
//                    newRect[k] = Integer.valueOf(currRect[k]);
//                }
//                rectangles[j] = newRect;
//            }
//            System.out.println(area(rectangles));
//        }
//        br.close();
//    }
//    // Do not modify above this line
//
//    public static class Pair implements Comparable<Pair> {
//        public int x, y;
//        Pair(int x, int y) {
//            this.x = x;
//            this.y = y;
//        }
//
//
//        @Override
//        public int compareTo(Pair o) {
//            if (this.x != o.x) return Integer.compare(this.x, o.x);
//            return Integer.compare(this.y, o.y);
//        }
//    }
//
//    public static final int MX = 10010;
//    public static int[][] psum = new int[2][MX];
//
//    public static int area(int[][] rectangles) {
//        ArrayList<Pair> add = new ArrayList<>();
//        ArrayList<Pair> sub = new ArrayList<>();
//        for (final int[] rectangle : rectangles) {
//            add.add(new Pair(rectangle[1] + 1, rectangle[0] + 1));
//            sub.add(new Pair(rectangle[3] + 1, rectangle[0] + 1));
//            sub.add(new Pair(rectangle[1] + 1, rectangle[2] + 1));
//            add.add(new Pair(rectangle[3] + 1, rectangle[2] + 1));
//        }
//        Collections.sort(add);
//        Collections.sort(sub);
//
//        int a = 0, s = 0;
//        int ans = 0;
//
//        for (int y=0; y<MX; ++y) psum[0][y] = 0;
//
//        for (int x=1; x<MX; ++x) {
//            for (int y=0; y<MX; ++y) psum[x&1][y] = 0;
//            while (a < add.size() && add.get(a).x == x) {
//                ++psum[x&1][add.get(a).y];
////                System.out.println(x + "," + add.get(a).y);
//                ++a;
//            }
//            while (s < sub.size() && sub.get(s).x == x) {
//                --psum[x&1][sub.get(s).y];
////                System.out.println(x + " " + sub.get(s).y);
//                ++s;
//            }
//            for (int y=1; y<MX; ++y) {
//                psum[x&1][y] += psum[(x&1)^1][y] - psum[(x&1)^1][y-1] + psum[x&1][y-1];
//                if (psum[x&1][y] > 0) {
//                    ++ans;
//                }
////                if (x < 10 && y < 10) System.out.print(psum[x&1][y] + " ");
//            }
////            if (x < 10) System.out.println();
//        }
//
//        return ans;
//    }
//}