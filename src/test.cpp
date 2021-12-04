/*
** test.cpp:
**
** The test/driver program for the DayOfYearSet clas and it's inner class DayOfYear.
**
*/

#include <iostream>
#include "dayOfYearSet.h"

using namespace std;
using namespace DoYGTU;

void test0 ();
void test1 ();

void test2 ();
// tests member functions add(), remove(), empty() 
// size(), operator==, operator!=, operator[]  
void test3 ();
// test union, difference, intersection and compliment properties
// tests member functions operator^, operator+, operator-, operator! 
void test4 ();
// test the member functions load() and save() 
void test5 ();
// tests the De Morgan Laws

int DayOfYearSet::_AllDoY = 0;

int main (void) {
    /*
    cout << "Test0\n" << "================================\n";
    test0();
    */
    cout << "\nTest1\n" << "================================\n";
    test1();
   /*
    cout << "\nTest2\n" << "================================\n";
    test2();
    cout << "\nTest3\n" << "================================\n";
    test3();
    cout << "\nTest4\n" << "================================\n";
    test4();
    cout << "\nTest5\n" << "================================\n";
    test5();
   */
    return 0;
}

void test0 () {
    DayOfYearSet::DayOfYear d1(12, 31), d2(3, 24);
    cout << "today       : " << d1 << " (last day of the year)\n"
         << "tomarrow    : " << ++d1 << endl
         << "5 days later: " << d1 + 4 << endl
         << "The days passed so far: " << d1.daySoFar() << "\n\n";

    d2.setDay(1);
    d2.setMonth(1);

    cout << "today     : " << d2 << " (first day of the year)\n"
         << "yesterday : " << --d2 << endl
         << "5 days ago: " << d2 - 4 << endl    
         << "The days passed so far: " << d2.daySoFar() << endl;
}

void test1 () {
    DayOfYearSet::DayOfYear today, birthday;
    cout << "Enter the todays date: ";
    cin >> today;    
    cout << "Enter your birthday: ";
    cin >> birthday;

    //!!!!!!!!!!!!!!1 ERRORRRR

    if (today == birthday)
        cout << "Happy birthday to youu\n";
    else 
        cout << "There are " << today - birthday << " days to your birtday\n";
}

void test2 () {
    DayOfYearSet s1, s2;
    DayOfYearSet::DayOfYear days[5] = {DayOfYearSet::DayOfYear(1, 1), 
                                       DayOfYearSet::DayOfYear(3, 12),
                                       DayOfYearSet::DayOfYear(4, 10),
                                       DayOfYearSet::DayOfYear(5, 21),
                                       DayOfYearSet::DayOfYear(5, 17)};

    // construct s1 and s2
    cout << "construct s1 and s2\n";
    s1.add(days[0]);
    s1.add(days[1]);
    s1.add(days[2]);
    s1.add(days[3]);
    s1.add(days[4]);
    cout << "s1: " << s1 << " (size: " << s1.size() << ")\n";

    // add same days as s1 with different order
    s2.add(days[4]);
    s2.add(days[2]);
    s2.add(days[3]);
    s2.add(days[1]);
    s2.add(days[0]);
    cout << "s2: " << s2 << " (size: " << s2.size() << ")\n";

    if (s1 == s2)
        cout << "s1 and s2 are equal\n";
    else
        cout << "s1 and s2 are not equal\n";

    // removes some of the elements of s1 than compare with s2
    cout << "\nremove elements " << s1[1] << " and " << days[4] << " from s1\n";
    s1.remove(1);
    s1.remove(days[4]);

    cout << "s1: " << s1 << " (size: " << s1.size() << ")\n";
    cout << "s2: " << s2 << " (size: " << s2.size() << ")\n";

    if (s1 != s2)
        cout << "s1 and s2 are not equal\n";
    else
        cout << "s1 and s2 are equal\n";

    cout << "\nMake empty s1 and s2 (delete the sets)\n";
    s1.empty();
    cout << "s1: " << s1 << " (size: " << s1.size() << ")\n";
    s2.empty();
    cout << "s1: " << s2 << " (size: " << s2.size() << ")\n";

    if (s1 != s2)
        cout << "s1 and s2 are not equal\n";
    else
        cout << "s1 and s2 are equal\n";
}

