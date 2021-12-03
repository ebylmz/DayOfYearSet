#include <iostream>
#include "dayOfYearSet.h"

using namespace std;
using namespace DoYGTU;

void test1 ();
void test2 ();
void test3 ();

int DayOfYearSet::_AllDoY = 0;


int main (void) {
    test1();
    // test2();
    // test3();
    return 0;
}

void test1 () {
    DayOfYearSet s1, s2;
    s1.add(DayOfYearSet::DayOfYear(3, 12));
    s1.add(DayOfYearSet::DayOfYear(4, 10));
    s1.add(DayOfYearSet::DayOfYear(5, 21));

    s2.add(DayOfYearSet::DayOfYear(4, 22));
    s2.add(DayOfYearSet::DayOfYear(7, 1));
    s2.add(DayOfYearSet::DayOfYear(12, 15));

    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    
    cout << "Union        (s1 + s2): "; cout << s1 + s2 << endl;
    cout << "Difference   (s1 - s2): " << s1 - s2 << endl;
    cout << "Intersection (s1 ^ s2): " << (s1 ^ s2) << endl;
    cout << "Complement   (!s1)    : " << !s1 << endl;
    cout << "Complement   (!s2)    : " << !s2 << endl;
}

// Test the De Morgan rule for sets with at least 5 different set pairs.
// Note that for sets s1 and s2, De Morgan says that !(s1 + s2) == !s1 ^ !s2
void test2 () {
    DayOfYearSet s1, s2;
    if (!(s1 + s2) == (!s1 ^ !s2))
        cout << "De Morgan says that !(s1 + s2) == !s1 ^ !s2\n";                
    else
        cout << "Program does not satisfied basic De Morgan Law\n";             
}

// Load & Save some sets to text files.
void test3 () {
    // construct first set
    DayOfYearSet s1;
    s1.add(DayOfYearSet::DayOfYear(3, 12));
    s1.add(DayOfYearSet::DayOfYear(4, 10));
    s1.add(DayOfYearSet::DayOfYear(5, 21));
    s1.add(DayOfYearSet::DayOfYear(4, 22));
    s1.add(DayOfYearSet::DayOfYear(7, 1));
    s1.add(DayOfYearSet::DayOfYear(12, 15));
    s1.save("set1.txt");

    // construct second set
    DayOfYearSet s2("set1.txt");
    s2.remove(1); 
    s2.remove(2);
    s2.add(DayOfYearSet::DayOfYear(9, 11));
    s2.add(DayOfYearSet::DayOfYear(11, 23));
    s2.save("set2.txt");   

    // take difference of two set and save the result the file
    DayOfYearSet difference = s1 ^ s2;
    difference.save("set1-diff-set2.txt");
}
