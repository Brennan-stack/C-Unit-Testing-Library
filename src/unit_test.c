#include "../include/unit_test.h"
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
    unit_test_print_header(test);
    start(test);
    
    if (print == NULL) {
        unit_test_print_summary(test);
    }
    else
    {
        print(test);
    }
    free(test);
}

void unit_test_print_header(struct unit_test *test) {
    printf("\n======================================== %s "
        "Results ========================================\n\n", 
        test->name);

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
void unit_test_print_summary(struct unit_test *test) {    
    printf("\n\033[1;37m========== %s Summary ==========\033[0m\n", test->name);

    printf("\033[1;37mTotal Tests:%*d\033[0m\n", 
        19 + sizeof(test->name), test->num_passed + test->num_failed);
    
    printf("\033[1;37mTests Passed: \033[1;32m%*d\033[0m\n", 
        17 + sizeof(test->name), test->num_passed);
    
    printf("\033[1;37mTests Failed: \033[1;31m%*d\033[0m\n", 
        17 + sizeof(test->name), test->num_failed);
    
    float percentPassing = 100;
    
    if (test->num_failed > 0)
    {
        percentPassing = ((float) (test->num_passed) / 
            (float) (test->num_failed + test->num_passed)) * 100;
    }

    if (percentPassing >= 90) {
        printf("\033[1;37mPercent Passing: \033[1;32m%*.2f%%\033[0m\n", 
        13 + sizeof(test->name), percentPassing);
    }
    else if (percentPassing > 50) {
        printf("\033[1;37mPercent Passing: \033[1;33m%*.2f%%\033[0m\n", 
        13 + sizeof(test->name), percentPassing);
    }
    else {
        printf("\033[1;37mPercent Passing: \033[1;31m%*.2f%%\033[0m\n", 
        13 + sizeof(test->name), percentPassing);
    }
    
    printf("\033[1;37m");
    
    for (int i = 0; i < 31 + sizeof(test->name); i++)
    {
        printf("=");
    }
    
    printf("\033[0m\n");
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
void unit_test_assert_float_equals(struct unit_test *test, float a, float b) {
    printf("%d - \033[1;37m%s: \033[1;36mAssert Float Equals\033[0m between floats "
             "\033[0;36m%ff\033[0m and \033[0;36m%ff\033[0m:", 
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
void unit_test_assert_int_equals(struct unit_test *test, int a, int b) {
    printf("%d - \033[1;37m%s: \033[1;36mAssert Integer Equals\033[0m between integers "
             "\033[0;36m%d\033[0m and \033[0;36m%d\033[0m:", 
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
void unit_test_assert_double_equals(struct unit_test *test, double a, double b) {
    printf("%d - \033[1;37m%s: \033[1;36mAssert Double Equals\033[0m between doubles "
             "\033[0;36m%f\033[0m and \033[0;36m%f\033[0m:", 
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
void unit_test_assert_long_equals(struct unit_test *test, long a, long b) {
    printf("%d - \033[1;37m%s: \033[1;36mAssert Long Equals\033[0m between longs "
             "\033[0;36m%ldL\033[0m and \033[0;36m%ldL\033[0m:", 
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
void unit_test_assert_char_equals(struct unit_test *test, char a, char b) {
    printf("%d - \033[1;37m%s: \033[1;36mAssert Char Equals\033[0m between chars "
             "\033[0;36m'%c'\033[0m and \033[0;36m'%c'\033[0m:", 
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
