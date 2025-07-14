# Smart Pointers 
## std::unique_ptr and std::shared_ptr
### Background: 
Raw pointers are prone to memory leaks and dangling pointers. Smart pointers automate memory management, improving safety and reducing boilerplate.

#### Task 1.1: std::unique_ptr - Exclusive Ownership

Implement a simple class named *Resource* that prints messages when its constructor, destructor, copy constructor, and copy assignment operator are called.

C++

```cpp
`
class Resource {
public:
    int value;
    Resource(int val) : value(val) { std::cout << "Resource " << value << " constructed." << std::endl; }
    ~Resource() { std::cout << "Resource " << value << " destructed." << std::endl; }
    // Disable copy operations to highlight unique_ptr's behavior
    Resource(const Resource&) = delete;
    Resource& operator=(const Resource&) = delete;
};`

```

In your main function:

- Create a std::unique_ptr<Resource> using std::make_unique.

- Demonstrate that unique_ptr cannot be copied (std::unique_ptr<Resource> res2 = res1; should cause a compile error).

- Demonstrate ownership transfer using std::move. After moving, verify that the original unique_ptr is null (e.g., by checking nullptr).

- Access the raw pointer using .get() and the managed object using * or ->.

- Show that when the unique_ptr goes out of scope, the Resource is automatically destructed.

#### Task 1.2: std::shared_ptr - Shared Ownership

Using the same Resource class (but enable copy operations for Resource if you want to see them, or use a different class if Resource is still deleteing copy operations):

```cpp
    // A copyable Resource for shared_ptr demo
    class SharedResource {
    public:
        int id;
        SharedResource(int val) : id(val) { std::cout << "SharedResource " << id << " constructed." << std::endl; }
        ~SharedResource() { std::cout << "SharedResource " << id << " destructed." << std::endl; }
        SharedResource(const SharedResource& other) : id(other.id) { std::cout << "SharedResource " << id << " copy constructed." << std::endl; }
        SharedResource& operator=(const SharedResource& other) { id = other.id; std::cout << "SharedResource " << id << " copy assigned." << std::endl; return *this; }
    };
```
In your main function:

- Create a std::shared_ptr<SharedResource> using std::make_shared.

- Create multiple std::shared_ptr objects that share ownership of the same SharedResource instance (e.g., by copying the first shared_ptr).

- Print the use count (.use_count()) after each copy or assignment to observe how it changes.

- Demonstrate that the SharedResource is destructed only when the last shared_ptr owning it goes out of scope.

- Briefly explain in your README.md the difference between std::make_shared and new SharedResource(...) followed by std::shared_ptr<SharedResource>(...).

#### Task 1.3: Factory Function Returning unique_ptr

- Write a function createUniqueResource(int value) that returns a std::unique_ptr<Resource> (from Task 1.1).

- Call this function in main and store the returned unique_ptr.

- Demonstrate that the ownership is correctly transferred from the function to the caller.

#### Task 1.4: Custom Deleter for unique_ptr (Bonus)

- Implement a custom deleter (e.g., a lambda or a functor) that prints a message before deleting the Resource object.

- Create a std::unique_ptr<Resource, CustomDeleterType> using this custom deleter.

- Observe the output to confirm your custom deleter is invoked.