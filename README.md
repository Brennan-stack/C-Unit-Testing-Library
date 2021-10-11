# <h1>C Unit Testing Library</h1>
![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)

The C Unit Testing Library on GitHub is a library designed for easy unit 
testing in C. It was written by Brennan Hurst for the purpose of providing
a J-Unit-like testing framework within C for personal projects.

The library features basic comparisons such as:
1. **AssertEquals:** which compares values to determine if they are equal.
2. **AssertArrayEquals:** which compares arrays to determine if they are equal. 
3. **AssertAddressEquals:** which compares addresses to determine if they are equal.
4. **AssertNull:** which determines if a value is null (still to be added). 
5. **AssertTrue:** which determines if a value is logically true (still to be added).
6. **AssertFalse:** which determines if a value is logically false (still to be added).
7. **AssertStructEquals:** which determines if two structs are equals (memory level, still to be added).

**This document is split up into a number of subsections to help with ease of use. Those are as follows:**
1. [Setting Up Inline Testing](#inline-testing): focused on testing code using assertions within the code itself. This is useful for debugging, but should not be done in a production testing environment. 
2. [Setting Up Unit Testing](#unit-testing): focused on use of a separate function for unit testing. This is the best way to use this library.
3. [Development](#development): discussion about the development of the unit testing library. 
4. [License](#license): the license this Git repository uses. 

If you have any additional questions not covered by this documentation, please reach out Brennan-Stack on GitHub. 

***
### Inline Testing
***
This section discusses how you can use this library to test code inline (that is, without the need for separate functions). This is particularly useful in situations where creating separate test functions may not be possible or you just want to test someting quickly without needing to create a new test function. **Note: This is not the proper way to use this repository, and it should be avoided if possible.**

<u>Getting Started</u>   
To get started with inline testing, all you have to do is import the module, create a new test, and begin executing assertions with that test. The best way to explain this is to show you an example:
```c
#include <unit_test.h>

/*
*   This is an example of executing unit tests inline.
*/
int main()
{
    int a = 0;
    int b = 0;
    //Here we create a new unit_test struct by calling unit_test_init(<name>);
    struct unit_test *test = unit_test_init("Example Inline Test");

    //we then print the header for the test, this is just to display the header
    unit_test_print_header(test);
    //we then execute some assertions inline
    unit_test_assert_int_equals(test, __FILE__, __LINE__, a, b);
    unit_test_assert_long_equals(test, __FILE__, __LINE__, 100L, 100L);
    //we then print the test summary 
    unit_test_print_summary(test);
}

```

And that's all you have to do to use inline tests. If you don't want to print the header, you don't have to.   
   
<u>Drawbacks to Inline Tests</u>  
There are a few drawbacks to inline tests. Specifically, they require printing of results as they run. Another drawback is they are directly in the code you are testing. This is good for quick tests, but would be a bad idea in production builds where you are trying to save space or keep code clean.   
   
Unit Testing fixes these issues by providing the ability for tests to be run separately from the code. 
***
### Unit Testing
***
Unit testing is the correct way to use this repository. It allows the programmer to create individual unit tests and to run them all under conditions of their choice. The best way to show how this works is with code:
```c
#include <unit_test.h>

/*
*   This is an example of a unit test. It is independent from the code which   
*   it executes and contains all of the unit tests. 
*/
int unit_test_1(struct unit_test *test)
{
    //create a dummy variable a
    int a = 0;
    //execute an assert_same_address on identical addresses &a and &a
    unit_test_assert_same_address(test, __FILE__, __LINE__, &a, &a);

    //create some dummy float arrays
    float floatarray1[2] = {0.0};
    float floatarray2[2] = {0.0};

    //execute an assert_float_array_equals on those arrays
    unit_test_assert_float_array_equals(test, __FILE__, __LINE__,
        floatarray1, sizeof(floatarray1), floatarray2, sizeof(floatarray2));
}

/*
*   This is an example of executing unit tests.
*/
int main()
{
    //here we create a new unit test struct using unit_test_init(<name>);
    struct unit_test *test = unit__test_init("Test Unit Tests");

    //here we call unit_test_start which starts the unit test
    unit_test_start(test, &unit_test_1, NULL);

    //we use unit_test_print_total_summary() to print a summary of all unit tests
    unit_test_print_total_summary();
}
```   
   
The above code does a few things in the main method. First, it creates a new unit_test which holds unit test information. It then starts the unit_test by calling unit_test_start(struct unit_test *test, void (*start)(), void (*print)()) which effectively handles the execution of the unit test pointed to by the function pointer *start and handles the print out of all assertions. The main then calls unit_test_print_total_summary() to print out an overall summary which shows results as a whole. 

### Development   
Development is currently being done by Brennan Hurst. This repository was initially created for the purpose of his personal use. Any contributions and/or suggestions related to this repository are more than welcome. 

### License   
This repository follows under the guidelines of the MIT License, as shown below:

>MIT License
>
>Copyright (c) 2021 Brennan-stack
>
>Permission is hereby granted, free of charge, to any person obtaining a copy
>of this software and associated documentation files (the "Software"), to deal
>in the Software without restriction, including without limitation the rights
>to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
>copies of the Software, and to permit persons to whom the Software is
>furnished to do so, subject to the following conditions:
>
>The above copyright notice and this permission notice shall be included in all
>copies or substantial portions of the Software.
>
>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
>IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
>FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
>AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
>LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
>OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
>SOFTWARE