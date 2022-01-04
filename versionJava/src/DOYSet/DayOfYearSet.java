/**
 * @file    DayOfYearSet.java
 * @author  Emirkan Burak Yılmaz 
 * @brief   DayOfYearSet Implementation   
 * @version 0.1
 * @date    2022-01-04
 * 
 * @copyright Copyright (c) 2021
 */

package DOYSet;

import java.util.ArrayList;

public class DayOfYearSet implements Cloneable {
    // static inner class 
    // each element of DayOfYearSet is DayOfYear object 
    public static class DayOfYear implements Cloneable {
        private int _day;
        private int _month;

        public DayOfYear (int m, int d) {
            setMonth(m);
            setDay(d);
        }
        
        public DayOfYear (int m) {this(m, 1);}
        
        public  DayOfYear () {this(1, 1);}
        
        public DayOfYear clone () {
            try {
                return (DayOfYear) super.clone();
            }
            catch (CloneNotSupportedException e) {
                // this will never happen
                return null;
            }
        }

        /**
         * Returns the number of day in given month
         * @param month 
         * @return day in given month, 0 for invalid month values
         */
        //! we can do this as static method
        public static int dayInMonth (int m) throws IllegalAccessError {
            switch (m) {
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
                default:
                    throw new IllegalArgumentException();
            }        
        }

        /**
         * @return the number of day passed from first day of year to current day
         */
        public int daySoFar () {
            int dayMonth = 0;
            for (int i = 1; i < month(); ++i)
                dayMonth += dayInMonth(i);
            return dayMonth + day(); 
        }

        // if next month has less day than current day value, then day is setted as 1
        private void nextMonth () {
            _month = (month() == 12) ? 1 : _month + 1; 
            // check if day is suitable for new month
            if (day() < dayInMonth())
                _day = 1;
        }

        // if next month has less day than current day value, then day is setted as 1
        private void preMonth () {
            _month = (month() == 1) ? 12 : _month - 1; 
            // check if day is suitable for new month
            if (day() < dayInMonth())
                _day = 1;
        }

        /**
         * Returns the number of day in current month
         * @return day in current month
         */
        public int dayInMonth () {
            return dayInMonth(month());
        }

        public int day () {return _day;}

        public int month () {return _month;}
        
        public void setDay (int d) {
            if (d <= dayInMonth())
                _day = d;
        }

        public void setMonth (int m) {
            if (1 <= m && m <= 12) {
                _month = m;
                // be sure day is still valid
                if (day() > dayInMonth())
                    _day = 1;
            }
        }

        /**
         * sets the day to next day
         */
        public void next () {
            if (day() == dayInMonth()) {
                nextMonth();
                _day = 1;
            }
            else
                ++_day;
        }

        /**
         * sets the day to previous day
         */
        public void pre () {
            if (day() == 1) {
                preMonth();
                _day = dayInMonth();
            }
        }

        /**
         * @return the day after current day in year
         */
        public DayOfYear nextDay () {
            var newday = clone();
            newday.next();
            return newday;   
        }

        /**
         * @return the day before current day in year
         */
        public DayOfYear preDay () {
            var newday = clone();
            newday.pre();
            return newday;
        }

        /**
         * 
         * @param other
         * @return true for this day comes before other day
         */
        public boolean preceding (DayOfYear other) {
            return daySoFar() < other.daySoFar();
        }

        public boolean equals (DayOfYear other) {
            return day() == other.day() && month() == other.month();
        }

        public String toString () {
            return String.format("%d/%d", _day, _month);
        }
    }

    /** Total day in year */
    public final int DAY_IN_YEAR = 365;
    private DayOfYear[] _set;   // dynamic array keeps set elements
    private int _size;          // keeps the filled array size
    private static int _total;  // total number of DayOfYear objects alive in all the sets
    
    public DayOfYearSet (ArrayList<DayOfYear> arr) {        
        reserve(arr.size());  
        for (var e : arr)
            add(e);
    }
    
    public DayOfYearSet () {
        _size = 0;
        _set = null;
    }

    public DayOfYearSet clone () {
        // protected Object clone () throws CloneNotSupportedException
        // handle the exception
        // change the return type (Covariant return type)
        try {
            DayOfYearSet clone = (DayOfYearSet) super.clone();
            if (_set != null) {
                clone._set = new DayOfYear[_set.length];
                for (int i = 0; i < size(); ++i)
                    clone._set[i] = _set[i];
            }
            else
                clone._set = null;
            return clone;
        }
        catch (CloneNotSupportedException e) {
            // this will never happen
            return null;
        }
    }

