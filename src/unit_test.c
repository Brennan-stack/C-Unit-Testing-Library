#include "../include/unit_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct unit_test **tests;
int test_count = 0;
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

    tests = realloc(tests, (test_count + 1) * sizeof(struct unit_test*));
    struct unit_test *u_test = calloc(1, sizeof(struct unit_test));
    //printf("%d\n", sizeof(tests));
    u_test->name = name;
    u_test->num_passed = 0;
    u_test->num_failed = 0;
    tests[test_count] = u_test;
    test_count++;
    return u_test;
}

/*
*   This function prints a total summary of all unit test which have executed.
*   It also reports to the user whether the program is passing as a whole, and 
*   must be called by the user.
*
*   @author Brennan Hurst
*   @version 10/10/2021
*/
void unit_test_print_total_summary() {
    
    printf("\033[1;37m================== Total Summary ==================\033[0m\n");
    printf("\033[4mTest Name|                                   |Score\033[0m\n");
    int total_passing = 0;
    int total_failing = 0;
    for (int i = 0; i < test_count; i++)
    {
        int size = 0;
        for(; tests[i]->name[size] != '\0'; size++);
        printf("%s: %*d/%d\n", tests[i]->name, 47 - size, tests[i]->num_passed,
            tests[i]->num_failed + tests[i]->num_passed);
        total_passing += tests[i]->num_passed;
        total_failing += tests[i]->num_failed;
    }
    printf("---------------------------------------------------\n");
    printf("# of Assertions Passing: \033[1;32m%*d\033[0m\n", 26, total_passing);
    printf("# of Assertions Failing: \033[1;31m%*d\033[0m\n", 26, total_failing);
    printf("Overall Status: ");

    if (total_failing == 0)
    {
        printf("\033[1;32m%*s\033[0m\n", 35, "PASSING");
    }
    else
    {
        printf("\033[1;31m%*s\033[0m\n", 28, "FAILING");
    }
    printf("===================================================\n");

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
    //free(test);
}

