import java.io.*;
import java.util.*;

public class Main {
	public static String translate(String message, Map<String, String> map) {
	    return "";
	}

	// Do not modify below this line
	public static void main(String[] args) throws Exception {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.valueOf(reader.readLine());
		
		for (int i = 0; i < t; i++) {
			String sentence = reader.readLine();
			int mappingCount = Integer.parseInt(reader.readLine());
			Map<String, String> map = new HashMap<String, String>();
			for (int j = 0; j < mappingCount; j++) {
			    String[] mapping = reader.readLine().split(" ");
			    map.put(mapping[0], mapping[1]);
			}
			String output = translate(sentence, map);
			System.out.println(output);
		}
	}
}