#include<stdio.h>
#include <stdlib.h>
#include "unit_tests/minunit.h"

int tests_run = 0;

/* Test using known good output for file unit_tests/a.tar */
static char *test_a_tar()
{
    mu_assert_when_true("Error, incorrect output for input file a.tar", 
               system("./tar_list ./unit_tests/a.tar | diff ./unit_tests/test1_output.txt -")); 
    return 0;
}

/* Test using known error for non-existent file b.tar  */
static char *test_b_tar()
{

    mu_assert_when_false("Error, incorrect output for input file b.tar", 
               system("./tar_list ./unit_tests/b.tar 2> diff ./unit_tests/test2_output.txt -")); 
    return 0;
}

/* Test using known good output + warning for file unit_tests/ccc.ddd */
static char *test_ccc_ddd()
{
    mu_assert_when_true("Error, incorrect output for input file ccc.ddd", 
               system("./tar_list ./unit_tests/ccc.ddd | diff ./unit_tests/test3_output.txt -")); 
    return 0;
}

static char *all_tests() 
{
    mu_run_test(test_a_tar);
    mu_run_test(test_b_tar);
    mu_run_test(test_ccc_ddd);
    return 0;
}

int main(int argc, char **argv)
{

    char * result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("All Tests Passed\n");
    }
    printf("Tests run: %d\n", tests_run);

    return (result != 0);

}

