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

        //! we can do this as static f
        /**
         * Returns the number of day in given month
         * @param month 
         * @return day in given month, 0 for invalid month values
         */
        public int dayInMonth (int m) {
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
                // returns 0 for invalid month values
                default: return 0;
                //! throw error  
            }        
        }

        // if next month has less day than current day value,
        // then day is setted as 1
        private void nextMonth () {
            _month = (month() == 12) ? 1 : _month + 1; 
            // check if day is suitable for new month
            if (day() < dayInMonth())
                _day = 1;
        }


        // if next month has less day than current day value,
        // then day is setted as 1
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

        public String toString () {
            return String.format("%d/%d", _day, _month);
        }
    }

    public final int DAY_IN_YEAR = 365;
    private DayOfYear[] _set;   // dynamic array keeps set elements
    private int _size;          // keeps the filled array size
    // to do not have issue with _set.length when _set is equals to null 
    private static int _total; 
    
    public DayOfYearSet (ArrayList<DayOfYear> arr) {        
        reserve(arr.size());  
        for (var e : arr)
            add(e);
        ++_total;   // new DayOfYearSet constructed
    }
    
    public DayOfYearSet () {
        _size = 0;
        _set = null;
        ++_total;   // new DayOfYearSet constructed
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
        
        for (var e : _set)
            if (!other.inside(e))
                return false;
        return true;
    }


    public static int total () {return _total;}

    // checks if given element is inside this set
    public boolean inside (DayOfYear element) {
        //!!!!!!!!!!!11
        /*
        for (var v : _set)
            if (v.equals(element))
                return true;
        return false;
        */
        return find(element) != -1;
    }

    // returns the index of the element if it's in set
    // o.w. returns the size of the set
    public int find (DayOfYear element) {
        for (int i = 0; i < size(); ++i)
            if (element.equals(_set[i]))
                return i;
        return -1;
    }

    public int size () {return _size;}
    
    public void add (DayOfYear element) {
        if (!inside(element)) {
            // make sure set has capacity to adding new elements
            if (_set == null)
                reserve(1);
            else if (size() == _set.length)
                reserve(2 * _set.length);
            
            _set[_size] = element.clone(); 
            ++_size;
        }
    }

    public void remove (DayOfYear element) {
        int position = find(element); 
        if (position != -1) {
            // if remove element is located at last position, 
            // then no copy-paste needed. Just decrease the set size 
            for (int i = position + 1; i < size(); ++i)
                _set[i - 1] = _set[i];
            --_size;
        }
    }

    public void reserve (int newcapacity) {
        if (newcapacity >= 0) {
            if (_size > newcapacity)
                _size = newcapacity;
            
            DayOfYear[] pre = _set;
            _set = new DayOfYear[newcapacity]; 

            for (int i = 0; i < size(); ++i)
                _set[i] = pre[i];
        }
    }

    public DayOfYearSet union (DayOfYearSet other) {
        DayOfYearSet newset = this.clone();

        for (var e : other._set)
            add(e); // add function does not allow dublicated elements
        return newset;
    }

    public DayOfYearSet difference (DayOfYearSet other) {
        DayOfYearSet newset = new DayOfYearSet();

        // add the elements which are only in this set
        for (var e : _set)
            if (!other.inside(e))
                newset.add(e);
        return newset;
    } 

    public DayOfYearSet intersection (DayOfYearSet other) {
        DayOfYearSet newset = new DayOfYearSet();

        // add the elements which are in both this sets
        for (var e : _set)
            if (other.inside(e))
                newset.add(e);
        return newset;
    } 
    
    public DayOfYearSet complement () {
        DayOfYearSet newset = new DayOfYearSet();
        DayOfYear e = new DayOfYear();    // an element of DayOfYearSet

        // try each day 
        for (int i = 0; i < DAY_IN_YEAR; ++i, e.next())
            if (!inside(e))
                newset.add(e);
        return newset;    
    } 

    public String toString () {
        //!!!!!!!!!!!!!!!!!!1
        String str_set = "";
        for (var e : _set)
            str_set += e + ", ";
        return String.format("{%s}", str_set);
    }
}