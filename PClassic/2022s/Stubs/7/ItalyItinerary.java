import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
      int tests = Integer.parseInt(br.readLine());
      for (int i = 0; i < tests; i++) {
          String amount = br.readLine();
          int val = Integer.valueOf(amount);
          int itinerary[][] = new int[val][2];
          for(int j = 0; j < val; j++) {
        	  String value = br.readLine();
        	  String[] split = value.split(" ");
        	  itinerary[j][0] = Integer.valueOf(split[0]);
        	  itinerary[j][1] = Integer.valueOf(split[1]);
          }
         System.out.println(maximizeFun(itinerary));
      }
      br.close();
    }
    //Do not modify above this line
    
    public static int maximizeFun(int[][] itinerary) {
    	return 0;
    }
}