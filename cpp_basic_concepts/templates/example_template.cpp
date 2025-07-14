#include<iostream>
#include<string>


//class templates
template <typename T>
class Box {
public:
    T val;
    Box(T v) : val(v) {}
    T getVal() const {return val;};
};

//function templates
template <typename T>
T max(T a, T b){
    return (a > b) ? a : b;
    
}
int main() {
    //Function templates
    int i_max = max(5,10);
    std::cout << "i_max: " << i_max << std::endl;

    int d_max = max(3.14, 2.3);
    std::cout << "d_max: " << d_max << std::endl;

    std::string s_max = max("hello", "world");
    std::cout << "s_max: " << s_max << std::endl;

    //Class templates
    Box<int> intBox(4);
    Box<std::string> strBox("Hello");

    std::cout << "intBox value: " << intBox.getVal() << std::endl;
    std::cout << "strBox value: " << strBox.getVal() << std::endl;



    return 0;
}