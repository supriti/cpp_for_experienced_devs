# Module 2: 
# Inheritance, Polymorphism, and Virtual Functions
## Concepts Covered:Concepts Covered:

- Inheritance (public, protected, private)

- Base classes and derived classes

- Virtual functions, pure virtual functions, abstract classes

- Polymorphism and dynamic dispatch

- Virtual destructors

- override and final specifiers

- Introduction to STL algorithms with custom predicates/lambdas.

## Learning Objectives:

- Master the concepts of inheritance and polymorphism to design flexible and extensible class hierarchies.

- Understand when and why to use virtual functions and virtual destructors.

- Apply abstract classes to define interfaces.

- Utilize STL algorithms effectively with custom logic.

## Problem Statement:

#### Document Processing System

##### Description
Design a system that can process different types of documents (e.g., Text Documents, Image Documents, PDF Documents) in a unified manner. Each document type will have specific processing steps.

##### Assignment Details:

###### Document Abstract Base Class:

- Create an abstract base class Document.

- It should have common attributes like title and author.

- Declare a pure virtual function process() that derived classes must implement.

- Include a virtual destructor.

###### Derived Document Classes:

- Create at least three concrete derived classes: TextDocument, ImageDocument, PdfDocument.

- Each derived class should have unique attributes (e.g., wordCount for TextDocument, resolution for ImageDocument, pageCount for PdfDocument).

- Implement the process() method for each derived class, printing a message specific to its processing (e.g., "Analyzing text...", "Applying image filters...", "Extracting PDF metadata...").

###### DocumentProcessor Class:

- Create a DocumentProcessor class that can hold a collection of Document raw pointers (Document*).

- It should have a method addDocument(Document* doc).

- Implement a processAllDocuments() method that iterates through the collection and calls process() on each document using polymorphism.

- ***Problem for Future Modules: Notice the challenge of managing the lifetime of Document* objects added to the processor. Who owns them? Who is responsible for deleteing them? This problem will be elegantly solved by smart pointers in Module 4.**

##### Main Function:

- In main(), create instances of various document types using new.

- Add them to a DocumentProcessor.

- Call processAllDocuments() and observe the polymorphic behavior.

- Crucially: Manually delete the Document objects created with new at the end of main() to avoid memory leaks. This reinforces the pain point that smart pointers will address.

- Key STL Components to Use:

- std::vector of Document*.

- std::string for document attributes.

- std::for_each or other relevant STL algorithms for iterating and processing.