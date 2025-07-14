#include<iostream>
#include<string>

using namespace std;

template <typename T>
T myMax(T a, T b) {
    return (a > b)?a:b;
}

template <typename T>
T myMin(T a, T b) {
    return (a < b)?a:b;
}

template <typename T>
void mySwap(T& a, T& b) {
    T c;
    c = a;
    a = b;
    b = c;
}

template <typename T>
void printArray(const T arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i];
    }
    cout << endl;
}

struct Point {
    int r;
    int c;

    bool operator<(const Point& other) const{
        if(r != other.r) {
            return r < other.r;
        }
        return c < other.c;
    }

    bool operator>(const Point& other) const{
        if(r != other.r) {
            return r > other.r;
        }
        return c > other.c;
    }

    bool operator==(const Point& other) const{
        return (r == other.r && c == other.c);
    }
};

ostream& operator<<(ostream& os, const Point& p) {
    os << "Point " << "(" << p.r << ","  << p.c << ")";
    return os;
}

int main() {
    Point p1 = {1,2};
    Point p2 = {2,3};
    Point p3 = min(p1,p2);
    Point p4 = max(p1,p2);

    string a = "Hello";
    string b = "World";

    //min
    cout << "Min integers: " << min(1,2) << endl;
    cout << "Min double: " << min(2.5, 3.7) << endl;
    cout << "Min string: " << min(a,b) << endl;
    cout << "Min point: " << p3 << " " << endl;

    //max
    cout << "Max integers: " << min(1,2) << endl;
    cout << "Max double: " << min(2.5, 3.7) << endl;
    cout << "Max string: " << min(a,b) << endl;
    cout << "Max point: " << p4 << " " << endl;

    //swap
    double sw_x = 1.1, sw_y = 2.2;
    cout << "Before swap (double): x = " << sw_x << ", y = " << sw_y << endl;
    mySwap(sw_x, sw_y);
    cout << "After swap (double): x = " << sw_x << ", y = " << sw_y << endl;

    Point sw_p1 = {10, 5}, sw_p2 = {20, 15};
    cout << "Before swap (Point): p1 = " << sw_p1 << ", p2 = " << sw_p2 << endl;
    mySwap(sw_p1, sw_p2);
    cout << "After swap (Point): p1 = " << sw_p1 << ", p2 = " << sw_p2 << endl;
    cout << endl;

    cout << "--- Testing printArray ---" << endl;
    int intArray[] = {1, 2, 3, 4, 5};
    cout << "Printing intArray: ";
    printArray(intArray, 5);

    double doubleArray[] = {1.1, 2.2, 3.3};
    cout << "Printing doubleArray: ";
    printArray(doubleArray, 3);

    std::string stringArray[] = {"apple", "banana", "cherry"};
    cout << "Printing stringArray: ";
    printArray(stringArray, 3);

    Point pointArray[] = {{1,1}, {2,2}, {3,3}};
    cout << "Printing pointArray: ";
    printArray(pointArray, 3);


    return 0;
}