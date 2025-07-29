#include<iostream>
#include<vector>

using namespace std;

int main(){
    int num;
    vector<int> fibonacci(num+1);
    cout << "Enter a number: " << endl;
    cin >> num;

    if (num == 0) {
        cout << "Fibonacci value: " << 0;
        return 0;
    }

    if (num == 1 || num == 2) {
        cout << "Fibonacci value: " << 1;
        return 0;
    }

    fibonacci[0] = 0;
    fibonacci[1] = 1;
    for (int i = 2; i <= num; i++){
        fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    }

    cout << "Fibonnaic Sum: " <<  fibonacci[num] << endl;
    return 0;
}