    public boolean equals (DayOfYearSet other) {
        if (size() != other.size())
            return false;        
        
        for (int i = 0; i < size(); ++i)
            if (!other.inside(at(i)))
                return false;
        return true;
    }

    /**
     * @return the total number of DayOfYear objects alive in all the sets
     */
    public static int total () {return _total;}

    /**
     * 
     * @param element
     * @return true if element is in set
     */
    public boolean inside (DayOfYear element) {
        return find(element) != -1;
    }

    // returns the index of the element if it's in set
    // o.w. returns the size of the set
    public int find (DayOfYear element) {
        for (int i = 0; i < size(); ++i)
            if (at(i).equals(element))
                return i;
        return -1;
    }

    /**
     * @return number of elements in the DayOfYearSet
     */
    public int size () {return _size;}
    
    //! returns final object to not modify it
    //! how user modify the set values ??? setAt () ...
    /**
     * Returns the element at given position
     * @param position
     * @return final DayOfYear object at position DayOfYearSet
     * @throws IllegalAccessError
     */
    public final DayOfYear at (int position) throws IllegalAccessError {
        if (_set == null || position < 0 || position >= size())
            throw new IllegalAccessError();
        return _set[position];
    }

    /**
     * Sorts the set as increasing order
     */
    public void sort () {
        for (int i = 1; i < size(); ++i) {
            DayOfYear min = _set[i].clone();
            
            int j = i;
            while (j > 0 && min.preceding(_set[j - 1])) {
                _set[j] = _set[j - 1];
                --j;
            }
            _set[j] = min;
        }
    }

    /**
     * Adds given element to the set. No duplication allowed.
     * @param element
     */
    public void add (DayOfYear element) {
        if (!inside(element)) {
            // make sure set has capacity to adding new elements
            if (_set == null)
                reserve(1);
            else if (size() == _set.length)
                reserve(2 * _set.length);
            
            _set[_size] = element.clone(); 
            ++_size;
            ++_total;   // new DayOfYear object created
        }
    }

    /**
     * Removes the given element if it's inside of the set
     * @param element
     */
    public void remove (DayOfYear element) {
        // find returns the position of given element
        remove(find(element));  
    }

    /**
     * Removes the element at given position
     * @param position
     */
    public void remove (int position) {
        if (0 <= position && position < size()) {
            // if remove element is located at last position, 
            // then no copy-paste needed. Just decrease the set size 
            for (int i = position + 1; i < size(); ++i)
                _set[i - 1] = _set[i];
            --_size;
            --_total;   // a DayOfYear object killed
        }
    }

    /**
     * deletes all the set and set it as empty set 
     */
    public void empty () {
        _size = 0;
    }

    // reserve is private because memory manipulation doesn't concern the user 
    private void reserve (int newcapacity) {
        if (newcapacity >= 0) {
            if (_size > newcapacity)
                _size = newcapacity;
            
            DayOfYear[] pre = _set;
            _set = new DayOfYear[newcapacity]; 

            for (int i = 0; i < size(); ++i)
                _set[i] = pre[i];
        }
    }

    /**
     * @param other
     * @return union of two set
     */
    public DayOfYearSet union (DayOfYearSet other) {
        DayOfYearSet newset = this.clone();

        for (int i = 0; i < other.size(); ++i)
            newset.add(other.at(i)); // add function does not allow dublicated elements
        return newset;
    }

    /**
     * @param other
     * @return difference of this from other set
     */
    public DayOfYearSet difference (DayOfYearSet other) {
        DayOfYearSet newset = new DayOfYearSet();

        // add the elements which are only in this set
        for (int i = 0; i < size(); ++i)
            if (!other.inside(at(i)))
                newset.add(at(i));
        return newset;
    } 

    /**
     * @param other
     * @return intersection of two set
     */
    public DayOfYearSet intersection (DayOfYearSet other) {
        DayOfYearSet newset = new DayOfYearSet();

        // add the elements which are in both sets
        for (int i = 0; i < size(); ++i)
            if (other.inside(at(i)))
                newset.add(at(i));
        return newset;
    } 
    
    /**
     * @return complement set of current set
     */
    public DayOfYearSet complement () {
        DayOfYearSet newset = new DayOfYearSet();
        DayOfYear e = new DayOfYear();  // e is 1 January by default
        
        // try each day 
        for (int i = 0; i < DAY_IN_YEAR; ++i, e.next())
            if (!inside(e))
                newset.add(e);
        return newset;    
    } 

    public String toString () {
        //! BETTER DESIGN NEEDED
        String str_set = "";
        for (int i = 0; i < size(); ++i) {
            if (i != 0)
                str_set += ", ";
            str_set += at(i);
        }
        return String.format("{%s}", str_set);
    }
}