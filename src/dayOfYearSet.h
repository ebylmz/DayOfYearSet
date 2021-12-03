#ifndef DAY_OF_YEAR_SET
#define DAY_OF_YEAR_SET

#include <vector>
#include <fstream>

using std::vector;
using std::ostream;

//! PROBLEMS
// What happens after execution of remove()?
    // Put the last element to the delete index
// Is set maintain the user enter order?
// How to take compliment (!) of the set?

//! USE decltype and auto
//! There are 365 day in a year

namespace DoYGTU {
    class DayOfYearSet {
    public:
        // inner class DayOfYear
        class DayOfYear {
        public:
            DayOfYear (int theMonth = 1, int theDay = 1);
            // default DayOfYear objects initialized as January 1

            int setDay (int theDay);
            int setMonth (int theMonth);

            int getDay () const;
            int getMonth () const;

            int daySoFar () const;
            // returns the number of the day passed so far

            friend ostream & operator<< (ostream & outs, const DayOfYear & d);
            
            friend bool operator== (const DayOfYear & d1, const DayOfYear & d2);
            friend bool operator!= (const DayOfYear & d1, const DayOfYear & d2);
            //! is friend function needed (12 == d1)
        
            friend const DayOfYear operator+ (const DayOfYear & d1, const DayOfYear & d2); 
            //! not sure is needed
            
            const DayOfYear operator++ ();          // pre increment 
            const DayOfYear operator++ (int);       // post increment
            // set the day as next day (tomarrow) 
            const DayOfYear operator-- ();          // pre decrement
            const DayOfYear operator-- (int);       // post decrement 
            // set the day as previos day (yesterday)
        private:
            // bool isDay () const;
            // bool isMonth () const;
            int dayInMonth ();
            // returns the total day in current month

            int day;
            int month;
        }; // inner class DayOfYear

        DayOfYearSet (const DayOfYearSet & s);
        // copy constructor        
        DayOfYearSet (int capacity = 0);
        // initialize the set with specific capacity, defaulty it's empty set
        DayOfYearSet (const vector<DayOfYear> & v);
        // construct the DayOfYearSet object same values as given set
        DayOfYearSet (const char * filename);
        // construct the DayOfYearSet object according to data at given file
        ~DayOfYearSet ();
        // deconstructor

        bool isInSet (const DayOfYear & element) const;
        
        int add (const DayOfYear & element);
        // returns 0 for successful execution for dublicated values returs 1
        int remove (const DayOfYear & element);
        int remove (int index);

        int resize (int newsize);

        int load (const char * filename);
        int save (const char * filename) const;

        friend ostream & operator<< (ostream & outs, const DayOfYearSet & s);
        // prints DayOfYearSet details

        const DayOfYearSet & operator= (const DayOfYearSet & other);
        bool operator== (const DayOfYearSet & other);
        bool operator!= (const DayOfYearSet & other);
        // two sets are equal if their elements are equal regardless of the keeping order
  

        const DayOfYearSet operator+ (const DayOfYearSet & other);
        // returns the union set
        const DayOfYearSet operator- (const DayOfYearSet & other);
        // returns the difference set
        const DayOfYearSet operator^ (const DayOfYearSet & other);
        // returns the intersection set
        const DayOfYearSet operator! ();
        // returns the complement set

        DayOfYear & operator[] (int position);             
        // returns the element at given position as "lvalue"
        const DayOfYear & operator[] (int position) const;  
        // returns the element at given position as "rvalue"

        int size () const;
        int capacity () const;

        static int AllDoY ();
        // returns the total number of DayOfYear objects alive in all the sets
    private:
        static int _AllDoY;   // total number of DayOfYear objects alive in all the sets
        int _size;           
        int _capacity;
        DayOfYear * set;
    }; // class DayOfYearSet
} // namespace DoYGTU 

#endif