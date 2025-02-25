#include "ranges.cpp"
#include "concepts.cpp"
#include "shared_ptr.cpp"

int main()
{
    testConcepts();
    testRanges();

    testSharedPtr();
    return EXIT_SUCCESS;
}