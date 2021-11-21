import java.io.BufferedReader;
import java.io.FileReader;
import java.util.LinkedList;

public class Race {
    
	public int getRaceLength(int k, int[][] arr) {
		LinkedList<Integer> deque1 = new LinkedList<Integer>(); 
		deque1.add(0);
		int statue = BFS_max(new boolean[k], arr, deque1);
		LinkedList<Pair> deque2 = new LinkedList<Pair>(); 
		deque2.add(new Pair(statue, 0));
		return BFS_dist(new boolean[k], arr, deque2);
	}
	
	private int BFS_dist(boolean[] visited, int[][] adjMat, 
			LinkedList<Pair> deque) {
		Pair statue = null;
		while (!deque.isEmpty()) {
			statue = deque.pop();
			visited[statue.first] = true;
			for (int neighbor: adjMat[statue.first]) {
				if (!visited[neighbor]) {
					deque.addLast(new Pair(neighbor, statue.second + 1));
				}
			}
		}
		return statue.second;
	}
	
	private int BFS_max(boolean[] visited, int[][] adjMat, LinkedList<Integer> deque) {
		int statue = -1;
		while (!deque.isEmpty()) {
			statue = deque.pop();
			visited[statue] = true;
			for (int neighbor: adjMat[statue]) {
				if (!visited[neighbor]) {
					deque.addLast(neighbor);
				}
			}
		}
		return statue;
	}
	
	class Pair {
		int first;
		int second;
		
		public Pair(int x, int y) {
			first = x;
			second = y;
		}
	}
	
	//Do not modify below this line
	
    public void run() throws Exception {
    	BufferedReader br = new BufferedReader(new FileReader("RaceIN.txt"));
        String line;
        while ((line = br.readLine()) != null) {
        	int statueCount = Integer.parseInt(line);
        	int[][] arr = new int[statueCount][];
        	for (int j = 0; j < statueCount; j++) {
        		line = br.readLine();
        		String[] numbers = line.split(" ");
        		int[] adjStatues = new int[numbers.length];
        		for (int i = 0; i < numbers.length; i++) {
        			int statue = Integer.parseInt(numbers[i]);
		            adjStatues[i] = statue;
        		}
        		arr[j] = adjStatues;
        	}
    		int num = getRaceLength(statueCount, arr);
            System.out.println(num);
        	
        }
        br.close();
    }
    
    public static void main (String[] args) throws Exception {
        new Race().run();
    }
    //Do not modify above this line
}