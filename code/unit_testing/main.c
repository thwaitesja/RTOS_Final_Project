#include <stdio.h>

#define CTEST_MAIN
#define CTEST_SEGFAULT
#define CTEST_COLOR_OK

#include "ctest.h"



int main(int argc, const char *argv[])
{
    int result = ctest_main(argc, argv);

    printf("\nRan all of the tests associated with the unit tests for the final project\n");
    return result;
}

