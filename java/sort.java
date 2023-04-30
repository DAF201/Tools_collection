
// package RV;
// import java.util.LinkedList;
import java.util.Arrays;

public class Main {
    static int compare = 0;
    static int swap_num = 0;

    public static void main(String[] args) {
        int[] sample = new int[5000];
        for (int i = 0; i < sample.length; i++) {
            sample[i] = 0 + (int) (Math.random() * ((50000 - 0) + 1));
        }
        bubble_sort(sample.clone());
        selection_sort(sample.clone());
        insertion_sort(sample.clone());
        quickSortAPI(sample.clone());
        merge_sort_API(sample.clone());

        BinarySearchTree bst = new BinarySearchTree();
        for (int i : sample) {
            bst.insert(i);
        }
        bst.inorder();
        // print_array(insertion_sort(sample));
    }

    static int[] bubble_sort(int[] array) {
        // compare two neibor elements, see if need to swap
        // repeat from 01, 12, 13...12, 13...23, 24...
        for (int i = 0; i < array.length - 1; i++) {
            for (int j = 0; j < array.length - i - 1; j++) {
                compare++;
                if (array[j] > array[j + 1]) {
                    // swap
                    swap(array, j, j + 1);
                }
            }
        }

        System.out.println("bubble sort compare: " + compare);
        System.out.println("bubble sort swap: " + swap_num);
        compare = 0;
        swap_num = 0;
        return array;
    }

    static int[] selection_sort(int[] array) {
        // create a new array, find the min from old array and insert to the new
        // then remove the min from old array
        int[] res = new int[array.length];
        for (int i = 0; i < array.length; i++) {
            // find min index
            int min_index = get_min(array);
            // add value to new array
            res[i] = array[min_index];
            // remove min from old
            array[min_index] = Integer.MAX_VALUE;
        }
        System.out.println("selection sort compare: " + compare);
        System.out.println("selection sort swap: " + swap_num);
        compare = 0;
        swap_num = 0;
        return res;
    }

    static int get_min(int[] array) {
        int min = array[0];
        int index = 0;
        for (int i = 0; i < array.length; i++) {
            compare++;
            if (array[i] < min) {
                min = array[i];
                index = i;
            }
        }
        return index;
    }

    static int[] insertion_sort(int[] array) {
        // splite array into two, and keep inserting element from second part to first
        // part
        for (int i = 1; i < array.length; i++) {
            int tmp = array[i];
            int j = i;
            while (j > 0 && tmp < array[j - 1]) {
                compare++;
                swap_num++;
                array[j] = array[j - 1];
                j--;
            }
            compare++;
            if (j != i) {
                array[j] = tmp;
            }
        }
        System.out.println("Insertion sort compare: " + compare);
        System.out.println("Insertion sort swap: " + swap_num);
        compare = 0;
        swap_num = 0;
        return array;
    }

    static int[] quickSortAPI(int[] array) {
        int[] res = quickSort(array, 0, array.length - 1);
        System.out.println("quick sort compare: " + compare);
        System.out.println("quick sort swap: " + swap_num);
        compare = 0;
        swap_num = 0;
        return res;
    }

    // split array to two sub arrays and recursively sort
    static int[] quickSort(int[] arr, int left, int right) {
        compare++;
        if (left < right) {
            // get index of spliting
            int partition_index = partition(arr, left, right);
            quickSort(arr, left, partition_index - 1);
            quickSort(arr, partition_index + 1, right);
        }
        return arr;
    }

    static int partition(int[] arr, int left, int right) {
        int pivot = left;
        int index = pivot + 1;

        // sorting
        for (int i = index; i <= right; i++) {
            compare++;
            if (arr[i] < arr[pivot]) {
                swap(arr, i, index);
                index++;
            }
        }
        swap(arr, pivot, index - 1);
        return index - 1;
    }

    static void swap(int[] arr, int i, int j) {
        swap_num++;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    static int[] merge_sort_API(int[] array) {
        int[] res = merge_sort(array);
        System.out.println("merge sort compare: " + compare);
        compare = 0;
        return res;
    }

    static int[] merge_sort(int[] array) {
        // copy
        int[] arr = Arrays.copyOf(array, array.length);
        // size = 1, return
        compare++;
        if (arr.length < 2) {
            return arr;
        }
        // split to two parts
        int middle = (int) Math.floor(arr.length / 2);
        int[] left = Arrays.copyOfRange(arr, 0, middle);
        int[] right = Arrays.copyOfRange(arr, middle, arr.length);
        // merge the two parts
        return merge(merge_sort(left), merge_sort(right));
    }

    static int[] merge(int[] left, int[] right) {
        int[] result = new int[left.length + right.length];
        int i = 0;
        // merge elements
        while (left.length > 0 && right.length > 0) {
            compare++;
            if (left[0] <= right[0]) {
                result[i++] = left[0];
                left = Arrays.copyOfRange(left, 1, left.length);
            } else {
                result[i++] = right[0];
                right = Arrays.copyOfRange(right, 1, right.length);
            }
        }
        // one side is empty
        while (left.length > 0) {
            result[i++] = left[0];
            left = Arrays.copyOfRange(left, 1, left.length);
        }

        while (right.length > 0) {
            result[i++] = right[0];
            right = Arrays.copyOfRange(right, 1, right.length);
        }
        return result;
    }

    static void print_array(int[] array) {
        String res = "";
        for (int i : array) {
            res += i + ",";
        }
        System.out.println(res.substring(0, res.length() - 1));
    }

}

class BinarySearchTree {

    // Class containing left and right child of
    // current node and key value
    class Node {
        int key;
        Node left, right;

        public Node(int item) {
            key = item;
            left = right = null;
        }
    }

    // Root of BST
    Node root;

    int compare = 0;

    // Constructor
    BinarySearchTree() {
        root = null;
    }

    BinarySearchTree(int value) {
        root = new Node(value);
    }

    // This method mainly calls insertRec()
    void insert(int key) {
        root = insertRec(root, key);
    }

    // A recursive function to
    // insert a new key in BST
    Node insertRec(Node root, int key) {
        // If the tree is empty return a new node
        compare++;
        if (root == null) {
            root = new Node(key);
            return root;
        }

        // Otherwise, recur down the tree
        compare++;
        if (key < root.key)
            root.left = insertRec(root.left, key);
        else {
            compare++;
            if (key > root.key)
                root.right = insertRec(root.right, key);
        }

        // return the (unchanged) node pointer
        return root;
    }

    // This method mainly calls InorderRec()
    void inorder() {
        inorderRec(root);
        System.out.println("BST compare: " + compare);
    }

    // A utility function to do inorder traversal of BST
    void inorderRec(Node root) {
        compare++;
        if (root != null) {
            inorderRec(root.left);
            // System.out.print(root.key + " ");
            inorderRec(root.right);
        }
    }
}
