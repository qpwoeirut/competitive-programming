import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import java.util.ArrayList;

public class TrickOrTreat {
	
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new FileReader("TrickOrTreatIN.txt"));
	
		while (br.ready()) {
			String s = br.readLine();
			if (!s.trim().isEmpty()) {
				String[] data = s.split(" ");
				int numWizards = Integer.parseInt(data[0]); 
				
				data = br.readLine().split(" ");
				int kL = Integer.parseInt(data[0]);
				int kR = Integer.parseInt(data[1]);
				int[][] candies = new int[numWizards][2];
				for (int i = 0; i < numWizards; i++) {
					data = br.readLine().split(" ");
					candies[i][0] = Integer.parseInt(data[0]);
					candies[i][1] = Integer.parseInt(data[1]);
				}
				
				System.out.println(trickOrTreat(kL,kR,candies));
				
				
				
			}
			
		}
		br.close();
		
		 
		
	 }

	
	static int kingLeft, kingRight;
	static int[][] ministerCoins;
	static ArrayList<int[]> coinProduct;
	static ArrayList<int[]> ministerLeft;
	static ArrayList<int[]> ministerRight;
	static ArrayList<Integer> lenLeft;
	static ArrayList<Integer> lenRight;
	
	
	static final int cSize = 3601;
	static final int productSize = 100001;
	static int[] product;
	static int[] max;
	
	
	static void processOneNum(int temp, ArrayList<int[]> num, ArrayList<Integer> len) {
		
		int[] tempArr = new int[6];
		int index = 0;
		while (temp > 0) {
			tempArr[index] = (int) (temp % 10);
			temp = temp / 10;
			index++;
		}
		num.add(tempArr);
		
		len.add(index);
		
		
	}
	
	static void processData() {
		for (int i = 0; i < ministerCoins.length; i++) {
			int temp = ministerCoins[i][0];
			processOneNum(temp, ministerLeft,lenLeft);
			temp = ministerCoins[i][1];
			processOneNum(temp, ministerRight, lenRight);
		}
	}
	
	
	
	static void multiplyLeftRight() {
		
		
		for (int n = 0; n < ministerCoins.length; n++) {
			int[] c = new int[cSize];
			for (int i = 0; i < lenLeft.get(n); i++) {
				int x = 0;
				for (int j = 0; j < lenRight.get(n); j++) {
					c[i+j] += x + ministerLeft.get(n)[i] * ministerRight.get(n)[j];
					x = c[i+j]/10;
					c[i+j] %= 10;
				}
				c[i+lenRight.get(n)] = (int) x;
			}
			coinProduct.add(c);
		}
		
		
	}
	
	static int compareTwoNum(int[] c, int[] pivot) {
		for (int i = cSize - 1; i >= 0; i--) {
			if (c[i] > pivot[i]) {
				return 1;
			} else if (c[i] < pivot[i]) {
				return -1;
			}
		}
		return 0;
	}
	
	static int partition(int begin, int end) {
		int[] pivot = coinProduct.get(end);
		int i = begin - 1;
		for (int j = begin; j < end; j++) {
			if (compareTwoNum(coinProduct.get(j),pivot) < 0) {
				i++;
				int[] temp = coinProduct.get(i);
				coinProduct.set(i, coinProduct.get(j));
				coinProduct.set(j, temp);
				temp = ministerLeft.get(i);
				ministerLeft.set(i, ministerLeft.get(j));
				ministerLeft.set(j, temp);
				temp = ministerRight.get(i);
				ministerRight.set(i, ministerRight.get(j));
				ministerRight.set(j, temp);
			}
		}
		int[] temp = coinProduct.get(i+1);
		coinProduct.set(i+1, coinProduct.get(end));
		coinProduct.set(end, temp);
		temp = ministerLeft.get(i+1);
		ministerLeft.set(i+1, ministerLeft.get(end));
		ministerLeft.set(end, temp);
		temp = ministerRight.get(i+1);
		ministerRight.set(i+1, ministerRight.get(end));
		ministerRight.set(end, temp);
		return i+1;
	}
	
	static void quickSort(int begin, int end) {
		if (begin < end) {
			int pIndex = partition(begin,end);
			quickSort(begin, pIndex-1);
			quickSort(pIndex+1, end);
		}
	}
	
	static void sortByProduct() {
		quickSort(0,coinProduct.size() - 1);
		
	}
	
	static void multiplyLeftCoin(int[] bs) {
		int[] c = new int[productSize];
		int l = productSize;
		while (product[l-1] == 0) {
			l--;
		}
		for (int i = 0; i < bs.length; i++) {
			int x = 0;
			for (int j = 0; j < l; j++) {
				c[i+j] += x + product[j] * bs[i];
				x = c[i+j]/10;
				c[i+j] %= 10;
			}
			c[i+l] = (int) x;
		}
		product = c;
		
		
		
	}
	
	static void divideByRightCoin(int[] ds) {
		int l = productSize;
		while (product[l-1] == 0) {
			l--;
		}
		
		int m = 0;
		int mul = 1;
		int b = 0;
		
		boolean hasSeenNonZero = false;
		while (!hasSeenNonZero || ds[m] > 0) {
			if (ds[m] > 0) {
				hasSeenNonZero = true;
			}
			b += mul*ds[m];
			mul *= 10;
			m++;
		}
		
		
		int[] c = new int[productSize];
		int x = 0;
		
		for (int i = l-1; i >= 0; i--) {
			x = x * 10 + product[i];
			c[i] = (int) (x / b);
			x = x % b;
		}
		
		if (compareTwoNum(c,max) > 0) {
			max = c;
		}
		
		
	}
	
	static void calcCoins() {
		
		int temp = kingLeft;
		int index = 0;
		while (temp > 0) {
			product[index] = (int) (temp % 10);
			temp = temp / 10;
			index++;
		}
		
		
		for (int i = 0; i < ministerLeft.size(); i++) {
			divideByRightCoin(ministerRight.get(i));
			multiplyLeftCoin(ministerLeft.get(i));
		}
	}
	
	
	
	
	
	public static String trickOrTreat(int kL, int kR, int[][] candies) {
		kingLeft = kL;
		kingRight = kR;
		ministerCoins = candies;
		coinProduct = new ArrayList<int[]>();
		ministerLeft = new ArrayList<int[]>();
		ministerRight = new ArrayList<int[]>();
		lenLeft = new ArrayList<Integer>();
		lenRight = new ArrayList<Integer>();
		product = new int[productSize];
		max = new int[cSize];
		
		
		processData();
		multiplyLeftRight();
		sortByProduct();
		calcCoins();
		
		StringBuilder ans = new StringBuilder();
		int i = 0;
		while (i < cSize) {
			ans.insert(0, max[i]);
			i++;
		}
		
		while (ans.charAt(0) == '0') {
			ans.deleteCharAt(0);
		}
		
		return ans.toString();
	}
	
	
	
}

