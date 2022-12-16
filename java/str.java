import java.util.Vector;

public class test {
    public static void main(String[] args) {
        str a = new str();
        a.add("Hello");
        a.add(" ");
        a.add("World");
        System.out.println(a.to_string());
        System.out.println(a.size());
        System.out.println(a.slice(1).to_string());
        System.out.println(a.slice(1, a.size()).to_string());

    }

    static void cout(str string) {

    }

    static void cout(String string) {

    }

    static void cout(char[] string) {

    }

    static void cout(Vector<Character> string) {

    }
}

interface str_like {
    void add(String str);

    str slice(int... index);

    void replace(String destination, String source);

    boolean equal(String str);

    char index();

    int size();

    void clear();
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
            if (index[0] > index[1]) {
                return this;
            }
            for (int i = size - 1; i >= 0; i--) {
                if (i > index[1] || i < index[0]) {
                    buffer.remove(i);
                }
            }
        } else {
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
}
