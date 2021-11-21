import java.util.Arrays;
import java.io.*;


public class StudyingMagic {

	static int findTriples (int[] A) {
	Arrays.sort(A);
	long[] newA = new long[A.length];
	int curr = A[0];
    int curri = 0;
	newA[0] = 1;
	for(int i = 1; i < A.length; i++) {
		if (A[i] == curr) {
			newA[curri] ++;
		} else {
			curri++;
			curr = A[i];
			newA[curri] = 1;
		}
	}

	long[] sumToEnd = new long [curri+1];
	sumToEnd[curri] = newA[curri];
	for(int i = curri-1; i >=0; i--) {
		sumToEnd[i] = sumToEnd[i+1] + newA[i];
	}

	long[] squareSumToEnd = new long [curri+1];
	squareSumToEnd[curri] = newA[curri]*newA[curri] ;
	for(int i = curri-1; i >= 0; i--) {
		squareSumToEnd[i] = (squareSumToEnd[i+1] + newA[i]*newA[i]);
	}

	long ans = 0;
    for(int i = 0; i <= curri-2; i++) {
    	ans = (ans + (newA[i] * (sumToEnd[i+1]*sumToEnd[i+1] - squareSumToEnd[i+1]) / 2)) % (1000000007);
    }
    return (int) ans;
    }


	public static void main(String[] args) throws NumberFormatException, IOException{
		File filein = new File("StudyingMagicIN.txt");
		String st;
		BufferedReader br = new BufferedReader(new FileReader(filein));

		while ((st = br.readLine()) != null){
			String[] temp = st.split(" ");
			int[] A = new int[temp.length];
			int count = 0;
			for (String i: temp) {
				A[count] = Integer.parseInt(i);
				count++;
			}
			int ans = findTriples(A);
			System.out.println(ans);
		}
		br.close();
	}



}
