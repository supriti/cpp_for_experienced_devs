#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Document {
    string title;
    string author;

public:
    Document(string t_name, string a_name): 
    title(t_name), author(a_name) 
    {}

    virtual ~Document() {
        cout << "Document destructor called for: " << title << endl;
    }

    virtual void process() = 0;
    const string& getTitle() {return title;}
    const string& getAuthoer() {return author;}

};

class TextDocument: public Document {
    int wordCount;

public:
    TextDocument(string t_name, string a_name, int wordCount) 
    : Document(t_name, a_name), wordCount(wordCount){ }
    
    void process() override{
        cout << "Analyzing text..." << endl;
    }

    ~TextDocument() override {
        cout << "TextDocument destructor called." << endl;
    }

};

class ImageDocument: public Document {
    int resolution;

public:
    ImageDocument(string t_name, string a_name, int res)
    : Document(t_name, a_name), resolution(res) { }
    
    void process() override{
        cout << "Applying image filters.." << endl;
    }

    ~ImageDocument() override {
        cout << "ImageDocument destructor called." << endl;
    }
};

class PdfDocument: public Document {
    int pageCount;
public:
    PdfDocument(string t_name, string a_name, int pgCnt)
    : Document(t_name, a_name), pageCount(pgCnt) 
    { }

    void process() override{
        cout << "Extracting PDF metadata.." << endl;
    }

    ~PdfDocument() override {
        cout << "PdfDocument destructor called." << endl;
    }

};

class DocumentProcessor {
    vector<Document* > docs;
public:
    void addDocument(Document *doc) {
        if (doc) {
            docs.push_back(doc);
            cout << "Added document " << doc->getTitle() << endl;
        }
    }

    void processAllDocuments() {
        cout << "Processing all the documents" << endl;

        for(Document* doc_ptr: docs) {
            if(doc_ptr) {
                doc_ptr->process();
            }
        }

        cout << "Finished processing all the documents" << endl;
    }

    ~DocumentProcessor() {
        cout << "Docuemnt Processor destructor" << endl;

        for(Document *doc_ptr: docs) {
            delete doc_ptr;
        }
        docs.clear();
        cout << "All docuemnts deleted" << endl;
    }
};

int main() {
    DocumentProcessor processor;

    Document *textDoc = new TextDocument("Report Q1 2025", "John Doe", 5000);
    Document *imageDoc = new ImageDocument("Vacation Photo", "Jane Smith", 1920);
    Document *pdfDoc = new PdfDocument("User Manual v2.0", "Acme Corp", 120);

    processor.addDocument(textDoc);
    processor.addDocument(imageDoc);
    processor.addDocument(pdfDoc);

    processor.processAllDocuments();

    return 0;
}