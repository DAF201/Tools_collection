public class looping_nested_array {
    static double[][][] coordinate_info = { { { 1, 2 }, { 3, 4 } }, { { 5, 6 }, { 7, 8 } } };

    public static void main(String[] args) {
        array_init(coordinate_info);
        System.out.println();
        for (double[][] arr1 : coordinate_info) {
            for (double[] arr2 : arr1) {
                for (double val : arr2) {
                    System.out.println(val);
                }
            }
        }
    }

    static void array_init(Object obj) {
        int this_array_size = Array.getLength(obj);
        for (int i = 0; i < this_array_size; i++) {
            Object element_array = Array.get(obj, i);
            if (element_array.getClass().isArray()) {
                array_init(element_array);
            } else {
                System.out.println(element_array);
                element_array = -1.0;
            }
        }
    }
}
// 1.0
// 2.0
// 3.0
// 4.0
// 5.0
// 6.0
// 7.0
// 8.0

// 1.0
// 2.0
// 3.0
// 4.0
// 5.0
// 6.0
// 7.0
// 8.0

// can only get values, not change, failure...
