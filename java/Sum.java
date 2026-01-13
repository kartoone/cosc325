import java.util.Scanner;

public class Sum {

    static int sum(int n) {
        int i;
        int total = 0;
        for (i=1; i<=n; i++) {
            total += i;
        }
        return total;
    }

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int n = Integer.parseInt(in.nextLine());
        System.out.printf("%d\n", sum(n));    
    }

}
