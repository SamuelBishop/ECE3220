#include <memory>

int main()
{
    // Variable 'ai' is an instance of C++'s std::allocator<T> template class, 
    // and is specialized to manage storage for values of type 'int'.
    std::allocator<int>  ai ;

    // (a) (5 points)
    // Use the allocator object 'ai' to dynamically allocate enough memory from
    // the heap to store one object of type 'int'. Store in pointer variable 'p'
    // the address of the allocated memory.
    // vvv--- write your answer here ---vvv
    
    ai.size_t = 1;
    int *p = new int[ai.size_t];


    // (b) (5 points)
    // Use 'ai' to create and initialize one int object within the memory where 'p'
    // is pointing. Define the int’s initial value as 123.
    // vvv--- write your answer here ---vvv

    
    // (c) (5 points)
    // Use 'ai' to uncreate (destruct) the int object within the memory where 'p' 
    // is pointing.
    // vvv--- write your answer here ---vvv


    // (d) (5 points)
    // Use 'ai' to free the dynamically allocated memory where 'p' is pointing.
    // vvv--- write your answer here ---vvv


    return 0;
}

