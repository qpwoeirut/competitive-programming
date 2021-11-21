import java.io.BufferedReader;
import java.io.FileReader;

public class SnapSave {
	//Do not modify below this line
	public void run() throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("SnapSaveIN.txt"));
        String line;
        while ((line = br.readLine()) != null) {
            String[] numbersString = line.split(" ");
            int[] numbers = new int[numbersString.length];
            for (int i = 0; i < numbersString.length; i++) {
                numbers[i] = Integer.parseInt(numbersString[i]);
            }
            System.out.println(findPeak(numbers));
        }
        br.close();
	}
	
    public static void main(String[] args) throws Exception {
        new SnapSave().run();
    }
    //Do not modify above this line
	
    public static int findPeak(int[] numbers) {
    	int prev = numbers[0];
        for (int i = 0; i < numbers.length - 1; i++) {
        	if (numbers[i] >= numbers[i + 1] && numbers[i] >= prev) {
        		return i;
        	}
        }
        return numbers.length - 1;
    }
}
