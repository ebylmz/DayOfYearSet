/**
 * @file    TestDayOfYearSet.java
 * @author  Emirkan Burak Yılmaz 
 * @brief   DayOfYearSet Driver Program   
 * @version 0.1
 * @date    2022-01-04
 * 
 * @copyright Copyright (c) 2021
 */

package DOYSet;
// import package.name.Class;   // Import a single class
// import package.name.*;   // Import the whole package
import DOYSet.DayOfYearSet.DayOfYear;

import java.util.ArrayList;

public class TestDayOfYearSet {
    public static void main (String[] args) {
        test2();

        test4();

        System.out.printf("\n============== END OF DRIVER PROGRAM ==============\n");
    }

    public static void test0 () {
        System.out.printf("======================== Test0 ========================\n");

        DayOfYear today = new DayOfYear(12, 31);

        System.out.printf("Today is new year's eve (%s)\n", today);
        System.out.printf("Tomarrow will be first day of new year (%s)\n", today.nextDay());
        System.out.printf("====================== Test DONE ======================\n");
    }

    public static void test1 () {
        System.out.printf("======================== Test1 ========================\n");

        DayOfYear today = new DayOfYear(1, 5);
        DayOfYear birthday = new DayOfYear(8, 25);

        if (today == birthday)
            System.out.printf("Happy birthday to youu\n");
        else
            System.out.printf("I will remember your birthday. Have a good day\n");
            System.out.printf("====================== Test DONE ======================\n");
        }

    /**
     * Tests methods union, intersection, difference, 
     * complement and static mothod total. 
     */
    public static void test2 () {
        System.out.printf("======================== Test2 ========================\n");

        System.out.printf("Total number of DayOfYear objects alive in all the sets: %d\n", DayOfYearSet.total());

        DayOfYearSet s1 = new DayOfYearSet();
        s1.add(new DayOfYear(1, 1));
        s1.add(new DayOfYear(2, 2));
        s1.add(new DayOfYear(3, 3));
        s1.add(new DayOfYear(4, 4));
        s1.add(new DayOfYear(5, 5));
        s1.add(new DayOfYear(6, 6));
        s1.add(new DayOfYear(7, 7));
        System.out.printf("s1: %s\n", s1);
        
        DayOfYearSet s2 = new DayOfYearSet();
        s2.add(new DayOfYear(12, 12));
        s2.add(new DayOfYear(11, 11));
        s2.add(new DayOfYear(10, 10));
        s2.add(new DayOfYear(9, 9));
        s2.add(new DayOfYear(8, 8));
        s2.add(new DayOfYear(7, 7));
        s2.add(new DayOfYear(6, 6));
        s2.add(new DayOfYear(5, 5));
        System.out.printf("s2: %s\n", s2);
        
        System.out.printf("Are s1 and s2 equivalent? ");
        if (s1.equals(s2))
            System.out.println("Yes");
        else
            System.out.println("No");

        System.out.printf("s1 u s2: %s\n", s1.union(s2));
        System.out.printf("s1 ∩ s2: %s\n", s1.intersection(s2));
        System.out.printf("s1 - s2: %s\n", s1.difference(s2));
        System.out.printf("s2 - s1: %s\n", s2.difference(s1));
        //! System.out.printf("~s1: %s\n", s1.complement());

        System.out.printf("Total number of DayOfYear objects alive in all the sets: %d\n", DayOfYearSet.total());
        //! something wrong there need an destructor
        System.out.printf("====================== Test DONE ======================\n");
    }

    /** Tests sort and remove method */
    public static void test3 () {
        System.out.printf("======================== Test3 ========================\n");

        DayOfYearSet s1 = new DayOfYearSet();
        DayOfYear d = new DayOfYear(5, 21);

        s1.add(new DayOfYear(12, 5));
        s1.add(new DayOfYear(5, 25));
        s1.add(new DayOfYear(4, 23));
        s1.add(new DayOfYear(2, 24));
        s1.add(d);
        s1.add(new DayOfYear(5, 15));
        s1.add(new DayOfYear(9, 14));
        s1.add(new DayOfYear(6, 16));
        s1.add(new DayOfYear(11, 2));
        System.out.printf("s1: %s\n", s1);

        s1.sort();
        System.out.printf("call s1.sort()\n");
        System.out.printf("s1: %s\n", s1);

        System.out.printf("Remove %s, %s, %s\n", d, s1.at(0), s1.at(s1.size() - 1));
        s1.remove(d);
        s1.remove(0);
        s1.remove(s1.size() - 1);
        s1.remove(s1.size() + 1000);    // out of index
        s1.remove(s1.size() + 2000);    // out of index

        System.out.printf("s1: %s\n", s1);
        System.out.printf("====================== Test DONE ======================\n");
    }

    /** Tests class constructor which takes an Arraylist */
    public static void test4 () {
        System.out.printf("======================== Test4 ========================\n");
        ArrayList<DayOfYear> arr = new ArrayList<DayOfYear>();
        
        arr.add(new DayOfYear(1, 12));
        arr.add(new DayOfYear(1, 32));
        arr.add(new DayOfYear(5, 22));
        arr.add(new DayOfYear(4, 12));
        arr.add(new DayOfYear(11, 25));
        arr.add(new DayOfYear(4, 1));
        arr.add(new DayOfYear(3, 12));
        // add dublicated values
        arr.add(new DayOfYear(1, 14));
        arr.add(new DayOfYear(1, 14));

        System.out.printf("ArrayList content: %s\n", arr);
        
        DayOfYearSet set = new DayOfYearSet(arr); 

        System.out.printf("set content: %s\n", set); 
        System.out.printf("====================== Test DONE ======================\n");
    }    

    /** Tests De Morgan laws in DayOfYearSet */
    public static void test5 () {
        System.out.printf("======================== Test5 ========================\n");
        //! NOT IMPLEMENTED YET
        System.out.printf("====================== Test DONE ======================\n");
    }

    /** Tests and writes some sets to text files */
    public static void test6 () {
        System.out.printf("======================== Test6 ========================\n");
        //! NOT IMPLEMENTED YET
        System.out.printf("====================== Test DONE ======================\n");
    }
}