/*
*   This function prints the header for the unit test section. It is used as 
*   a helper function and may be useful for inline printing. 
*
*   @param *test - the unit_test you wish to print out.
*
*   @author Brennan Hurst
*   @version 10/09/2021
*/
void unit_test_print_header(struct unit_test *test) {
    assert(test != NULL);
    printf("======================================== %s "
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
    assert(test != NULL);    
    int size = 0;
    for (; test->name[size + 1] != '\0'; size++);
    printf("\n\033[1;37m========== %s Summary ==========\033[0m\n", test->name);

    printf("\033[1;37mTotal Tests:%*d\033[0m\n", 
        19 + size, test->num_passed + test->num_failed);
    
    printf("\033[1;37mTests Passed: \033[1;32m%*d\033[0m\n", 
        17 + size, test->num_passed);
    
    printf("\033[1;37mTests Failed: \033[1;31m%*d\033[0m\n", 
        17 + size, test->num_failed);
    
    float percentPassing = 100;
    
    if (test->num_failed > 0)
    {
        percentPassing = ((float) (test->num_passed) / 
            (float) (test->num_failed + test->num_passed)) * 100;
    }

    if (percentPassing >= 90) {
        printf("\033[1;37mPercent Passing: \033[1;32m%*.2f%%\033[0m\n", 
        13 + size, percentPassing);
    }
    else if (percentPassing > 50) {
        printf("\033[1;37mPercent Passing: \033[1;33m%*.2f%%\033[0m\n", 
        13 + size, percentPassing);
    }
    else {
        printf("\033[1;37mPercent Passing: \033[1;31m%*.2f%%\033[0m\n", 
        13 + size, percentPassing);
    }
    
    printf("\033[1;37m");
    
    for (int i = 0; i < 31 + size; i++)
    {
        printf("=");
    }
    
    printf("\033[0m\n\n");
}

/*
*   This function takes two pointers and tests if they point to the same memory
*   address. 
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param *a - the first pointer you are comparing
*   @param *b - the second pointer you are comparing
*   @param *fname - file name. Use the macro __FILE_ for this field.
*   @param lineno - line number. Use the macro __LINE__ for this field.
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_assert_same_address(struct unit_test *test, const char *fname, int lineno, void *a, void *b) {
    assert(test != NULL);
    assert(fname != NULL);
    assert(a != NULL);
    assert(b != NULL);
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
        printf("\n\t\033[1;37mExpanded Information:\n");
        printf("\t\033[1;36mAssert Same Address \033[1;31mFailed\033[0m"
            " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
        printf("\tAssertion expected \033[1;31m0x%p\033[0m but got \033[1;31m0x%p\033[0m.\n", a, b);
        printf("\n\033[0m");
    }
    
}

/*
*   This function takes two floats and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first float you are comparing
*   @param b - the second float you are comparing
*   @param *fname - file name. Use the macro __FILE_ for this field.
*   @param lineno - line number. Use the macro __LINE__ for this field.
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_assert_float_equals(struct unit_test *test, const char *fname, int lineno, float a, float b) {
    assert(test != NULL);
    assert(fname != NULL);
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
        printf("\n\t\033[1;37mExpanded Information:\n");
        printf("\t\033[1;36mAssert Float Equals \033[1;31mFailed\033[0m"
            " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
        printf("\tAssertion expected \033[1;31m%ff\033[0m but got \033[1;31m%ff\033[0m.\n", a, b);
        printf("\n\033[0m");
    }
}

/*
*   This function takes two integers and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first integers you are comparing
*   @param b - the second integers you are comparing
*   @param *fname - file name. Use the macro __FILE_ for this field.
*   @param lineno - line number. Use the macro __LINE__ for this field.
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_assert_int_equals(struct unit_test *test, const char *fname, int lineno, int a, int b) {
    assert(test != NULL);
    assert(fname != NULL);
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
        printf("\n\t\033[1;37mExpanded Information:\n");
        printf("\t\033[1;36mAssert Integer Equals \033[1;31mFailed\033[0m"
            " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
        printf("\tAssertion expected \033[1;31m%d\033[0m but got \033[1;31m%d\033[0m.\n", a, b);
        printf("\n\033[0m");
    }
}

/*
*   This function takes two doubles and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first doubles you are comparing
*   @param b - the second doubles you are comparing
*   @param *fname - file name. Use the macro __FILE_ for this field.
*   @param lineno - line number. Use the macro __LINE__ for this field.
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_assert_double_equals(struct unit_test *test, const char *fname, int lineno, double a, double b) {
    assert(test != NULL);
    assert(fname != NULL);
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
        printf("\n\t\033[1;37mExpanded Information:\n");
        printf("\t\033[1;36mAssert Double Equals \033[1;31mFailed\033[0m"
            " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
        printf("\tAssertion expected \033[1;31m%f\033[0m but got \033[1;31m%f\033[0m.\n", a, b);
        printf("\n\033[0m");
    }    
}

/*
*   This function takes two longs and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first long you are comparing
*   @param b - the second long you are comparing
*   @param *fname - file name. Use the macro __FILE_ for this field.
*   @param lineno - line number. Use the macro __LINE__ for this field.
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_assert_long_equals(struct unit_test *test, const char *fname, int lineno, long a, long b) {
    assert(test != NULL);
    assert(fname != NULL);
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
        printf("\n\t\033[1;37mExpanded Information:\n");
        printf("\t\033[1;36mAssert Long Equals \033[1;31mFailed\033[0m"
            " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
        printf("\tAssertion expected \033[1;31m%ldL\033[0m but got \033[1;31m%ldL\033[0m.\n", a, b);
        printf("\n\033[0m");
    }      
}

/*
*   This function takes two chars and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first char you are comparing
*   @param b - the second char you are comparing
*   @param *fname - file name. Use the macro __FILE_ for this field.
*   @param lineno - line number. Use the macro __LINE__ for this field.
*
*   @author Brennan Hurst
*   @version 10/07/2021
*/
void unit_test_assert_char_equals(struct unit_test *test, const char *fname, int lineno, char a, char b) {
    assert(test != NULL);
    assert(fname != NULL);
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
        printf("\n\t\033[1;37mExpanded Information:\n");
        printf("\t\033[1;36mAssert Char Equals \033[1;31mFailed\033[0m"
            " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
        printf("\tAssertion expected \033[1;31m'%c'\033[0m but got \033[1;31m'%c'\033[0m.\n", a, b);
        printf("\n\033[0m");
    }    
}

/*
*   This function takes two floats and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first float array are comparing
*   @param b - the second float array are comparing
*   @param *fname - file name. Use the macro __FILE_ for this field.
*   @param lineno - line number. Use the macro __LINE__ for this field.
*   @param asize - the size of array a.
*   @param bsize - the size of array b.
*
*   @author Brennan Hurst
*   @version 10/09/2021
*/
void unit_test_assert_float_array_equals(struct unit_test *test, const char *fname, int lineno, float *a, int asize, float *b, int bsize) {
    assert(a != NULL);
    assert(b != NULL);
    assert(test != NULL);
    assert(fname != NULL);

    printf("%d - \033[1;37m%s: \033[1;36mAssert Float Array Equals\033[0m:", 
             test->num_passed + test->num_failed, test->name);
    if (asize == bsize) {
        int i = 0;
        for (; i < asize/sizeof(a[0]); i++)
        {
            if (a[i] != b[i]) break;
        }
        if (i == (asize/sizeof(a[0])))
        {
            test->num_passed++;
            printf(" \033[1;32mPASSED\n\033[0m");
        }
        else
        {
            test->num_failed++;
            printf(" \033[1;31mFAILED\n\033[0m");
            printf("\n\t\033[1;37mExpanded Information:\n");
            printf("\t\033[1;36mAssert Float Array Equals \033[1;31mFailed\033[0m"
                " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
            printf("\tAssertion expected:\n");
            printf("\t\033[1;32m[");
            for (int j = 0; j < asize/sizeof(a[0]); j++)
            {
                printf("%ff", a[j]);
                if (j < asize/sizeof(a[0]) - 1)
                {
                    printf(", ");
                }
                else
                {
                    printf("]\n\033[0m");
                }
            }
            printf("\tbut got:\n");
            printf("\t\033[1;32m[");
            for (int j = 0; j < bsize/sizeof(b[0]); j++)
            {
                if (j == i)
                {
                   printf("\033[1;31m%ff\033[0m", b[j]); 
                }
                else
                {
                    printf("\033[1;32m%ff", b[j]);
                }
                if (j < bsize/sizeof(b[0]) - 1)
                {
                    printf(", ");
                }
                else
                {
                    printf("]\n\033[0m");
                }
            }
            printf("\n\033[0m");
        }
    }
    else
    {
        test->num_failed++;
        printf(" \033[1;31mFAILED\n\033[0m");
        printf("\n\t\033[1;37mExpanded Information:\n");
        printf("\t\033[1;36mAssert Float Array Equals \033[1;31mFailed\033[0m"
            " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
        printf("\n\t\033[1;31mFloat arrays are of uneven length.\033[0m\n\n");
        printf("\tAssertion expected:\n");
        printf("\t\033[1;32m[");
        for (int j = 0; j < asize/sizeof(a[0]); j++)
        {
            printf("%ff", a[j]);
            if (j < asize/sizeof(a[0]) - 1)
            {
                printf(", ");
            }
            else
            {
                printf("] (Array Length: %d)\n\033[0m", asize/sizeof(a[0]));
            }
        }
        printf("\tbut got:\n");
        printf("\t\033\033[1;31m[");
        for (int j = 0; j < bsize/sizeof(b[0]); j++)
        {
            printf("%ff", b[j]);
            
            if (j < bsize/sizeof(b[0]) - 1)
            {
                printf(", ");
            }
            else
            {
                printf("] \033[1;31m(Array Length: %d)\n\033[0m", bsize/sizeof(b[0]));
            }
        }
        printf("\n\033[0m");
        
    }    
}

/*
*   This function takes two integers and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first integer array you are comparing
*   @param b - the second integer array you are comparing
*   @param *fname - file name. Use the macro __FILE_ for this field.
*   @param lineno - line number. Use the macro __LINE__ for this field.
*   @param asize - the size of array a.
*   @param bsize - the size of array b.
*   @author Brennan Hurst
*   @version 10/09/2021
*/
void unit_test_assert_int_array_equals(struct unit_test *test, const char *fname, int lineno, int *a, int asize, int *b, int bsize) {
    assert(a != NULL);
    assert(b != NULL);
    assert(test != NULL);
    assert(fname != NULL);

    printf("%d - \033[1;37m%s: \033[1;36mAssert Integer Array Equals\033[0m:", 
             test->num_passed + test->num_failed, test->name);
    if (asize == bsize) {
        int i = 0;
        for (; i < asize/sizeof(a[0]); i++)
        {
            if (a[i] != b[i]) break;
        }
        if (i == (asize/sizeof(a[0])))
        {
            test->num_passed++;
            printf(" \033[1;32mPASSED\n\033[0m");
        }
        else
        {
            test->num_failed++;
            printf(" \033[1;31mFAILED\n\033[0m");
            printf("\n\t\033[1;37mExpanded Information:\n");
            printf("\t\033[1;36mAssert Integer Array Equals \033[1;31mFailed\033[0m"
                " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
            printf("\tAssertion expected:\n");
            printf("\t\033[1;32m[");
            for (int j = 0; j < asize/sizeof(a[0]); j++)
            {
                printf("%d", a[j]);
                if (j < asize/sizeof(a[0]) - 1)
                {
                    printf(", ");
                }
                else
                {
                    printf("]\n\033[0m");
                }
            }
            printf("\tbut got:\n");
            printf("\t\033[1;32m[");
            for (int j = 0; j < bsize/sizeof(b[0]); j++)
            {
                if (j == i)
                {
                   printf("\033[1;31m%d\033[0m", b[j]); 
                }
                else
                {
                    printf("\033[1;32m%d", b[j]);
                }
                if (j < bsize/sizeof(b[0]) - 1)
                {
                    printf(", ");
                }
                else
                {
                    printf("]\n\033[0m");
                }
            }
            printf("\n\033[0m");
        }
    }
    else
    {
        test->num_failed++;
        printf(" \033[1;31mFAILED\n\033[0m");
        printf("\n\t\033[1;37mExpanded Information:\n");
        printf("\t\033[1;36mAssert Integer Array Equals \033[1;31mFailed\033[0m"
            " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
        printf("\n\t\033[1;31mInteger arrays are of uneven length.\033[0m\n\n");
        printf("\tAssertion expected:\n");
        printf("\t\033[1;32m[");
        for (int j = 0; j < asize/sizeof(a[0]); j++)
        {
            printf("%d", a[j]);
            if (j < asize/sizeof(a[0]) - 1)
            {
                printf(", ");
            }
            else
            {
                printf("] (Array Length: %d)\n\033[0m", asize/sizeof(a[0]));
            }
        }
        printf("\tbut got:\n");
        printf("\t\033\033[1;31m[");
        for (int j = 0; j < bsize/sizeof(b[0]); j++)
        {
            printf("%d", b[j]);
            
            if (j < bsize/sizeof(b[0]) - 1)
            {
                printf(", ");
            }
            else
            {
                printf("] \033[1;31m(Array Length: %d)\n\033[0m", bsize/sizeof(b[0]));
            }
        }
        printf("\n\033[0m");
        
    }    
}

/*
*   This function takes two doubles and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first double array you are comparing
*   @param b - the second double array you are comparing
*   @param *fname - file name. Use the macro __FILE_ for this field.
*   @param lineno - line number. Use the macro __LINE__ for this field.
*   @param asize - the size of array a.
*   @param bsize - the size of array b.
*
*   @author Brennan Hurst
*   @version 10/09/2021
*/
void unit_test_assert_double_array_equals(struct unit_test *test, const char *fname, int lineno, double *a, int asize, double *b, int bsize) {
    assert(a != NULL);
    assert(b != NULL);
    assert(test != NULL);
    assert(fname != NULL);

    printf("%d - \033[1;37m%s: \033[1;36mAssert Double Array Equals\033[0m:", 
             test->num_passed + test->num_failed, test->name);
    if (asize == bsize) {
        int i = 0;
        for (; i < asize/sizeof(a[0]); i++)
        {
            if (a[i] != b[i]) break;
        }
        if (i == (asize/sizeof(a[0])))
        {
            test->num_passed++;
            printf(" \033[1;32mPASSED\n\033[0m");
        }
        else
        {
            test->num_failed++;
            printf(" \033[1;31mFAILED\n\033[0m");
            printf("\n\t\033[1;37mExpanded Information:\n");
            printf("\t\033[1;36mAssert Double Array Equals \033[1;31mFailed\033[0m"
                " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
            printf("\tAssertion expected:\n");
            printf("\t\033[1;32m[");
            for (int j = 0; j < asize/sizeof(a[0]); j++)
            {
                printf("%f", a[j]);
                if (j < asize/sizeof(a[0]) - 1)
                {
                    printf(", ");
                }
                else
                {
                    printf("]\n\033[0m");
                }
            }
            printf("\tbut got:\n");
            printf("\t\033[1;32m[");
            for (int j = 0; j < bsize/sizeof(b[0]); j++)
            {
                if (j == i)
                {
                   printf("\033[1;31m%f\033[0m", b[j]); 
                }
                else
                {
                    printf("\033[1;32m%f", b[j]);
                }
                if (j < bsize/sizeof(b[0]) - 1)
                {
                    printf(", ");
                }
                else
                {
                    printf("]\n\033[0m");
                }
            }
            printf("\n\033[0m");
        }
    }
    else
    {
        test->num_failed++;
        printf(" \033[1;31mFAILED\n\033[0m");
        printf("\n\t\033[1;37mExpanded Information:\n");
        printf("\t\033[1;36mAssert Double Array Equals \033[1;31mFailed\033[0m"
            " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
        printf("\n\t\033[1;31mDouble arrays are of uneven length.\033[0m\n\n");
        printf("\tAssertion expected:\n");
        printf("\t\033[1;32m[");
        for (int j = 0; j < asize/sizeof(a[0]); j++)
        {
            printf("%f", a[j]);
            if (j < asize/sizeof(a[0]) - 1)
            {
                printf(", ");
            }
            else
            {
                printf("] (Array Length: %d)\n\033[0m", asize/sizeof(a[0]));
            }
        }
        printf("\tbut got:\n");
        printf("\t\033\033[1;31m[");
        for (int j = 0; j < bsize/sizeof(b[0]); j++)
        {
            printf("%f", b[j]);
            
            if (j < bsize/sizeof(b[0]) - 1)
            {
                printf(", ");
            }
            else
            {
                printf("] \033[1;31m(Array Length: %d)\n\033[0m", bsize/sizeof(b[0]));
            }
        }
        printf("\n\033[0m");
        
    }    
}

/*
*   This function takes two longs and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first long array you are comparing
*   @param b - the second long array you are comparing
*   @param *fname - file name. Use the macro __FILE_ for this field.
*   @param lineno - line number. Use the macro __LINE__ for this field.
*   @param asize - the size of array a.
*   @param bsize - the size of array b.
*
*   @author Brennan Hurst
*   @version 10/09/2021
*/
void unit_test_assert_long_array_equals(struct unit_test *test, const char *fname, int lineno, long *a, int asize, long *b, int bsize) {
    assert(a != NULL);
    assert(b != NULL);
    assert(test != NULL);
    assert(fname != NULL);

    printf("%d - \033[1;37m%s: \033[1;36mAssert Long Array Equals\033[0m:", 
             test->num_passed + test->num_failed, test->name);
    if (asize == bsize) {
        int i = 0;
        for (; i < asize/sizeof(a[0]); i++)
        {
            if (a[i] != b[i]) break;
        }
        if (i == (asize/sizeof(a[0])))
        {
            test->num_passed++;
            printf(" \033[1;32mPASSED\n\033[0m");
        }
        else
        {
            test->num_failed++;
            printf(" \033[1;31mFAILED\n\033[0m");
            printf("\n\t\033[1;37mExpanded Information:\n");
            printf("\t\033[1;36mAssert Long Array Equals \033[1;31mFailed\033[0m"
                " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
            printf("\tAssertion expected:\n");
            printf("\t\033[1;32m[");
            for (int j = 0; j < asize/sizeof(a[0]); j++)
            {
                printf("%ldL", a[j]);
                if (j < asize/sizeof(a[0]) - 1)
                {
                    printf(", ");
                }
                else
                {
                    printf("]\n\033[0m");
                }
            }
            printf("\tbut got:\n");
            printf("\t\033[1;32m[");
            for (int j = 0; j < bsize/sizeof(b[0]); j++)
            {
                if (j == i)
                {
                   printf("\033[1;31m%ldL\033[0m", b[j]); 
                }
                else
                {
                    printf("\033[1;32m%ldL", b[j]);
                }
                if (j < bsize/sizeof(b[0]) - 1)
                {
                    printf(", ");
                }
                else
                {
                    printf("]\n\033[0m");
                }
            }
            printf("\n\033[0m");
        }
    }
    else
    {
        test->num_failed++;
        printf(" \033[1;31mFAILED\n\033[0m");
        printf("\n\t\033[1;37mExpanded Information:\n");
        printf("\t\033[1;36mAssert Long Array Equals \033[1;31mFailed\033[0m"
            " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
        printf("\n\t\033[1;31mLong arrays are of uneven length.\033[0m\n\n");
        printf("\tAssertion expected:\n");
        printf("\t\033[1;32m[");
        for (int j = 0; j < asize/sizeof(a[0]); j++)
        {
            printf("%ldL", a[j]);
            if (j < asize/sizeof(a[0]) - 1)
            {
                printf(", ");
            }
            else
            {
                printf("] (Array Length: %d)\n\033[0m", asize/sizeof(a[0]));
            }
        }
        printf("\tbut got:\n");
        printf("\t\033\033[1;31m[");
        for (int j = 0; j < bsize/sizeof(b[0]); j++)
        {
            printf("%ldL", b[j]);
            
            if (j < bsize/sizeof(b[0]) - 1)
            {
                printf(", ");
            }
            else
            {
                printf("] \033[1;31m(Array Length: %d)\n\033[0m", bsize/sizeof(b[0]));
            }
        }
        printf("\n\033[0m");
        
    }    
}

/*
*   This function takes two chars and determines if they both contain the same
*   value.
*
*   @param *test - the unit_test you wish to use to track the results. 
*   @param a - the first char array you are comparing
*   @param b - the second char array you are comparing
*   @param *fname - file name. Use the macro __FILE_ for this field.
*   @param lineno - line number. Use the macro __LINE__ for this field.
*   @param asize - the size of array a.
*   @param bsize - the size of array b.
*
*   @author Brennan Hurst
*   @version 10/09/2021
*/
void unit_test_assert_char_array_equals(struct unit_test *test, const char *fname, int lineno, char *a, int asize, char *b, int bsize) {
    assert(a != NULL);
    assert(b != NULL);
    assert(test != NULL);
    assert(fname != NULL);

    printf("%d - \033[1;37m%s: \033[1;36mAssert Char Array Equals\033[0m:", 
             test->num_passed + test->num_failed, test->name);
    if (asize == bsize) {
        int i = 0;
        for (; i < asize/sizeof(a[0]); i++)
        {
            if (a[i] != b[i]) break;
        }
        if (i == (asize/sizeof(a[0])))
        {
            test->num_passed++;
            printf(" \033[1;32mPASSED\n\033[0m");
        }
        else
        {
            test->num_failed++;
            printf(" \033[1;31mFAILED\n\033[0m");
            printf("\n\t\033[1;37mExpanded Information:\n");
            printf("\t\033[1;36mAssert Char Array Equals \033[1;31mFailed\033[0m"
                " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
            printf("\tAssertion expected:\n");
            printf("\t\033[1;32m[");
            for (int j = 0; j < asize/sizeof(a[0]); j++)
            {
                printf("'%c'", a[j]);
                if (j < asize/sizeof(a[0]) - 1)
                {
                    printf(", ");
                }
                else
                {
                    printf("]\n\033[0m");
                }
            }
            printf("\tbut got:\n");
            printf("\t\033[1;32m[");
            for (int j = 0; j < bsize/sizeof(b[0]); j++)
            {
                if (j == i)
                {
                   printf("\033[1;31m'%c'\033[0m", b[j]); 
                }
                else
                {
                    printf("\033[1;32m'%c'", b[j]);
                }
                if (j < bsize/sizeof(b[0]) - 1)
                {
                    printf(", ");
                }
                else
                {
                    printf("]\n\033[0m");
                }
            }
            printf("\n\033[0m");
        }
    }
    else
    {
        test->num_failed++;
        printf(" \033[1;31mFAILED\n\033[0m");
        printf("\n\t\033[1;37mExpanded Information:\n");
        printf("\t\033[1;36mAssert Char Array Equals \033[1;31mFailed\033[0m"
            " in file \033[1;31m%s\033[0m at line \033[1;31m%d\033[0m.\n", fname, lineno);
        printf("\n\t\033[1;31mChar arrays are of uneven length.\033[0m\n\n");
        printf("\tAssertion expected:\n");
        printf("\t\033[1;32m[");
        for (int j = 0; j < asize/sizeof(a[0]); j++)
        {
            printf("'%c'", a[j]);
            if (j < asize/sizeof(a[0]) - 1)
            {
                printf(", ");
            }
            else
            {
                printf("] (Array Length: %d)\n\033[0m", asize/sizeof(a[0]));
            }
        }
        printf("\tbut got:\n");
        printf("\t\033\033[1;31m[");
        for (int j = 0; j < bsize/sizeof(b[0]); j++)
        {
            printf("'%c'", b[j]);
            
            if (j < bsize/sizeof(b[0]) - 1)
            {
                printf(", ");
            }
            else
            {
                printf("] \033[1;31m(Array Length: %d)\n\033[0m", bsize/sizeof(b[0]));
            }
        }
        printf("\n\033[0m");
        
    }    
}
