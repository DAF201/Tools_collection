import java.util.LinkedList;

@SuppressWarnings("unchecked")
public class hash_table {
    private int size = 10;
    private LinkedList<Integer>[] payload = new LinkedList[10];
    private int lambda = 31;
    private int items_added = 0;

    hash_table() {
        newPayload(size);
    }

    private void newPayload(int newSize) {
        payload = new LinkedList[newSize];
        for (int i = 0; i < payload.length; i++) {
            payload[i] = new LinkedList<Integer>();
        }
    }

    private int calculate_index(Object obj) {
        String obj_str = obj.toString();
        int result = 0;
        for (int i = 0; i < obj_str.length(); i++) {
            result += obj_str.charAt(i) * Math.pow(lambda, obj_str.length() - i);
        }
        return result % size;
    }

    private void rehash() {
        System.out.println("Rehashing, size: " + size);
        LinkedList<Integer>[] backup_copy = payload;
        size = size * 2;
        newPayload(size);
        for (LinkedList<Integer> busket : backup_copy) {
            for (Integer number : busket) {
                insert(number);
            }
        }
    }

    public int insert(int number) {
        int index = calculate_index(number);
        if (items_added / size >= 2) {
            rehash();
            insert(number);
        } else {
            // System.out.print(number + " ");
            payload[index].add(number);
            items_added++;
        }
        return index;
    }

    public void print() {
        // for (LinkedList<Integer> bucket : payload) {
        // for (Integer number : bucket) {
        // System.out.print(number + " ");
        // }
        // System.out.println();
        // }
        for (int i = 0; i < payload.length; i++) {
            // System.out.print(i + ": ");
            for (Integer number : payload[i]) {
                System.out.print(number + " ");
            }
            System.out.println();
        }
    }
}
