#include "../src/unit_test.c"

void test_unit_test_start(struct unit_test *test)
{
    int a = 0;
    //test to see if addresses are equal
    unit_test_assert_same_address(test, __FILE__, __LINE__, &a, &a);
    unit_test_assert_int_equals(test, __FILE__, __LINE__, 1, 1);
    unit_test_assert_float_equals(test, __FILE__, __LINE__, 1.0f, 1.0f);
    unit_test_assert_double_equals(test, __FILE__, __LINE__, 1.0, 1.0);
    unit_test_assert_long_equals(test, __FILE__, __LINE__, 100L, 100L);
    unit_test_assert_char_equals(test, __FILE__, __LINE__, 'a', 'a');

}

void test_unit_test_arrays(struct unit_test *test)
{
    float floatarray1[2] = {0.0};
    float floatarray2[2] = {0.0};
    unit_test_assert_float_array_equals(test, __FILE__, __LINE__, floatarray1, sizeof(floatarray1), floatarray2, sizeof(floatarray2));
    
    int intarray1[2] = {0};
    int intarray2[2] = {0};
    unit_test_assert_int_array_equals(test, __FILE__, __LINE__, intarray1, sizeof(intarray1), intarray2, sizeof(intarray2));

    double doublearray1[2] = {0.0};
    double doublearray2[2] = {0.0};
    unit_test_assert_double_array_equals(test, __FILE__, __LINE__, doublearray1, sizeof(doublearray1), doublearray2, sizeof(doublearray2));

    long longarray1[2] = {0L};
    long longarray2[2] = {0L};
    unit_test_assert_long_array_equals(test, __FILE__, __LINE__, longarray1, sizeof(longarray1), longarray2, sizeof(longarray2));

    char chararray1[2] = {'a'};
    char chararray2[2] = {'a'};
    unit_test_assert_char_array_equals(test, __FILE__, __LINE__, chararray1, sizeof(chararray1), chararray2, sizeof(chararray2));
}

void test_unit_test_inline()
{
    int a = 1;
    int b = 1;
    struct unit_test *test2 = unit_test_init("Test Inline Unit Tests");
    unit_test_print_header(test2);
    unit_test_assert_int_equals(test2, __FILE__, __LINE__, a, b);
    unit_test_assert_long_equals(test2, __FILE__, __LINE__, 100L, 100L);
    unit_test_assert_long_equals(test2, __FILE__, __LINE__, 100L, 100L);
    unit_test_assert_long_equals(test2, __FILE__, __LINE__, 100L, 100L);
    unit_test_print_summary(test2);
}

int main()
{
    test_unit_test_inline();

    struct unit_test *test = unit_test_init("Test Unit Test Start");
    unit_test_start(test, &test_unit_test_start, NULL);

    struct unit_test *arraytest = unit_test_init("Test Unit Test Arrays");
    unit_test_start(arraytest, &test_unit_test_arrays, NULL);
    
    unit_test_print_total_summary();

}

