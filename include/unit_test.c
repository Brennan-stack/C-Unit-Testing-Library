#include "unit_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
*   This function initializes a new unit test with a given name.
*   
*   @param name - char* array representing the name of the test case.
*   @returns unit_test* pointer representing the new and initialized 
*   unit test.
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
struct unit_test* unit_test_init(char* name) {
    struct unit_test *u_test = malloc(sizeof(struct unit_test));
    u_test->name = name;
    u_test->num_passed = 0;
    u_test->num_failed = 0;
    return u_test;
}

/*
*   This function starts a unit test and is responsible for executing
*   and printing out the unit test.
*   
*   @param *test - unit_test structure representing the test you will be
*       running.
*   @param void (*start)() - function pointer representing the start funciton 
*       for the unit test.
*   @param void (*print)() - function pointer representing the print 
*       function for the unit test. If NULL, the print function defaults to 
*       the built-in print funciton.
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_start(struct unit_test *test, void (*start)(), void (*print)()) {
    assert(test != NULL);
    assert(start != NULL);
    printf("==========%s Results==========\n", test->name);
    start(test);

    if (print == NULL) {
        unit_test_printf(test);
    }
    else
    {
        print(test);
    }
    free(test);
}

/*
*   This function takes a unit_test struct and prints out the results to 
*   standard output.
*
*   @param *test - the unit_test you wish to print out. 
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_printf(struct unit_test *test) {
    printf("Total Tests:%d\n", test->num_passed + test->num_failed);
    printf("Tests Passed: %d\n", test->num_passed);
    printf("Tests Failed: %d\n", test->num_failed);
    printf("Percent Passing: %02f\n", test->num_passed / test->num_failed);
}

/*
*   This function takes two pointers and tests if they point to the same memory
*   address. 
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param *a - the first pointer you are comparing
*   @param *b - the second pointer you are comparing
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_assert_same_address(struct unit_test *test, void *a, void *b) {
    printf("%d - \033[1;37m%s: \033[1;36mAssert Same Address\033[0m on addresses"
             " \033[0;36m0x%p\033[0m and \033[0;36m0x%p\033[0m:", 
             test->num_passed + test->num_failed, test->name, a, b);
    if (a == b) {
        test->num_passed++;
        printf(" \033[1;32mPASSED\n\033[0m");
    }
    else
    {
        test->num_failed++;
        printf(" \033[1;31mFAILED\n\033[0m");
    }
    
}

/*
*   This function takes two floats and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first float you are comparing
*   @param b - the second float you are comparing
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_assert_float_equals(struct unit_test *test, float a, float b) {}

/*
*   This function takes two integers and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first integers you are comparing
*   @param b - the second integers you are comparing
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_assert_int_equals(struct unit_test *test, int a, int b) {}

/*
*   This function takes two doubles and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first doubles you are comparing
*   @param b - the second doubles you are comparing
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_assert_double_equals(struct unit_test *test, double a, double b) {}

/*
*   This function takes two longs and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first long you are comparing
*   @param b - the second long you are comparing
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_assert_long_equals(struct unit_test *test, long a, long b) {}

/*
*   This function takes two chars and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first char you are comparing
*   @param b - the second char you are comparing
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_assert_char_equals(struct unit_test *test, char a, char b) {}



int main()
{
    int a = 1;
    int b = 2;
    struct unit_test *test = unit_test_init("Unit Test");
    unit_test_assert_same_address(test, &a, &a);
    unit_test_assert_same_address(test, &a, &b);
    unit_test_assert_same_address(test, &a, &a);
    unit_test_assert_same_address(test, &a, &a);
    unit_test_assert_same_address(test, &a, &a);

    unit_test_assert_int_equals(test, 1, 1);
    unit_test_assert_float_equals(test, 1.0f, 1.0f);
    unit_test_assert_double_equals(test, 1.0, 1.0);
    unit_test_assert_long_equals(test, 100L, 100L);
    unit_test_assert_char_equals(test, 'a', 'a');
}