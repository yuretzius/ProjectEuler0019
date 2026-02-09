#include <iostream>

using namespace std;

// see explanations in the python code

int t[12] = {5, 1, 0, 3, 5, 1, 3, 6, 2, 4, 0, 2};

int findDay(int day, int month, int year) {
        if (month < 3) year -= 1;
        cout << year << endl;
        int century = year/ 100;
        cout << century << endl;
        century = (2 + 5*(century % 4)) % 7;
        cout << century << endl;
        year %= 100;
        cout << year << endl;
        cout << (year&0x1) << endl;
        year = (year + 11*(year&0x1)) >> 1;
        cout << year << endl;
        year = 7 - (year + 11*(year&0x1)) % 7;
        cout << year << endl;
        int w = (century + year + t[month-1] + day) % 7; 
        // 0 means Sunday
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