# Module 1: Core C++ - Classes, Objects, and Basic Resource Management

## Concepts Covered:

- Classes, Objects, Constructors (default, parameterized, copy, move), Destructors

- Member functions, const correctness

- Access specifiers (public, private, protected)

- Operator Overloading (basics like operator<< for output)

- Introduction to RAII (Resource Acquisition Is Initialization) principle

- Basic I/O with std::cout, std::cin, std::fstream

- Learning Objectives:

- Understand the fundamental building blocks of C++: classes and objects.

- Implement proper object lifecycle management using constructors and destructors.

- Apply const correctness for safer and more readable code.

- Grasp the RAII principle as a cornerstone of C++ resource management.

## Problem Statement: 
### Simple Log Management System

#### Description:
Develop a basic log management system that can record messages with different severity levels (e.g., INFO, WARNING, ERROR). The system should allow logging to both the console and a file.

#### Assignment Details:

##### LogEntry Class:

- Create a LogEntry class with members for timestamp, severity level (e.g., an enum or std::string), and the log message itself.

- Implement appropriate constructors and a destructor.

- Overload operator<< to enable easy printing of LogEntry objects to std::ostream (console or file).

#####  Logger Class:

- Create a Logger class responsible for managing log entries.

- It should have methods like logInfo(const std::string& message), logWarning(const std::string& message), logError(const std::string& message).

- Internally, Logger should store LogEntry objects using an std::vector or std::list.

- Implement functionality to write all accumulated log entries to a specified file upon request (e.g., a flushToFile() method or automatically on destruction using RAII).

##### Main Function:

- In main(), create a Logger instance.

- Log several messages of different severities.

- Demonstrate logging to both console and file.

##### Key STL Components to Use:

- std::string for messages and severity.

- std::vector or std::list for storing LogEntry objects.

- std::chrono for timestamps.

- std::fstream for file I/O.
