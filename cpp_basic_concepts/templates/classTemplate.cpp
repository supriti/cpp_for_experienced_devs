#include<iostream>
#include<vector>
#include<string>

using namespace std;

template<typename T1, typename T2>
class Pair {
    T1 first;
    T2 second;
public:
    Pair(T1 val1, T2 val2): first(val1), second(val2)
    {}

    T1 getFirst() const{return first;}
    T2 getSecond() const{ return second;}
    
    void print() const{
        cout << "First: " << getFirst();
        cout << ",Second: " << getSecond() <<endl;
    }
};

template<typename T>
class Stack {
    vector<T> sv;
public:

    void push(const T& element){
        sv.push_back(element);
    }

    bool isEmpty() const {
        return sv.empty();
    }

    T pop() {
        if(isEmpty()){
            throw out_of_range("Stack is empty, Cannot pop");
        }
        T val  = sv.back();
        sv.pop_back();
        return val;
    }

    T peek() const {
        if(isEmpty()){
            throw out_of_range("Stack is empty, Cannot peek");
        }
        return sv.back();
    }

    int size() const{
        return sv.size();
    }
};

int main() {
    Pair<int,string> p1 = {1, "hello"};
    cout << "p1.first: " << p1.getFirst() << " p1.second " << p1.getSecond() << endl;
    p1.print();

    Pair<int, double> p2 = {1, 1.2};
    cout << "p2.first: " << p2.getFirst() << " p2.second " << p2.getSecond() << endl;
    p2.print();

    string a = {"Hello"};
    Pair<string, int> p3 = {a, 5};
    cout << "p3.first: " << p3.getFirst() << " p3.second" << p3.getSecond() << endl;
    p3.print();


    //Stack
    Stack<int> intStack;
    for(int i = 0; i < 5; i++) {
        intStack.push(i);
    }

    cout << "Element at top: " << intStack.peek() << endl;
    cout << "Remove all the elements" << endl;
    while(!intStack.isEmpty()){
        intStack.pop();
    }

    cout << "Is intStack empty? " << (intStack.isEmpty() ? "Yes" : "No") << endl;
    Stack<string> stringStack;
    for(int i = 0; i < 5; i++) {
        stringStack.push("String " + to_string(i));
    }
    try {
        cout << "Attempting to peek from empty stringStack." << endl;
        stringStack.peek();
    } catch (const out_of_range& e) {
        cerr << "Caught exception: " << e.what() << endl;
    }

    cout << "Element at top: " << stringStack.peek() << endl;
    cout << "Remove all the elements" << endl;
    while(!stringStack.isEmpty()){
        cout << stringStack.pop() << endl;
    }
    

    cout << "Is stringStack empty? " << (stringStack.isEmpty() ? "Yes" : "No") << endl;
    try {
        cout << "Attempting to peek from empty stringStack." << endl;
        stringStack.peek();
    } catch (const out_of_range& e) {
        cerr << "Caught exception: " << e.what() << endl;
    }
    
    return 0;
}