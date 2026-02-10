#include <iostream>

using namespace std;

// month's shift or 7 minus the first doomsday's date
int mshift[12] = {5, 1, 0, 3, 5, 1, 3, 6, 2, 4, 0, 2};

int findDay(int day, int month, int year) {       
        if (month < 3) year -= 1; // in this calculation Jan and Feb use previous year's doomsday       
        int century = year/ 100; // "century" is just the first two digits of the year        
        century = (2 + 5*(century % 4)) % 7; // century's anchor:     
        year %= 100; // two-digit year:
        year = (year + 11*(year&0x1)) >> 1; // 11-odd rule
        year = 7 - (year + 11*(year&0x1)) % 7; // year's drift
        // doomsday = century's anchor + year's drift = century + year 
        int w = (century + year + mshift[month-1] + day) % 7; // weekday value: 0 for Sunday, 1 for Monday etc.
        return w; 
    }
    
    
int main() {
    int day, month, year;
    cout << "day?" << endl;
    cin >> day;
    cout << "month?" << endl;
    cin >> month;
    cout << "year?" << endl;
    cin >> year;
    cout << findDay(day, month, year) << endl;
    return 0;
}