void test3 () {
    // construct s1 and s2
    DayOfYearSet s1, s2;
    s1.add(DayOfYearSet::DayOfYear(1, 1));
    s1.add(DayOfYearSet::DayOfYear(4, 10));
    s1.add(DayOfYearSet::DayOfYear(5, 21));
    s1.add(DayOfYearSet::DayOfYear(5, 17));
    s1.add(DayOfYearSet::DayOfYear(3, 12));

    s2.add(DayOfYearSet::DayOfYear(4, 22));
    s2.add(DayOfYearSet::DayOfYear(7, 1));
    s2.add(DayOfYearSet::DayOfYear(12, 15));
    s2.add(DayOfYearSet::DayOfYear(5, 17));

    cout << "Sets\n"
         << "s1: " << s1 << " (size: " << s1.size() << ")\n"
         << "s2: " << s2 << " (size: " << s2.size() << ")\n";

    // DayOfYearSet unionSet = s1 + s2;
    // DayOfYearSet diffSet = s1 - s2;
    // DayOfYearSet isectionSet = s1 ^ s2;
    // DayOfYearSet s1Complement = !s1;
    // DayOfYearSet s2Complement = !s2;
    
    cout << "\nUnion\n" 
         << "s1 + s2: " << (s1 + s2) << "\n\n";
    cout << "Difference\n" 
         << "s1 - s2: " << (s1 - s2) << "\n\n";
    cout << "Intersection\n" 
         << "s1 ^ s2: " << (s1 ^ s2) << "\n\n";
    cout << "Complement of s1\n" 
         << "!s1    : " << !s1 << "\n\n";
    cout << "Complement of s2\n" 
         << "!s2    : " << !s2 << "\n\n";
    cout << "Complement of s1 has " << (!s1).size() << " element\n";
}


void test4 () {
    // construct sets s1 and s2
    DayOfYearSet s1, s2;
    s1.add(DayOfYearSet::DayOfYear(3, 12));
    s1.add(DayOfYearSet::DayOfYear(4, 10));
    s1.add(DayOfYearSet::DayOfYear(5, 21));
    s1.add(DayOfYearSet::DayOfYear(4, 22));
    s1.add(DayOfYearSet::DayOfYear(7, 1));
    s1.add(DayOfYearSet::DayOfYear(12, 15));
    s1.save("set1.txt");

    // construct second set as compliment of s1
    s2 = !s1;
    cout << s2 << " size(" << s2.size() << ")" << endl;
    s2.save("set2.txt");   

    // take difference of two set and save the result the file
    DayOfYearSet difference = s1 - s2;
    difference.save("set3.txt");
    
    cout << "s1 is a set and s2 is compliment of s1\n"
         << "s1 and s2 saved respectively to the files \"set1.txt\" and \"set1.txt\"\n"
         << "s1 difference s2 is saved as \"set3.txt\"\n"
         << "Check the results\n";
    //! check the load function
}

// Note that for sets s1 and s2, De Morgan says that !(s1 + s2) == !s1 ^ !s2
void test5 () {
    // load the sets s1 and s2 from the files
    DayOfYearSet s1("setA.txt"), s2("setB.txt");
    int r;

/*
    cout << "Sets\n"
         << "s1: " << s1 << " (size: " << s1.size() << ")\n"
         << "s2: " << s2 << " (size: " << s2.size() << ")\n";
*/

    if (!(s1 + s2) == (!s1 ^ !s2)) {
        cout << "the complement of the union of two sets is " 
             << "the same as the intersection of their complements\n";
        if (!(s1 ^ s2) == !s1 + !s2)
            cout << "the complement of the intersection of two sets "
                 << "is the same as the union of their complements\n";
        else
            r = EXIT_FAILURE;
    }
    else 
        r = EXIT_FAILURE;
    
    if (r == EXIT_FAILURE)
        cout << "Either De Morgan was Wrong or I implemented something wrong :)\n";             
}