#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

//Allocates memory for a vector.
Vector* Vector_create()
{
    Vector* ret = (Vector*)calloc(1,sizeof(Vector));
    if(ret != NULL)
        return ret;
    else
        fprintf(stderr, "Error - unable to allocate required memory\n"); //Print error message if the space isn't allocated successfully.
}

// Initialize a vector to be empty
// Pre: 'vector' != NULL
void Vector_ctor_default(Vector *vector)
{
    if(vector != NULL)
    {
        vector->size = 0;
        vector->head = NULL;
        vector->tail = NULL;
    }
    else
        fprintf(stderr, "Error - vector is NULL in call to Vector_ctor_default\n");
    
}

// Deallocate internal structures of the vector
// Note: the user is responsible for deleting all values
// Note: the user is responsible for deleting the actual vector if it was dynamically allocated
void Vector_dtor(Vector *vector)
{
    if(vector != NULL)
    {
        struct Node* temp;
        if ((vector->head->next != NULL)) //If head->next is NULL then there is only one or zero elements stored in the vector.
            for(temp = vector->head->next; temp != NULL; temp = temp->next)
            {
                free(temp->prev);//Free space for all the nodes except the last.
            }
        free(vector->tail); //Free space for the last node, if head->next was null, then head = tail.
        free(vector); //Free the space for the vector frame work.
    }

}

// Insert a new element in the back of the vector
// Pre: 'vector' != NULL
void Vector_pushBack(Vector *vector, void *value)
{
    Node* node = calloc(1,sizeof(Node)); //Allocate space for a new node.
    if(node!=NULL) //If the space was allocated successfully.
    {
        node->value = value; //Set value of the node
        node->index = vector->size+1; //Set index of node.
        if(vector->tail == NULL) //If the vector is empty
        {
            vector->head = node;
            vector->tail = node;//If the vector was empty the first node is both head and tail.
        }
        else //If the vector is not empty.
        {
            vector->tail->next = node;
            node->prev = vector->tail;
            vector->tail = node; //Insert the new node and make it the new tail of the vector.
        }
        vector->size++;//Increase size of vector.
    }
    else
        fprintf(stderr, "Error - unable to allocate required memory\n");//If the space for the new node couldn't be allocated, print error message.
}


// Remove the last element in the vector and return the value
// Pre: the vector is non-empty, 'vector' != NULL
void *Vector_popBack(Vector *vector)
{
    void* ret;
    if(vector->size > 1) //Case if the vector size is greater than 1.
    {
        ret = malloc(sizeof(vector->tail->value));//Space for the return value
        ret = vector->tail->value; //The value to return
        vector->tail = vector->tail->prev; //move tail to the previous node.
        free(vector->tail->next); //free space used by the node removed.
        vector->tail->next = NULL; //Next node after tail is null
        vector->size--; //reduce size of vector.
    }
    else if(vector->size == 1)//Case if vector size is 1.
    {
        ret = malloc(sizeof(vector->tail->value));
        ret = vector->tail->value;
        free(vector->tail);
        Vector_ctor_default(vector);
    }
    else //If the vector is empty return null;
        ret = NULL;
    return ret;    
}

// Return the number of elements in the vector
// Pre: 'vector' != NULL
size_t Vector_size(const Vector *vector)
{
    if(vector != NULL)
        return vector->size;
    else
        fprintf(stderr, "Error - Vector NULL in Vector_size call\n");
}

// Return the value at the given index
// Pre: index < Vector_size(vector)
void *Vector_getElement(const Vector *vector, size_t index)
{
    if(vector != NULL && index < Vector_size(vector))
    {
        Node* n;
        for(n = vector->head; (n != NULL) && (n->index != index); n = n->next)//Find the element that matches the index
        {}
        return n->value;//Return the value of the element that matches the index.        
    }
    else
        fprintf(stderr, "Error - Vector NULL or Index out of bounds in Vector_getElement call\n");
}

// Inserts the given value at the given index (Each component in this vector with an index greater
// or equal to the specified index is shifted upward to have an index one greater than the value 
// it had previously.)
// Pre: index <= Vector_size(vector)
void Vector_insertElement(Vector *vector, size_t index, void* value)
{
    if(vector != NULL && index < Vector_size(vector))
    {
        Node* insert = (Node*)calloc(1,sizeof(Node));
        insert->index = index;
        insert->value = value;
        Node* n;
        for(n = vector->head; n != NULL; n = n->next)//Find where new node is to be inserted
        {
            if(n->index == index)
            {
                if(index == vector->head->index)//If the node replaces the head of the vector
                {
                    vector->head->prev = insert;
                    vector->head = insert;
                }
                else if(index == vector->tail->index)//If the node replaces the tail of the vector
                {
                    vector->tail->prev->next = insert;
                    vector->tail->prev = insert;
                    insert->next = vector->tail;
                }
                else//All other cases
                {
                    n->prev->next = insert;
                    insert->next = n;
                    n->prev = insert;                
                }
            }
            if(n->index >= index)
            {
                n->index++; //Increase the index of all the remaining nodes.
            }
        }
    }
    else
        fprintf(stderr, "Error - Vector NULL or Index out of bounds in Vector_insertElement call\n");
}

// Sets the value of the given element.
// Returns the old value so the user can remove the value.
// Pre: index <= Vector_size(vector)
void *Vector_setElement(Vector *vector, size_t index, void* value)
{
    if(vector != NULL && index < Vector_size(vector))
    {
        void* ret;
        Node* n;
        for(n = vector->head; (n != NULL) && (n->index != index); n = n->next)//Find the correct node
        {}
        ret = n->value; //Get the old value
        n->value = value; //Set the new value
        return ret;
    }
    else
        fprintf(stderr, "Error - Vector NULL or Index out of bounds in Vector_setElement call\n");
}

// Copy the content of the vector into a user given array. That means, after this call, the array 
// contains the pointers pointing to the stored values. Return value is a pointer to the beginning 
// of the array.
// Note: The user is responsible for creating the array and assuring it is large enough
// Pre: 'vector' != NULL
void* Vector_toString(const Vector *vector, void** array)
{
    if(vector != NULL)
    {
        Node* iter;
        int i = 0;
        for(iter = vector->head; iter != NULL; iter = iter->next)
        {
            array[i] = iter->value; //Fill array with the pointers to values.
            i++;
        }
        void* ret = array; //The pointer that points to the beginning of the array.
        return ret;
    }
    else
        fprintf(stderr, "Error - Vector NULL in Vector_toString call\n");
}