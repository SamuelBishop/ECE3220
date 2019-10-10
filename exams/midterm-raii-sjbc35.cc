/* practical-raii.cc */

#include <cstddef>  // std::size_t

class buffer {
public:
    // (a) 5 points
    // Default constructor AND converting constructor declaration.
    //
    // Provide a function parameter named 'buffer_size' whose type is
    // `std::size_t', and whose value defaults to `buffer::bufsize_default'
    // when the program does not provide an argument for the parameter
    // `buffer_size', e.g.,
    //      buffer b1;          // buffer_size = buffer::bufsize_default
    //      buffer b2 {100};    // buffer_size = 100
    //      buffer b3(500);     // buffer_size = 500
    //
    // vvv--- YOUR CODE HERE ---vvv
    
    // default ctor
    buffer(){ bufsize = buffer::bufsize_default };

    // converting ctor
    buffer( int bufferSize ){ bufsize = bufferSize };

    // destructor declaration
    ~buffer();

private:
    // per instance data members
    char *pbuf ;    // pointer to an array of char
    const std::size_t  bufsize ;  // the number of chars in the array

    // static data member declaration
    static const std::size_t  bufsize_default ;
};

// Definition and initialization of the constant-valued static data member
// `buffer::bufsize_default'.
const std::size_t  buffer::bufsize_default = 1000 ;


// (b) 25 points
// Write the code that defines the buffer class's default constructor AND
// converting constructor, as declared in part (a) above.
// Hint: Resource Acquisition Is Intialization (RAII).
//
// Use C++'s class 'member initializer list' syntax to assign initial values to
// this buffer intance's data members as described here:
// * Use C++'s dynamic memory allocation operator (do not use the C language's
//   malloc() function) to allocate storage for a char array that has
//   `buffer_size' elements, and store the array's address in this instance's
//   `pbuf' data member.
// * Store the value `buffer_size' in this instance's `bufsize' data member.
//   
// vvv--- YOUR CODE HERE ---vvv

X::~buffer(){ }



// (c) 10 points
// Write the code that defines the buffer class's destructor method.
// Hint: Resource Acquisition Is Intialization (RAII).
//
// Use the array form of C++'s dynamic memory deallocation operator (do not use
// C's free() function) to deallocate the storage for the char array whose
// address resides in this instance's `pbuf' pointer variable.
//
// vvv--- YOUR CODE HERE ---vvv

X::~buffer(){
    delete pbuf;
    delete bufsize;
    delete bufsize_default;
}

// DO NOT MODIFY FUNCTION MAIN()
int main()
{
    buffer b1;          // buffer with default size (1000 chars)
    buffer b2 {100};    // buffer with 100 chars
    buffer b3(500);     // buffer with 500 chars
    return 0;
}
