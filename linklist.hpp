#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
struct LinkList { 

    private:
    void check_index_in_range(int index) {
        if (index>(length-1)) {
            throw std::out_of_range ("List index out of range.");
        }
    }
    
    template <typename node_type> struct Node {   // Node of the linked list.
    node_type data;
    Node<node_type> * next = nullptr;
    };
    
    Node<T> * head = nullptr;

    public:
    int length = 0;

    ~LinkList() { 
        // Destructor  
        Node<T> * current_node = head;
        Node<T> * next_node;
        for(int i=0; i<length;i++) {
            next_node = current_node->next;
            delete current_node;
            current_node = next_node;
        }
    }
    
    T read(int index) {
        // return data from the list at index
        Node<T> *current_node = head;
        
        check_index_in_range(index); // Make sure the list index is in range.
        
        for(int i=0; i<index; i++) {
            current_node = current_node->next;
        }        

        return current_node->data;
    }

    T operator[](int index) {
        return read(index);
    }

    void push(T new_data) {
        // append a new data point to the top of the list
        
        Node<T> *new_node; // Initialise new node
        new_node = new Node<T>;
        new_node->data = new_data;

        if(head == nullptr) { // If first element in list
            head = new_node;
            // cout << "Added new value successfully.\n";
        }
        else {
            new_node->next = head;
            head = new_node;
        }
        
        length++; //add one to length variable
    }

    T pop() { 
        
        if(length>0) {
            Node<T> * current_node = head;

            T data = current_node->data; // Return data from top node.
            return data;
                        
            head = current_node->next; // Remove top node.
            delete current_node;  

        }

        else {
            throw std::out_of_range ("Can't pop from list with no elements.");
        }
    }

    void append(T new_data) {
        Node<T> * current_node = head;
        Node<T> * prev_node;
        Node<T> * new_node;
        
        new_node = new Node<T>; // Generate new node.
        new_node->data = new_data;

        for(int i=0; i<(length-1); i++) { //Get pointer to the node at the end of the list
            current_node = current_node->next;
        }
        
        if(!(current_node==nullptr)) { //If list is not empty
            current_node->next = new_node;
        }

        else { //If list is empty
            head = new_node;
        }

        length++; // add one to length
    }

    void remove(int index) {
        Node<T> *prev_node_ptr;
        Node<T> *next_node_ptr;
        Node<T> *current_node_ptr = head;

        check_index_in_range(index); // Throws an error if the index is out of range.

        for(int i = 0; i<index;i++ ) { // Loop through all nodes until the index
            prev_node_ptr = current_node_ptr;
            current_node_ptr = current_node_ptr->next;
        }
        
        next_node_ptr = current_node_ptr->next;

        if (index==0) { // If first element, change the head of the list
            head = next_node_ptr;
        }
        
        else { // Update "next" pointer of previous node
            prev_node_ptr->next = next_node_ptr;
        }

        delete current_node_ptr;
        length--;
    }
    
    void insert(int index, T new_data) { 
        // Inserts node at an index. Displaces the node at that index forwards.
        // For list of length n:
        //        insert(index=n) will append. 
        //        insert(index = n-a) for any a<n will insert and displace. 

        Node<T> * current_node = head;
        Node<T> * previous_node;
        Node<T> * new_node;
        check_index_in_range(index); // Safety check
       
        //std::cout << "insertion commenced\n";
        for(int i=0;i<index;i++) {
            previous_node = current_node;
            current_node = current_node->next;
        }
            
        new_node = new Node<T>; // Initialising node
        new_node->data = new_data;

        if(index==0) { // If first element, update head pointer
            head = new_node;
        }
        else { // If not the first element, update pointer of previous node
            previous_node->next = new_node;
        }
        
        new_node->next = current_node; // Displace first node to after the new node
        length++;
    }

    void replace(int index, T new_data) {
        check_index_in_range(index);
        remove(index);
        insert(index, new_data);
    }

};



