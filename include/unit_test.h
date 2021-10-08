#ifndef __UNIT_TEST_H
#define __UNIT_TEST_H
/*
*   This unit_test.h header file is responsible for defining the 
*   functions which will be implemented in unit_test.c. The purpose
*   of this file is to provide a unit test framework for c, which
*   I will make use of for various projects. 
*
*   To use this unit test file, follow the following instructions:
*
*   1. Initialize a new unit test:
*       struct unit_test* test1 = unit_test_init("test1");
*
*   2. define a void function where your tests will be held.
*       Make sure to add a parameter for struct unit_test.
*       This parameter is useful for all tests in this file.
*
*       void test1_test(struct unit_test *test) {
*       
*       }
*
*   3. Perform unit tests within this test function. 
*
*       void test1_test(struct unit_test *test) {
*           unit_test_assert_float_equals(test, 1.0f, 2.0f)
*       }
*
*   4. Call unit_test_start(test1, &test1_test, NULL) to execute
*       your unit test. 
*
*   Note: alternatively, you can use this library without the 
*   built in way of executing tests. You can define a new unit test
*   and execute the commands you wish to execute on that unit test
*   in any function. This is useful for inline testing, where executing
*   a separate function may not be possible. 
*
*   Enjoy!
*   @author Brennan Hurst
*   @version 10/07/2021
*/

/*
*   The unit_test struct is responsible for housing 
*   unit test information. 
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
struct unit_test {
    char* name;
    int num_passed;
    int num_failed;
};

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
struct unit_test* unit_test_init(char* name);

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
void unit_test_start(struct unit_test *test, void (*start)(), void (*print)());

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
void unit_test_assert_same_address(struct unit_test *test, void *a, void *b);

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
void unit_test_assert_float_equals(struct unit_test *test, float a, float b);

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
void unit_test_assert_int_equals(struct unit_test *test, int a, int b);

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
void unit_test_assert_double_equals(struct unit_test *test, double a, double b);

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
void unit_test_assert_long_equals(struct unit_test *test, long a, long b);

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
void unit_test_assert_char_equals(struct unit_test *test, char a, char b);

/*
*   This function takes a unit_test struct and prints out the results to 
*   standard output.
*
*   @param *test - the unit_test you wish to print out. 
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_print_summary(struct unit_test *test);

void unit_test_print_header(struct unit_test *test);
#endif