# Module 3: 
# Templates and Advanced STL Containers
## Concepts Covered:

- Function Templates

- Class Templates

- Template Metaprogramming (brief introduction, e.g., std::enable_if or if constexpr)

- Advanced STL Containers: std::map, std::set, std::unordered_map, std::unordered_set, std::priority_queue.

- Iterators and range-based for loops.

- Custom comparators for ordered containers.

## Learning Objectives:Learning Objectives:

- Write generic code using function and class templates.

- Choose the appropriate STL container for a given data storage and retrieval scenario.

- Leverage iterators and range-based for loops for efficient container traversal.

## Problem Statement: Generic Inventory Management System

### Description:
Building on the concept of managing collections from Module 2, design a generic inventory system that can manage items of any type, identified by a unique ID. The system should support adding, removing, updating, and querying items efficiently.

### Assignment Details:

#### InventoryItem Concept:InventoryItem Concept:

Define a concept (e.g., a simple struct or class) for an InventoryItem that has at least an id (e.g., std::string or int) and a name.

You can make this a template parameter for the Inventory class.

Connection to Module 2: Consider how InventoryItem could be a base class, and specific items (like Book, Product) could derive from it, allowing for polymorphic behavior within a generic container.

#### Inventory Class Template:

Create a class template Inventory<T, ID_Type> where T is the type of the item (e.g., Product, Book) and ID_Type is the type of the item's unique identifier.

Internally, use an std::map<ID_Type, T> or std::unordered_map<ID_Type, T> to store items, mapping their ID to the item object. Discuss the pros and cons of each choice.

Implement methods:

addItem(const T& item): Adds an item. Handle duplicate IDs.

removeItem(ID_Type id): Removes an item by ID.

getItem(ID_Type id): Retrieves an item by ID (return T* or std::optional<T>).

updateItem(ID_Type id, const T& newItemData): Updates an existing item.

getAllItems(): Returns a std::vector<T> of all items.

Problem for Future Modules: If T itself were a dynamically allocated object (like Document from Module 2), how would Inventory<T*, ID_Type> handle ownership? This highlights the need for std::unique_ptr and std::shared_ptr to manage resources within generic containers, which will be covered in Module 4.

#### Custom Item Types:

Define at least two concrete item types, e.g., Product (with price, quantity) and Book (with author, isbn).

#### Main Function:

Demonstrate the Inventory template with both Product and Book types.

Perform add, remove, update, and retrieve operations.

Use range-based for loops to print all items in the inventory.

#### Key STL Components to Use:

std::map or std::unordered_map for efficient key-value storage.

std::string for IDs and names.

std::vector for returning collections of items.

std::optional (C++17) for getItem return type if an item might not be found.