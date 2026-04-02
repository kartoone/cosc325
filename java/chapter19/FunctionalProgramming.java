package chapter19;

import java.util.stream.IntStream;

public class FunctionalProgramming {

    public static void main(String[] args) {
        int nums[] = new int[] { 1, 2, 3, 4};
        int sum = java.util.Arrays.stream(nums).reduce(0, Integer::sum);
        int prod = java.util.Arrays.stream(nums).reduce(1, (int a, int b) -> { return a*b; });
        System.out.println(sum);
        System.out.println(prod);

        IntStream s = java.util.Arrays.stream(nums).map(a -> a + 7);
        //int newnums[] = s.toArray();
        //System.out.println(java.util.Arrays.toString(newnums));
        //IntStream fs = java.util.Arrays.stream(newnums).filter(a -> a < 10);
        IntStream fs = s.filter(a -> a < 10);
        int reduce = fs.reduce(0, Integer::sum);
        System.out.println(reduce);

        // all-in-one example
        int mapfilterreduce = java.util.Arrays.stream(nums)
                                    .map((int a)->{ return a + 7; })
                                    .map((int a)->{ return a - 7; })
                                    .filter(a->a<10)
                                    .reduce(0, Integer::sum);
        System.out.println(mapfilterreduce);

    }
    
}