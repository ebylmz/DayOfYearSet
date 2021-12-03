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
    test2();
    test3();
    return 0;
}

//* Send the class objects to functions using call 
//* by value and call by reference and testing the results.

void test1 () {
    DayOfYearSet s1, s2;
    // s1.add(....);
    // s1.add(....);
    // s1.add(....);

    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    
    cout << "Union        (s1 + s2): " << s1 + s2 << endl;
    cout << "Difference   (s1 - s2): " << s1 - s2 << endl;
    cout << "Intersection (s1 ^ s2): " << (s1 ^ s2) << endl;
    cout << "Complement   (!s1)    : " << !s1 << endl;
    cout << "Complement   (!s2)    : " << !s2 << endl;
}

// Test the De Morgan rule for sets with at least 5 different set pairs.
// Note that for sets s1 and s2, De Morgan says that !(s1 + s2) == !s1 ^ !s2
void test2 () {
    DayOfYearSet s1, s2;
    
    cout << "De Morgan rules:\n";
    // if (!(s1 + s2) == !s1 ^ !s2)
}


// Load & Save some sets to text files.
void test3 () {
    DayOfYearSet s1("example-set1.txt");
    
    cout << "S1: " << s1 << endl;
    s1.remove(2);   //! not sure
    s1.save("example-set2.txt");   
}
