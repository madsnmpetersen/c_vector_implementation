#ifndef __VECTOR__H__
#define __VECTOR__H__
#include <stdlib.h>

//-----------------------------------------------------------------------------
// Vector, implemented as a double-linked list.
// There are prerequisites mentions in each function description. The user has to make sure
// that these conditions are fulfilled before the function call. Nevertheless, the function
// should check these conditions as well and react accordingly (e.g., exit the program)
// 
// You can implement more functions if you like.
//-----------------------------------------------------------------------------

// forward declare structs and bring them from the tag namespace to the ordinary namespace
typedef struct Vector Vector;
typedef struct Node Node;


// actually define the structs
struct Vector  //Vector is just the framework, all the values are stored as nodes.
{
    int size;
    Node* head;
    Node* tail;
};

struct Node //Used for storing elements in the vector, contains pointers to the next and previous node.
{
    Node* prev;
    Node* next;
    int index;
    void* value;
};
//Allocate space for a Vector
Vector* Vector_create();

// Initialize a vector to be empty
// Pre: 'vector' != NULL
void Vector_ctor_default(Vector *vector);

// Deallocate internal structures of the vector
// Note: the user is responsible for deleting all values
// Note: the user is responsible for deleting the actual vector if it was dynamically allocated
void Vector_dtor(Vector *vector);

// Insert a new element in the back of the vector
// Pre: 'vector' != NULL
void Vector_pushBack(Vector *vector, void *value);

// Remove the last element in the vector and return the value
// Pre: the vector is non-empty, 'vector' != NULL
void *Vector_popBack(Vector *vector);

// Return the number of elements in the vector
// Pre: 'vector' != NULL
size_t Vector_size(const Vector *vector);

// Return the value at the given index
// Pre: index < Vector_size(vector)
void *Vector_getElement(const Vector *vector, size_t index);

// Inserts the given value at the given index (Each component in this vector with an index greater
// or equal to the specified index is shifted upward to have an index one greater than the value 
// it had previously.)
// Pre: index <= Vector_size(vector)
void Vector_insertElement(Vector *vector, size_t index, void* value);

// Sets the value of the given element.
// Returns the old value so the user can remove the value.
// Pre: index <= Vector_size(vector)
void *Vector_setElement(Vector *vector, size_t index, void* value);

// Copy the content of the vector into a user given arry. That means, after this call, the array 
// contains the pointers pointing to the stored values. Return value is a pointer to the beginning 
// of the array.
// Note: The user is responsible for creating the array and assuring it is large enough
// Pre: 'vector' != NULL
void *Vector_toString(const Vector *vector, void** array);

#endif
