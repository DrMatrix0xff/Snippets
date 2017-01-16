/*
 * Module name: Laread.java
 * Create on Mon, Jan 09 2017
 *
 */

import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.IOException;

public class Laread {
    public static void main(String[] args) {
        if (args.length == 1) {
            String filename = args[0];
            try {
                FileInputStream fs = new FileInputStream(filename);
                InputStreamReader ir = new InputStreamReader(fs, "UTF-8");
                StringBuilder content = new StringBuilder();
                for (int c = ir.read(); c != -1; c = ir.read())
                    content.append((char) c);
                System.out.print(content);
            } catch (IOException ex) {
                System.err.println(ex);
            }
        }
    }
}

