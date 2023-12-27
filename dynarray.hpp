#include <iostream>

using namespace std;

template <typename T> struct DynArray {
    private:
    
    T *array_internal = new T [4];
    unsigned int array_size = 4;
    unsigned int current_length = 0;

    public:

    /* Function to resize the dynamic array. Truncates the array if the new size is smaller than the current size. */
    void resize(unsigned int new_size) {
        T *new_array = new T[new_size];
        const int smallest_size = min(array_size, new_size); //will only iterate till the end of whichever is smallest
        
        for(int i=0;i<smallest_size;i++){
            new_array[i]=array_internal[i];
        }
        
        delete[] array_internal;
        array_internal = new_array;
        array_size = new_size;
    }

    /* Insert a new element into the array, replacing whatever's there. */
    void insert(const T new_element, const unsigned int index) {
        if(index>=array_size){
            resize(index+1);
        }
        if(index>=current_length) {
            current_length = index+1;
        }

        array_internal[index] = new_element;
    }   

    /* Read a value from an index. Looping index so that can never be out of range:
    once index is larger than the array it loops back around to the front. */
    T read(unsigned int index) {
        index = index % array_size;
        return array_internal[index];
    }

    T operator[](unsigned int index) {
        return read(index);
    }

    /* Append an element to the dynamic array */
    void append(const T new_element) {
        if(current_length==array_size) {
            resize(array_size*2);
        }

        array_internal[current_length] = new_element;
        current_length++;
    }
    
    /* Get the current size of the dynamic array */
    unsigned int size() {
        return current_length;
    }

    /* Destructor */
    ~DynArray() {
        // cout << "Array out.\n";
        delete[] array_internal;
    }
    
};