import java.util.*;
import java.io.*;
import java.math.*;

public class Roman {
    public void run() throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("RomanIN.txt"));
        int n = Integer.parseInt(br.readLine());
        while (n-->0) {
            String s = br.readLine();
            System.out.println(solve(Integer.parseInt(s)));
        }
    }
    
    public String solve(int dec) {
        String ans = "";
        int thousands = dec / 1000;
        for (int i = 0; i < thousands; i++) {
            ans += "M";
        }
        int hundreds = dec % 1000 / 100;
        switch(hundreds) {
            case 9:
                ans += "CM";
                break;
            case 4:
                ans += "CD";
                break;
            default:
                if (hundreds >= 5) {
                    ans += "D";
                    hundreds -= 5;
                }
                for (int i = 0; i < hundreds; i++) {
                    ans += "C";
                }
        }
        int tens = dec % 100 / 10;
        switch(tens) {
            case 9:
                ans += "XC";
                break;
            case 4:
                ans += "XL";
                break;
            default:
                if (tens >= 5) {
                    ans += "L";
                    tens -= 5;
                }
                for (int i = 0; i < tens; i++) {
                    ans += "X";
                }
        }
        int ones = dec % 10;
        switch(ones) {
            case 9:
                ans += "IX";
                break;
            case 4:
                ans += "IV";
                break;
            default:
                if (ones >= 5) {
                    ans += "V";
                    ones -= 5;
                }
                for (int i = 0; i < ones; i++) {
                    ans += "I";
                }
        }
        return ans;
    }
    
    public static void main (String[] args) throws Exception {
        new Roman().run();
    }
}


//import java.util.*;
//import java.io.*;
//import java.math.*;
//
//public class Roman {
//    public void run() throws Exception {
//        BufferedReader br = new BufferedReader(new FileReader("RomanIN.txt"));
//        int n = Integer.parseInt(br.readLine());
//        while (n-->0) {
//            String s = br.readLine();
//            System.out.println(solve(s));
//        }
//    }
//    
//    public int solve(String rn) {
//        rn = rn.toUpperCase();
//        int ans = 0;
//        for (int i = 0; i < rn.length(); i++) {
//            char c = rn.charAt(i);
//            int cv = value(c);
//            if (i+1 < rn.length()) {
//                char n = rn.charAt(i+1);
//                int nv = value(n);
//                if (cv < nv) {
//                    ans += nv - cv;
//                    i++;
//                    continue;
//                }
//            }
//            ans += cv;
//        }
//        return ans;
//    }
//    
//    public int value(char c) {
//        switch(c) {
//            case 'I' : return 1;
//            case 'V' : return 5;
//            case 'X' : return 10;
//            case 'L' : return 50;
//            case 'C' : return 100;
//            case 'D' : return 500;
//            case 'M' : return 1000;
//        }
//        return 0;
//    }
//    
//    public static void main (String[] args) throws Exception {
//        new Roman().run();
//    }
//}
