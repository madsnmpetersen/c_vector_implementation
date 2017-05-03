#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "string_reader.h"

/* qsort C-string comparison function */
int cstring_cmp(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

/*Used to create a vector from a text file, putting each line of text in a node in the vector*/
Vector* Vectorize_file(char* filename)
{
    Vector* ret = Vector_create(); //Allocates space for the vector frame
    Vector_ctor_default(ret); //inits the vector to be empty
    FILE* fp = fopen(filename,"r"); //opens the file specified as argument for the function
    if(fp) //If the file is successfully opened, continue.
    {
        char* value;
        char buffer[4096]; //This is the maximum number of symbols that can be contained in a line of text, if there is more than 4096 characters in a line, then it is split in two.
        while (fgets(buffer, 4096, fp))//While reading from the file is successfull keep looping. 4095 characters is read from the file, or until a newline occurs.
        {
            value = (char*)malloc(sizeof(buffer)); //Allocate space for the line of text.
            strncpy(value,buffer,strlen(buffer)-1); //Copy everything but the newline.
            Vector_pushBack(ret, value); //Store the line of text in the vector.
        }
        fclose(fp); //Close the file when done reading from it.
        return ret; //Return the vector that is created from the file.
    }
    else
        return NULL; //If the file is not opened successfully return null.
}

int main(int argc, char** argv)
{
    if(argc != 2) //If there aren't exactly 1 argument passed(one beyond the executable name), print an error.
    {
        fputs("Must pass exactly 1 argument, the text file",stderr);//Print to standard error.
        return 1; //Exit with error state 1.
    }
        
    Vector* myVector = Vectorize_file(argv[1]);
    if(myVector == NULL) //If null is returned the file wasn't opened successfully.
    {
        fputs("Error opening file",stderr); //Print that the file wasn't opened to stderr.
        return 1; //Exit with error state 1.
    }
    char* array[myVector->size]; //Create an array of size = current size of the vector.
    Vector_toString(myVector,(void**)array); //Get the pointers to the values stored in the vector in the array just created.
    size_t array_len = sizeof(array) / sizeof(char*); //Indicating the size of the array, for qsort.
    qsort(array,array_len,sizeof(char*),cstring_cmp); //Sort the lines stored in the vector.
    int i;
    for(i = 0; i < array_len; i++)
    {
        printf("%s\n",array[i]); //Print the sorted array.
    }
    return 0;
}