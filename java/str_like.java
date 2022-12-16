/*
// Java's string is just like C++, which is fixed once created... Which sounds like kind of waste to me after I knew whenever you str1+str2 is acctually creating a new string.
public class test {
    public static void main(String[] args) {
        str a = new str();
        a.add("HELLO");
        a.add(" ");
        a.add("WORLD");

        System.out.println(a.size());
        str.cout(a.size());

        System.out.println(a.to_string());
        a.cout();
        str.cout("HELLO WORLD");
        char[] ch_array = { 'H', 'E', 'L', 'L', 'O', ' ', 'W', 'O', 'R', 'L', 'D' };
        str.cout(ch_array);
        str.cout(a);

        System.out.println(a.slice(1).to_string());// this will also change the instance same time
        System.out.println(a.slice(1, a.size()).to_string());
    }
}

11
11
HELLO WORLD
HELLO WORLD
HELLO WORLD
HELLO WORLD
HELLO WORLD
ELLO WORLD
LLO WORLD

*/


import java.util.Vector;

interface str_like {
    void add(String str);

    str slice(int... index);

    void replace(String destination, String source);

    boolean equal(String str);

    char index();

    int size();

    void clear();

    static void cout(str string) {
    }

    static void cout(String string) {

    }

    static void cout(char[] string) {

    }

    static void cout(Vector<Character> string) {

    }
}

class str implements str_like {
    Vector<Character> buffer = new Vector<>();
    private int size = 0;

    str(String str) {
        for (; this.size < str.length(); this.size++) {
            buffer.add(str.charAt(this.size));
        }
    }

    str() {

    }

    public void add(String str) {
        for (int i = 0; i < str.length(); i++) {
            buffer.add(str.charAt(i));
            size++;
        }
    }

    public str slice(int... index) {
        // add -1 and suchthing
        if ((index.length == 0) || (index.length > 2)) {
            return this;
        }

        if (index.length != 1) {
            if ((index[0] > size) || (index[1] > size)) {
                return this;
            }
            if (index[0] > index[1]) {
                return this;
            }
            for (int i = size - 1; i >= 0; i--) {
                if (i > index[1] || i < index[0]) {
                    buffer.remove(i);
                }
            }

        } else {

            if (index[0] > size) {
                return this;
            }

            for (int i = size - 1; i >= 0; i--) {
                if (i < index[0]) {
                    buffer.remove(i);
                }
            }
        }

        return this;
    }

    public void replace(String destination, String source) {
    }

    public boolean equal(String str) {
        return true;
    }

    public int size() {
        return this.size;
    }

    public static int size(str str) {
        return str.size;
    }

    public void clear() {
        buffer.clear();
    }

    public char index() {
        return '0';
    }

    public String to_string() {
        StringBuilder res = new StringBuilder(0);
        for (int i = 0; i < buffer.size(); i++) {
            res.append(buffer.elementAt(i));
        }
        return res.toString();
    }

    public static void newline() {
        System.out.println();
    }

    void cout() {
        System.out.println(this.to_string());
    }

    public static void cout(str string) {
        string.cout();
    }

    public static void cout(Number num) {
        System.out.println(num);
    }

    public static void cout(String string) {
        System.out.println(string);
    }

    public static void cout(char[] string) {
        System.out.println(string);
    }

    public static void cout(Vector<Character> string) {
        for (int i = 0; i < string.size(); i++) {
            System.out.print(string.elementAt(i));
        }
        System.out.println();
    }
}
