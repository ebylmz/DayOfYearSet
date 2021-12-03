#include <iostream>
#include <vector>
#include "dayOfYearSet.h"

using std::vector;
using std::ostream;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

namespace DoYGTU {
    /******************************************************************************
     *                              DayOfYearSet::DayOfYear
     ******************************************************************************/
    
        DayOfYearSet::DayOfYear::DayOfYear (int theMonth, int theDay) {
        // first set the month, than set the day 
        // since each month don't have same number of days
        bool r = setMonth(theMonth) == EXIT_SUCCESS && setDay(theDay) == EXIT_SUCCESS;
        if (r == false) {
            cerr << "(!)Invalid date (" << theDay << "." << theMonth << "). Aborted\n";
            exit(1); 
        }
    }

    int DayOfYearSet::DayOfYear::DayOfYear::setDay (int theDay) {
        if (1 <= theDay && theDay <= dayInMonth()) {
            day = theDay;
            return EXIT_SUCCESS;   
        }
        else
            return EXIT_FAILURE;
    }

    int DayOfYearSet::DayOfYear::DayOfYear::setMonth (int theMonth) {
        if (1 <= theMonth && theMonth <= 12) {
            month = theMonth;
            return EXIT_SUCCESS;   
        }
        else
            return EXIT_FAILURE;
    }

    inline int DayOfYearSet::DayOfYear::getDay () const {return day;}
    inline int DayOfYearSet::DayOfYear::getMonth () const {return month;}

    int DayOfYearSet::DayOfYear::daySoFar () const {
        return getDay() + getMonth() * 31;
    }

    ostream & operator<< (ostream & outs, const DayOfYearSet::DayOfYear & d) {
        outs << d.getDay() << "." << d.getMonth();
        return outs;
    }

    bool operator== (const DayOfYearSet::DayOfYear & d1, const DayOfYearSet::DayOfYear & d2) {
        return d1.getDay() == d2.getDay() && d1.getMonth() == d2.getMonth();
    }

    bool operator!= (const DayOfYearSet::DayOfYear & d1, const DayOfYearSet::DayOfYear & d2) {
        return !(d1 == d2);
    }

    const DayOfYearSet::DayOfYear DayOfYearSet::DayOfYear::operator++ () {
        // if today is the last day of month
        // set the day as first day of next month
        if (day == dayInMonth()) {
            month = (month == 12) ? 1 : month + 1; 
            day = 1;   
        }
        else 
            ++day;
        return *this; 
    } 
    const DayOfYearSet::DayOfYear DayOfYearSet::DayOfYear::operator++ (int) {
        DayOfYearSet::DayOfYear tmp(*this);
        ++(*this);
        return tmp;
    }

    const DayOfYearSet::DayOfYear DayOfYearSet::DayOfYear::operator-- () {
        // if today is the first day of month
        // set the day as last day of previos month
        if (day == 1) {
            month = (month == 1) ? 12 : month - 1;
            day = dayInMonth();
        }
        return *this;
    } 

    const DayOfYearSet::DayOfYear DayOfYearSet::DayOfYear::operator-- (int) {
        DayOfYearSet::DayOfYear tmp(*this);
        --(*this);
        return tmp;
    }

    int DayOfYearSet::DayOfYear::dayInMonth () {
        switch (month) {
            case  1: return 31;
            case  2: return 28;
            case  3: return 31;
            case  4: return 30;
            case  5: return 31;
            case  6: return 30;
            case  7: return 31;
            case  8: return 31;
            case  9: return 30;
            case 10: return 31;
            case 11: return 30;
            case 12: return 31;
            default: return 0;
        }
    }

    /******************************************************************************
     *                             DayOfYearSet
     ******************************************************************************/
    DayOfYearSet::DayOfYearSet (int capacity) : _capacity(capacity), _size(0) {
        if (capacity < 0) {
            cerr << "(!) negative capacity\n";
            exit(1);
        }
    }

    DayOfYearSet::DayOfYearSet (const DayOfYearSet & s) {
        *this = s;
    }

    DayOfYearSet::DayOfYearSet (const vector<DayOfYearSet::DayOfYear> & v) 
        : _capacity(v.capacity()), _size(v.size()) {
        set = new DayOfYearSet::DayOfYear[capacity()];
        if (set != nullptr) {
            for (int i = 0; i < size(); ++i)
                if (add(v[i]) == EXIT_FAILURE)
                    cerr << "(!) Dublicated value, ignored\n";
                    //! IGNORES DUBLICATED VALUES
        }  
        else {
            cerr << "(!) No enough memory. Aborted\n";
            exit(1);
        }
    }

    DayOfYearSet::DayOfYearSet (const char * filename) {
        char buff[120];

        while (load(filename) == EXIT_FAILURE) {
            cout << "Enter the file name: ";
            cin >> buff;
            //! NOT IMPLEMENTED YET
        }
    }

    DayOfYearSet::~DayOfYearSet () {delete [] set;}

    bool DayOfYearSet::isInSet (const DayOfYearSet::DayOfYear & element) const {
        for (int i = 0; i < size(); ++i)
            if (set[i] == element)
                return true;
        return false;
    }

