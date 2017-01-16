import java.util.Stack;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

class Worker {
class Task {
    public int n;
    public char a;
    public char b;
    public char c;
    public Task (int n, char a, char b, char c) {
        this.n = n; this.a = a; this.b = b; this.c = c;
    }
}

    private Stack<Task> tasks;
    private static final Logger logger = LogManager.getLogger("Hanoi.worker");

    public Worker () {
        tasks = new Stack<Task>();
        logger.info("stack has been initialized~");
    }

    public void printMove(int nt, char a, char b, char c) {
        Task t, t1;
        t = new Task(nt, a, b, c);
        tasks.push(t);
        while (! tasks.empty()) {
            t = tasks.pop();
            if (t.n <= 1) {
                System.out.printf("%c --> %c\n", t.a, t.c);
            } else {
                t1 = new Task(t.n - 1, t.b, t.a, t.c);
                tasks.push(t1);
                t1 = new Task(1, t.a, t.b, t.c);
                tasks.push(t1);
                t1 = new Task(t.n - 1, t.a, t.c, t.b);
                tasks.push(t1);
            }
        }
    }
}

public class ExHanoi {

    private static final Logger logger = LogManager.getLogger("Hanoi");

    public static void main(String[] args) {
        if (args.length == 1) {
            int ntask;
            Worker w = new Worker();
            try {
                ntask = Integer.parseInt(args[0]);
            } catch (NumberFormatException e) {
                // e.printStackTrace();
                logger.error("parse integer from command line input error, abort~");
                return;
            }
            if (ntask >= 1) {
                w.printMove(ntask, 'A', 'B', 'C');
                logger.info("solution has been found");
            } else {
                logger.warn("can not find any solutions for zero or negtive integer~");
            }
        }
    }
}
