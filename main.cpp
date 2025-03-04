// #include "ranges.cpp"
// #include "concepts.cpp"
// #include "shared_ptr.cpp"

// int main()
// {
//     testConcepts();
//     testRanges();

//     testSharedPtr();
//     return EXIT_SUCCESS;
// }

#include <iostream>
#include <string>

#include "Logger/logger.h"

void test_logger()
{
    LOG_ERROR("This is an Error {{i}} {{i}} {{i}}", 1, 3, 4);
    LOG_DEBUG("This is an Error {{i}}", 2.0f);
    std::string s = "Ashish";
    LOG_INFO("My name is {{s}}", s.c_str());
}

int main() {

    // Find a way to save this file before the main.
    LogInitializer init;

    std::cout<<"Entering Main\n";
    test_logger();
    return 0;
}