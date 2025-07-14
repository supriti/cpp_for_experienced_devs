# C++ Templates Assignment:
## Generic Data Structures and Algorithms
### Objective:
This assignment aims to solidify your understanding of C++ templates by implementing generic data structures and algorithms. You will explore function templates, class templates, and their practical applications.

### Submission:
Your submission should include all source code files (.h and .cpp) and a README.md file explaining how to compile and run your code, along with any design choices or challenges faced.

#### Part 1: Function Templates - Generic Utility Functions
##### Task 1.1: max and min Function Templates

Implement two function templates: myMax and myMin.

template <typename T> T myMax(T a, T b);

template <typename T> T myMin(T a, T b);

These templates should return the maximum and minimum of two values of any comparable type T.

##### Task 1.2: swap Function Template

Implement a function template mySwap that swaps the values of two variables of any type T.

template <typename T> void mySwap(T& a, T& b);

##### Task 1.3: printArray Function Template

Implement a function template printArray that prints the elements of an array of any type T.

template <typename T> void printArray(const T arr[], int size);

##### Testing (Part 1):
In your main function, demonstrate the usage of these function templates with at least three different built-in types (e.g., int, double, char) and one custom class (e.g., a simple Point struct you define).

#### Part 2: Class Templates - Generic Data Structures
##### Task 2.1: Generic Pair Class Template

Implement a class template Pair that can hold two values of potentially different types: 

The Pair class should have:

- Private member variables first (type T1) and second (type T2).

- A constructor to initialize first and second.

- Public getter methods getFirst() and getSecond().

- A public method print() that prints the values of first and second.

#####Task 2.2: Generic Stack Class Template

Implement a class template Stack that can store elements of any type T.

The Stack class should use a std::vector internally to store its elements.

It should provide the following public methods:

- void push(const T& element);

- T pop(); (should throw an exception or handle error if stack is empty)

- T peek() const; (returns the top element without removing it; handle empty stack)

- bool isEmpty() const;

- int size() const;

#### Testing (Part 2):
In your main function, demonstrate the usage of:

- Pair with different combinations of types (e.g., Pair<int, double>, Pair<std::string, bool>).

- Stack with at least two different types (e.g., Stack<int>, Stack<std::string>). Push and pop several elements, check for emptiness, and peek.

#### Part 3: Advanced Template Concepts (Optional/Bonus)
##### Task 3.1: Template Specialization (for myMax or myMin)

Choose either myMax or myMin from Part 1. Implement a template specialization for const char* types that compares C-style strings lexicographically (using strcmp).

##### Task 3.2: Non-Type Template Parameters - StaticArray

Implement a class template StaticArray that uses a non-type template parameter for its fixed size.

template <typename T, int N>

The StaticArray should internally use a C-style array T arr[N];

It should provide:

- A constructor to initialize elements (optional, or just default initialization).

- An overloaded operator[] for element access (both const and non-const versions).

- A size() method that returns N.

##### Testing (Part 3):

Demonstrate the specialized myMax or myMin with const char* arguments.

Create instances of StaticArray with different types and sizes (e.g., StaticArray<double, 10>, StaticArray<char, 5>). Access and modify elements using operator[].

#### Deliverables:
##### Source Code:

- main.cpp (for main function and testing all parts)

- utils.h (for function templates from Part 1)

- pair.h (for Pair class template)

- stack.h (for Stack class template)

- static_array.h (for StaticArray class template, if attempted)

- Any other necessary header or source files.

