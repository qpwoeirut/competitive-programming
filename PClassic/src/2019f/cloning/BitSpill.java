import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;

public class BitSpill {
	
	public static void main(String[] args) throws IOException{
		
		BufferedReader br = new BufferedReader(new FileReader("BitSpillIN.txt"));
		
	    
		while (br.ready()) {
			String s = br.readLine();
			
			if (!s.trim().isEmpty()) {
				String[] data = s.split("-");
				
				//parse the source nodes
				ArrayList<Integer> sourcesX = new ArrayList<Integer>();
				ArrayList<Integer> sourcesY = new ArrayList<Integer>();
				String srcString = data[0].substring(1,data[0].length()-2);
				while (srcString.indexOf(']') != -1) {
					int endPos = srcString.indexOf(']');
					int startPos = srcString.indexOf('[');
					String[] xy = srcString.substring(startPos+1, endPos).split(", ");
					sourcesX.add(Integer.parseInt(xy[0]));
					sourcesY.add(Integer.parseInt(xy[1]));
					srcString = srcString.substring(endPos+1);
				}
				int[][] src = new int[sourcesX.size()][2];
				for (int i = 0; i < sourcesX.size(); i++) {
					src[i][0] = sourcesX.get(i);
					src[i][1] = sourcesY.get(i);
				}
				
				
				//parse the matrix
				ArrayList<String[]> matrixNodes = new ArrayList<String[]>();
				int dim;
				String matrixString = data[1].substring(2,data[1].length()-1);
				while (matrixString.indexOf(']') != -1) {
					int endPos = matrixString.indexOf(']');
					int startPos = matrixString.indexOf('[');
					String[] nodes = matrixString.substring(startPos+1, endPos).split(", ");
					matrixNodes.add(nodes);
					matrixString = matrixString.substring(endPos+1);
					
				}
				dim = matrixNodes.size();
				int[][] matrix = new int[dim][dim];
				for (int i = 0; i < dim; i++) {
					for (int j = 0; j < dim; j++) {
						matrix[i][j] = Integer.parseInt(matrixNodes.get(i)[j]);
					}
				}
				
				
				String ans = Arrays.deepToString(bitSpill(matrix,src));
				System.out.println(ans);
				
			}
		}
		br.close();
		
		
		 
		
	 }
	
	
	static void spillHelper(int x, int y, int[][] matrix, int srcColor) {
		LinkedList<Integer> xcoords = new LinkedList<Integer>();
		LinkedList<Integer> ycoords = new LinkedList<Integer>();
		
		xcoords.add(x);
		ycoords.add(y);
		
		while (!xcoords.isEmpty()) {
			int xn = xcoords.removeFirst();
			int yn = ycoords.removeFirst();
			if (matrix[xn][yn] == srcColor) {
				matrix[xn][yn] = 1 - matrix[xn][yn];
				if (xn > 0) {
					xcoords.add(xn-1);
					ycoords.add(yn);
				} 
				if (xn < matrix.length - 1) {
					xcoords.add(xn+1);
					ycoords.add(yn);
				}
				if (yn > 0) {
					xcoords.add(xn);
					ycoords.add(yn-1);
				}
				if (yn < matrix.length - 1) {
					xcoords.add(xn);
					ycoords.add(yn+1);
				}
			}
		}
		
		
	}
	
	public static int[][] bitSpill(int[][] matrix, int[][] src) {
		for (int i = 0; i < src.length; i++) {
			spillHelper(src[i][0],src[i][1],matrix, matrix[src[i][0]][src[i][1]]);
		}
		return matrix;
	}

}
