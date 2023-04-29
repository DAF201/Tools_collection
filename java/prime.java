import java.math.BigInteger;

public class Main {
    public static void main(String[] args) {
        long n = 11;
        BigInteger b = new BigInteger(String.valueOf(n));
        long res = Long.parseLong(b.nextProbablePrime().toString());
        System.out.println(res);
    }
}
