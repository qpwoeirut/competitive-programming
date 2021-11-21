import java.io.BufferedReader;
import java.io.FileReader;

public class FlyingQuiz {
	//Do not modify below this line
	public void run() throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("FlyingQuizIN.txt"));
        String line;
        while ((line = br.readLine()) != null) {
            String[] numbersString = line.split(" ");
            int[] numbers = new int[numbersString.length];
            for (int i = 0; i < numbersString.length; i++) {
                numbers[i] = Integer.parseInt(numbersString[i]);
            }
            System.out.println(findMinDiff(numbers));
        }
        br.close();
	}
    
    public static void main(String[] args) throws Exception {
        new FlyingQuiz().run();
    }
    //Do not modify above this line
    
    public static int findMinDiff(int[] numbers) {
        int min = 2147483640;
        for (int i = 0; i < numbers.length - 1; i++) {
        	if (Math.abs(numbers[i + 1] - numbers[i]) < min) {
        		min = Math.abs(numbers[i + 1] - numbers[i]);
            }
        }
        return min;
    }

}