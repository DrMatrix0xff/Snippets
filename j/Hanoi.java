

public class Hanoi {
    private static void move (int n, char a, char b, char c) {
        if (n <= 1) {
            System.out.printf("%c --> %c\n", a, c);
        } else {
            move(n-1, a, c, b);
            System.out.printf("%c --> %c\n", a, c);
            move(n-1, b, a, c);
        }
    }
    public static void main (String[] args) {
        int scale;
        if (args.length == 1) {
            try {
                scale = Integer.parseInt(args[0]);
            } catch (NumberFormatException e) {
                e.printStackTrace();
                return;
            }
            if (scale >= 1) {
                move(scale, 'A', 'B', 'C');
            }
        }
    }
}

