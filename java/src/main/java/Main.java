import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        try (PrintWriter out = new PrintWriter(System.out)) {
            Solution solution = new Solution();
            solution.in = new InputReader(getInput());
            solution.out = out;
            solution.solve();
        }
    }

    static InputStream getInput() {
        String inputFile = getInputFileName();
        if (inputFile == null) {
            return System.in;
        }
        try {
            return new FileInputStream(Main.class.getClassLoader().getResource(inputFile).getFile());
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    static String getInputFileName() {
        try {
            return System.getProperty("compet.input");
        } catch (Exception ex) {
            return null;
        }
    }
}

class Solution {
    InputReader in;
    PrintWriter out;

    void solve() {
    }
}

class InputReader {
    BufferedReader reader;
    StringTokenizer tokenizer;

    InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }

    String next() {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(reader.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }

    int nextInt() {
        return Integer.parseInt(next());
    }

    long nextLong() {
        return Long.parseLong(next());
    }
}
