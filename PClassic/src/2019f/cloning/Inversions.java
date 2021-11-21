import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Inversions {
	// Before submitting, make sure the main method hasn't been changed!
    // DO NOT MODIFY BELOW THIS LINE
    
    public static void main(String[] args) throws IOException {
        Scanner fileInput = new Scanner(new FileReader("InversionsIN.txt"));

        int tests = Integer.parseInt(fileInput.nextLine());
        for(int i = 0; i < tests; i++) {
            String[] row = fileInput.nextLine().split(" ");
            int n = Integer.parseInt(row[0]);
            int k = Integer.parseInt(row[1]);
            int[] list = new int[n];
            row = fileInput.nextLine().split(" ");
            for(int j = 0; j < n; j++) {
            	list[j] = Integer.parseInt(row[j]);
            }
            System.out.println(solve(n, k, list));
        }
        fileInput.close();
    }   
    
    // DO NOT MODIFY ABOVE THIS LINE
    
    // Fill out the body of this method
    public static long solve(int n, int k, int[] list) {
    	int[] fen = new int[n+1];
    	long ans = 0;
    	int curr_inversions = 0;
    	int left = 0;
    	for(int right = 0; right < n; right++) {
    		int q = query(fen, list[right]);
			curr_inversions += (right - left - q);
    		update(fen, list[right], n, 1);
    		while(curr_inversions > k) {
    			update(fen, list[left], n, -1);
    			q = query(fen, list[left]);
    			curr_inversions -= q;
    			left++;
    		}
    		ans += right - left + 1;
    	}
        return ans;
    }
    
    public static void update(int[] fen, int index, int n, int val) {
    	while(index <= n) {
    		fen[index] += val;
    		index += index & (-index);
    	}
    }
    
    public static int query(int[] fen, int index) {
    	int ans = 0;
    	while(index > 0) {
    		ans += fen[index];
    		index -= index & (-index);
    	}
    	return ans;
    }
}
