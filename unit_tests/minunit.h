/* file: minunit.h */
 #define mu_assert_when_true(message, test) do { if ((test)) return message; } while (0)
 #define mu_assert_when_false(message, test) do { if (!(test)) return message; } while (0)
 #define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
 extern int tests_run;

