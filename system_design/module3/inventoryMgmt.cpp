#include <iostream>
#include <string>

using namespace std;

class inventoryItem {
    int id;
    string name;

public:
    inventoryItem(int val, string n)
    : id(val), name(n)
    {}

    int getId() const {return id;}

};


int main() {
    return 0;
}