//import java.io.*;
//
//public class Main {
//    public static void main(String[] args) throws Exception {
//        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
//        int t = Integer.parseInt(reader.readLine());
//        for (int q=0; q<t; q++) {
//            String[] sa = reader.readLine().split(" ");
//            int n = Integer.parseInt(sa[0]);
//            int k = Integer.parseInt(sa[1]);
//            int[][] hits = new int[k][3];
//            for (int i = 0; i < k; i++) {
//            	String[] sa2 = reader.readLine().split(" ");
//                hits[i][0] = Integer.parseInt(sa2[0]);
//                hits[i][1] = Integer.parseInt(sa2[1]);
//                hits[i][2] = Integer.parseInt(sa2[2]);
//
//            }
//            int count = netTemperature(n, hits);
//            System.out.println(count);
//        }
//        reader.close();
//    }
//
//    public static int netTemperature(int n, int[][] temperatures) {
//        return 0;
//    }
//}