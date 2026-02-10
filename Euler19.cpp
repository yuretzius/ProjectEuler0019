#include <iostream>

using namespace std;

int SF (int w) {
    w = (w == 0) ? 1 : 0;
    return w;
} 

int t[12] = {5, 1, 0, 3, 5, 1, 3, 6, 2, 4, 0, 2};

int findDay(int day, int month, int year) {
        if (month < 3) year -= 1;
        int century = year/ 100;
        century = (2 + 5*(century % 4)) % 7;
        year %= 100;
        year = (year + 11*(year&0x1)) >> 1;
        year = 7 - (year + 11*(year&0x1)) % 7;
        int w = (century + year + t[month-1] + day) % 7; 
        // 0 means Sunday
        return SF(w); 
    }
    
    
int main() {
    int d1, m1, d2, m2; 
    int y1, y2, counter;
    cout << "start date? (YYYY MM DD)" << endl;
    cin >> y1 >> m1 >> d1;
    cout << "end date? (YYYY MM DD)" << endl;
    cin >> y2 >> m2 >> d2;
    counter = 0;
    if (d1 == 1) counter += findDay(d1, m1, y1);
    if (y1 == y2) {
        if (m1 != 12) {
            for(int month = m1+1; month != m2+1; month++) {
                counter += findDay(1, month, y1);
            }
        }
    }
    else {
        if (m1 != 12) {
            for(int month = m1+1; month != 13; month++) {
                counter += findDay(1, month, y1);
            }
        }
        for(int month = 1; month != m2 + 1; month++) {
            counter += findDay(1, month, y2);
        }
        for (int year = y1+1; year != y2; year++) {
            for (int month = 1; month != 13; month++) {
                counter += findDay(1, month, year);
            }
                
        }
    }
    cout << counter << endl;
    return 0;
}