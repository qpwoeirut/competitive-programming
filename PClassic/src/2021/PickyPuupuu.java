//import java.io.BufferedReader;
//import java.io.InputStreamReader;
//import java.util.*;
//import java.util.stream.*;
//import static java.util.stream.Collectors.toList;
//
//public class Main {
//    public static void main(String[] args) throws Exception {
//      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//      int tests = Integer.parseInt(br.readLine());
//      for (int i = 0; i < tests; i++) {
//          List<List<Integer>> arr = new ArrayList<>();
//
//          while (true) {
//              String s = br.readLine();
//              if (s.equals("")) {
//                  break;
//              }
//              arr.add(Stream.of(s.trim().split(" ")).map(Integer::parseInt).collect(toList()));
//          }
//
//          int[][] grid = new int[arr.size()][arr.get(0).size()];
//
//          for (int k = 0; k < arr.size(); k++) {
//              for (int j = 0; j < arr.get(0).size(); j++) {
//                  grid[k][j] = arr.get(k).get(j);
//              }
//          }
//
//          if (magicSquare(grid)) {
//              System.out.println("true");
//          } else {
//              System.out.println("false");
//          }
//      }
//      br.close();
//    }
//    // Do not modify above this line
//
//    public static boolean magicSquare(int[][] grid) {
//        return false;
//    }
//}