    int DayOfYearSet::add (const DayOfYearSet::DayOfYear & element) {
        int r;

        // no duplicates are allowed in a set
        if (!isInSet(element)) {
            // resize the set if needed
            if (size() == capacity()) 
                r = resize(capacity() * 2);
            else
                r = EXIT_SUCCESS;

            // add the new element to the last index
            if (r == EXIT_SUCCESS) {
                set[_size] = element;
                ++_size;
                ++_AllDoY;     //! new active DoY object created
            }
        }
        else r = EXIT_FAILURE;

        return r;
    }

    int DayOfYearSet::remove (const DayOfYearSet::DayOfYear & element) {
        for (int i = 0; i < size(); ++i)
            if (set[i] == element)
                return remove(i);
        return EXIT_FAILURE;
    }

    int DayOfYearSet::remove (int index) {
        if (0 <= index && index < size()) {
            //! THEN WHAT HAPPENS AFTER DELETION
            set[index] = DayOfYear();
            return EXIT_SUCCESS;
        }
        else {
            cerr << "(!) Invalid index for remove operation";
            return EXIT_FAILURE;
        }
    }

    int DayOfYearSet::resize (int newCapacity) {
        int r;
            
        DayOfYearSet::DayOfYear * tmp = new DayOfYearSet::DayOfYear[capacity()]; 
        if (tmp != nullptr) {
            _capacity = newCapacity;
            
            // copy the values inside of old array to new allocated array
            for (int i = 0; i < size() /* && set[i] != nullptr */; ++i)
                tmp[i] = set[i];
            
            delete [] set;
            set = tmp;
            r = EXIT_SUCCESS;
        }
        else {
            cerr << "(!) No enough memory for new allocation\n";
            r = EXIT_FAILURE;
        }

        return r;
    }

    int DayOfYearSet::load (const char * filename) {}
    //! NOT IMPLEMENTED YET
    int DayOfYearSet::save (const char * filename) const {}
    //! NOT IMPLEMENTED YET

    ostream & operator<< (ostream & outs, const DayOfYearSet & s) {
        for (int i = 0; i < s.size(); ++i)
            outs << s[i] << " ";
        return outs;
    }

    const DayOfYearSet & DayOfYearSet::operator= (const DayOfYearSet & other) {
        // update the size of set
        if (capacity() != other.capacity()) {
            delete [] set;

            _capacity = other.capacity();
            set = new DayOfYearSet::DayOfYear[capacity()];
        }

        for (int i = 0; i < size(); ++i)
            set[i] = set[i];
        
        return *this; 
        // return other; 
    }

    bool DayOfYearSet::operator== (const DayOfYearSet & other) {
        for (int i = 0; i < other.size(); ++i) 
            if (!isInSet(other[i]))
                return false;
        return true;
    }

    bool DayOfYearSet::operator!= (const DayOfYearSet & other) {
        return !(*this == other);
    }

    const DayOfYearSet DayOfYearSet::operator+ (const DayOfYearSet & other) {
        DayOfYearSet unionSet(*this);
        for (int i = 0; i < other.size(); ++i)
            add(other[i]);  // add functions does not allow dublicated values 
        return unionSet;
    }

    const DayOfYearSet DayOfYearSet::operator- (const DayOfYearSet & other) {
        DayOfYearSet diffSet;

        // add the elements which are belongs to only this set
        for (int i = 0; i < other.size(); ++i)
            if (!isInSet(other[i]))  
                diffSet.add(other[i]);

        return diffSet;
    }

    const DayOfYearSet DayOfYearSet::operator^ (const DayOfYearSet & other) {
        DayOfYearSet intersectionSet;

        // add the elements which are belongs to both this and other set
        for (int i = 0; i < other.size(); ++i)
            if (isInSet(other[i]))
                intersectionSet.add(other[i]);

        return intersectionSet;
    }
  
    const DayOfYearSet DayOfYearSet::operator! () {
        const int DAY_IN_YEAR = 365;
        DayOfYearSet::DayOfYear day;  // initialized as January 1
        DayOfYearSet complementSet;

        // check all the day in a year
        for (int i = 0; i < DAY_IN_YEAR; ++i, ++day) 
            if (!isInSet(day)) // add all the days except the days in this set
                complementSet.add(day);
        return complementSet;
    }

    DayOfYearSet::DayOfYear & DayOfYearSet::operator[] (int position) {
        if (position < capacity()) //! size or capacity
            return set[position];
        else {
            cerr << "(!) Invalid position at set. Aborted\n";
            exit(1);
        }
    }

    const DayOfYearSet::DayOfYear & DayOfYearSet::operator[] (int position) const {
        if (position < capacity()) //! size or capacity
            return set[position];
        else {
            cerr << "(!) Invalid position at set. Aborted\n";
            exit(1);
        }
    }

    inline int DayOfYearSet::size() const {return _size;}

    inline int DayOfYearSet::capacity () const {return _capacity;}

    int DayOfYearSet::AllDoY () {return _AllDoY;}
} // namespace DoYGTU 