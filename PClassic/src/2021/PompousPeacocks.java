//import java.util.*;
//import java.io.*;
//
//public class Main {
//    public static void main(String[] args) throws Exception {
//        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//        int tests = Integer.parseInt(br.readLine());
//        for (int i = 0; i < tests; i++) {
//            List<List<Integer>> peacockStats = new ArrayList<>();
//            int pos = 0;
//            while (true) {
//                String peacockStatsLine = br.readLine();
//                if (peacockStatsLine == null || peacockStatsLine.equals(""))
//                    break;
//                peacockStats.add(new ArrayList<Integer>());
//
//                String[] peacockStat = peacockStatsLine.split(" ");
//                peacockStats.get(pos).add(Integer.parseInt(peacockStat[0]));
//                peacockStats.get(pos).add(Integer.parseInt(peacockStat[1]));
//                pos++;
//            }
//
//            int[][] peacocks = new int[peacockStats.size()][peacockStats.get(0).size()];
//
//            for (int k = 0; k < peacockStats.size(); k++) {
//                for (int j = 0; j < peacockStats.get(0).size(); j++) {
//                    peacocks[k][j] = peacockStats.get(k).get(j);
//                }
//            }
//
//            System.out.println(unbeatable(peacocks));
//        }
//        br.close();
//    }
//    // Do not modify above this line
//
//    public static int unbeatable(int[][] peacocks) {
//        return 0;
//    }
//
//}