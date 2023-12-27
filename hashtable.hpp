#include "linklist.hpp"
#include "dynarray.hpp"
using namespace std;

template <typename data_type, typename key_type = string> struct HashTable {
    
    private:
    /* Node substructure. */
    template <typename node_type,typename node_key_type> struct Node {
        key_type *key = nullptr;
        node_type data;
        Node<node_type,node_key_type> *next = nullptr;
        ~Node() {
            delete key;
        }
    };

    /* Properties defns. */
    hash<key_type> hasher;
    int table_length = 4;
    DynArray<Node<data_type,key_type>* > node_array;

    /* Private method to get the correct index of a string */    
    int get_index(key_type key) {
        int key_hash = hasher(key);
        int key_index = key_hash % table_length;
        return key_index;
    }

    public:
    /* Constructor */
    HashTable() {;
        for (int i=0;i<table_length;i++) {
            node_array.append(new Node<data_type,key_type>());
        }
    }

    data_type lookup(key_type key) {
        int key_index = get_index(key);
        Node<data_type,key_type> *current = node_array[key_index];
        Node<data_type,key_type> *prev;
        
        current = current->next;
        while(current!=nullptr) {
            if(*current->key==key){
                break;
            }
            current = current->next;
        } 

        if(current==nullptr) {
            std::cout << "Key not in table.\n";
        } else {
            return current->data;
        }
    }

    data_type operator[](key_type key) {
        return lookup(key);
    }

    /* Insert a new key:data pair. */
    void insert(key_type key, data_type new_data) {
        //std::cout << key << "\n";
        int key_index = get_index(key);

        // Find correct place for the new data, add it to the list at the hashed address.
        Node<data_type,key_type> *current = node_array[key_index];
        Node<data_type,key_type> *prev;
        
        prev=current;
        current = current->next;
        
        while( // Iterate until the end of the linked list or correct key is found
            (current!=nullptr) 
            ) {
            
            if(*current->key == key) {
                break;
            }
            prev=current;
            current = current->next;

        } 

        if(current == nullptr) { // If the loop stopped at the end of a list
            prev->next = new Node<data_type,key_type>();
            prev->next->data = new_data;
            key_type *new_key_obj = new key_type;
            *new_key_obj = key;
            prev->next->key = new_key_obj;

        } else { // If while loop stopped on a node with the same key
            current->data = new_data;
        }

    }
    
    /* Remove a key from the table. */
    void remove(key_type key) {
        int key_index = get_index(key);
        Node<data_type,key_type> *current = node_array[key_index];
        Node<data_type,key_type> *prev = node_array[key_index];
        Node<data_type,key_type> *next = node_array[key_index];

        while (
            (current->next!=nullptr) &&
            (*(current->key)!=key)
        ) {
            prev=current;
            current = current->next;
        } // Iterate until either found the key or end of the list at the address

        if(*(current->key)==key) {
            next=current->next;
            delete current;
            prev->next = next;
        } else {
            cout << "Key not in table.\n";
        }
    }
};
