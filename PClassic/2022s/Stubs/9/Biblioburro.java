import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;

class Biblioburro {

    public static boolean efficientTrip(long[] mountainList) {
        return true;
    }


    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(reader.readLine());
        while (t-- > 0) {
            int length = Integer.parseInt(reader.readLine());
            long[] mountainList = new long[length];
            String[] elements = reader.readLine().split(" ");
            for (int i = 0; i < length; i++) {
                mountainList[i] = Long.parseLong(elements[i]);
            }
            boolean result = efficientTrip(mountainList);
            if (result) {
                System.out.println(1);
            } else {
                System.out.println(0);
            }
        }
    }
}
