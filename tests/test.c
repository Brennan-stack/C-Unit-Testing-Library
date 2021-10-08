#include "../src/unit_test.c"

void unit_test_start_test(struct unit_test *test)
{
    int a = 0;
    int b = 2;
    //test to see if addresses are equal
    unit_test_assert_same_address(test, &a, &a);
    unit_test_assert_int_equals(test, 1, 1);
    unit_test_assert_float_equals(test, 1.0f, 1.0f);
    unit_test_assert_double_equals(test, 1.0, 1.0);
    unit_test_assert_long_equals(test, 100L, 100L);
    unit_test_assert_char_equals(test, 'a', 'a');

}

void unit_test_inline_test()
{
    int a = 1;
    int b = 1;
    struct unit_test *test2 = unit_test_init("Test 2");
    unit_test_print_header(test2);
    unit_test_assert_int_equals(test2, a, b);
    unit_test_print_summary(test2);
    unit_test_assert_long_equals(test2, 100L, 100L);
    unit_test_assert_long_equals(test2, 100L, 300L);
    unit_test_print_summary(test2);
    unit_test_assert_long_equals(test2, 100L, 300L);
    unit_test_print_summary(test2);

}

int main()
{
    struct unit_test *test = unit_test_init("Unit Test");
    unit_test_start(test, &unit_test_start_test, NULL);
    unit_test_inline_test();

}

