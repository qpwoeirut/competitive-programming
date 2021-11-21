import java.io.BufferedReader;
import java.io.FileReader;

public class PotionBrewing {
	
	public int getNumOfPotions(int n, int k) {
		int mod = 100000007;
		int[] arr = new int[n];
		int num = 0;
		for (int i = 0; i < n; i++) {
			arr[i]++;
			if (i - k >= 0) {
				num += arr[i - k];
				num = num % mod;
				arr[i] += num;
				arr[i] = arr[i] % mod;
			}
		}
		int count = 0;
		for (int i = 0; i < n; i++) {
			count += arr[i];
			count = count % mod;
		}
		return count + 1;
	}
	
	//Do not modify below this line
    public void run() throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("PotionBrewingIN.txt"));
        String line;
        while ((line = br.readLine()) != null) {
        	String[] numbers = line.split(" ");
            int days = Integer.parseInt(numbers[0]);
            int wizards = Integer.parseInt(numbers[1]);
            int num = getNumOfPotions(days, wizards);
            System.out.println(num);
        }
        br.close();
    }
    
    public static void main (String[] args) throws Exception {
        new PotionBrewing().run();
    }
    //Do not modify above this line
}
