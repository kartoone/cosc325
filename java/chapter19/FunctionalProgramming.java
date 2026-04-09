package chapter19;

import java.util.stream.IntStream;
import java.util.Arrays;
class Counter {
    int thecount = 0;
    void increment() {
        thecount++;
    }
}
class Student {
    public String name;
    public double gpa;
    public int year;
    public Student(String name, double gpa, int year) {
        this.name = name;
        this.gpa = gpa;
        this.year = year;
    }
}

public class FunctionalProgramming {
    
    public static void objectStreaming() {
        Student students[] = {
            new Student("student1",3.0,0),
            new Student("student2",3.1,1),
            new Student("student3",3.2,2),
            new Student("student5",3.3,3),
        };
        java.util.Scanner in = new java.util.Scanner(System.in);
        final Counter c = new Counter();
        System.out.println("lower level gpa avg: " + Arrays.stream(students).filter(s->s.year<=1).peek(s->c.increment()).mapToDouble(s->s.gpa).reduce((a,b)->a+b).getAsDouble()/c.thecount);
        System.out.println("upper level gpa avg: " + Arrays.stream(students).filter(s->s.year>1).mapToDouble(s->s.gpa).average());

    }

    public static void intStreaming() {
        int nums[] = new int[] { 1, 2, 3, 4};

        int sum = java.util.Arrays.stream(nums).reduce(0, Integer::sum);
        System.out.println(java.util.Arrays.toString(nums));
        int prod = java.util.Arrays.stream(nums).reduce(1, (int a, int b) -> { return a*b; });
        System.out.println(java.util.Arrays.toString(nums));
        System.out.println(sum);
        System.out.println(prod);

        IntStream s = java.util.Arrays.stream(nums).map(a -> a + 7);
        //int newnums[] = s.toArray();
        //System.out.println(java.util.Arrays.toString(newnums));
        //IntStream fs = java.util.Arrays.stream(newnums).filter(a -> a < 10);
        IntStream fs = s.filter(a -> a < 10);
        System.out.println(java.util.Arrays.toString(nums));
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

    public static void main(String[] args) {
        objectStreaming();
        //intStreaming();
    }
    
}