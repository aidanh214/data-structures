#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
struct Node {   // Node of the linked list.
    T data;
    struct Node *next = nullptr;

    Node() {}
    ~Node() {}

};

template <typename T>
struct LinkList { 
    int length = 0;
    Node<T> * head = nullptr;
    
    LinkList() { 
        //cout << "In Linklist\n"; 
        }
    ~LinkList() { 
        //cout << "Out Linklist\n";  
        Node<T> * current_node = head;

    }

    T read(int index) {
        // return data from the list at index
        Node<T> *current_node = head;

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
            Node<T> * next_node = current_node->next;
            T data = current_node->data;
            return data;
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
        bool completed = false;

        check_index_in_range(index); // Throws an error if the index is out of range.

        for(int i = 0; i<index;i++ ) { // Loop through all nodes until the index
            prev_node_ptr = current_node_ptr;
            current_node_ptr = current_node_ptr->next;
        }
        
        next_node_ptr = current_node_ptr->next;

        if (index==0) { // If first element, change the head of the list
            head = next_node_ptr;
        }

        delete current_node_ptr;
        length--;
    }
    
    void insert(int index, T new_data) {
        
    }

    private: void check_index_in_range(int index) {
        if (index>(length-1)) {
            throw std::out_of_range ("List index out of range.");
        }
    }
};


int main() {
    

}



