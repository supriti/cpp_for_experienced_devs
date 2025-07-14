#include<iostream>

using namespace std;

class Resource {
public:
    int value;
    Resource(int val) : value(val) {
        cout << "Resource " << value << " constructed." << endl;
    }
    ~Resource() {
        cout << "Resource " << value << " destrcuted." << endl;
    }
    Resource(const Resource&) = delete;
    Resource& operator=(const Resource&) = delete;
};

class sharedResource {
public:
    int id;

    sharedResource(int val): id(val) {
        cout << "SharedResource" << id << " constructed." << endl;
    }
    ~sharedResource() {
        cout << "SharedResource" << id << "destructed." << endl;
    }

    //copy constructor
    sharedResource(const sharedResource& other):id(other.id){
    cout << "SharedResource " << id << " copy constructed." << endl; 
    }

    //operator=
    sharedResource& operator=(const sharedResource& other){
        id = other.id;
        cout << "SharedResource " << id << " copy assigned." << endl;
        return *this;
    }
};

unique_ptr<Resource> createUniqueResource(int val){
    return make_unique<Resource>(val);
}

int main(){
    cout << "--- Starting Smart Pointers Assignment ---" << endl;

    cout << "\n--- Task 1.1: std::unique_ptr Demo ---" << endl;
    {
        unique_ptr<Resource> res1 = make_unique<Resource>(100);
        cout << "res1->value: " << res1->value << endl;
        cout << "(*res1).value: " << (*res1).value << endl;
        cout << "res1.get(): " << res1.get() << endl;
        cout << "Value via raw_ptr: " << (res1.get())->value << endl;

        // Transfer ownership from res1 to res_move
        unique_ptr<Resource> res1_mov = move(res1);
        cout << "res1.get() after move: " << res1.get() << endl;
        cout << "res1_mov.get() after move: " << res1_mov.get() << endl;
        cout << "res1_move->val: " << res1_mov->value << endl;

    }
    cout << "Scope for unique_ptr demo ended. Resource 100 should be destructed." << endl;
    
    // --- Task 1.2: std::shared_ptr - Shared Ownership ---
    cout << "\n--- Task 1.2: std::shared_ptr Demo ---" << endl;
    {

        shared_ptr<sharedResource> shrRes1 = make_shared<sharedResource>(100);
        shared_ptr<sharedResource> shrRes2;
        shared_ptr<sharedResource> shrRes3;

        cout << "Usage count of shared resource: " << shrRes1.use_count() << endl;
        shrRes2 = shrRes1;

        cout << "Usage count of shared resource: " << shrRes1.use_count() << endl;
        shrRes3 = shrRes1;

        cout << "Usage count of shared resource: " << shrRes1.use_count() << endl;
    }

    // --- Task 1.2: Factory Function Returning unique_ptr ---
    cout << "\n--- Task 1.3 Factory Function Returning unique_ptr ---" << endl;
    {
        unique_ptr<Resource> resPtr = createUniqueResource(100);
        cout << "resPtr->value: " << resPtr->value << endl;
    }

    // Task 1.4: Custom Deleter for unique_ptr (Bonus)
    cout << "\n--- Task 1.4: Custom Deleter for unique_ptr ---" << endl;
    {
        
    }
    return 0;
}