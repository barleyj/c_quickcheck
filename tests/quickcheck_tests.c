#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <check.h>
#include "../inc/quickcheck.h"

int return_true(generic_type *throw_away) {
  return true;
}

int not_null(generic_type *type) {
  return *type != NULL;
}

int less_than_ten(generic_type *value) {
  int local_value = *((int *)value);

  return (local_value < 10);
}

void generate_null(generic_type *value) {
  *value = NULL;

  return;
}

void generate_int(generic_type *value) {
  *((int *)value) = rand();

  return;
}

void free_int(generic_type *value) {
  if(value) {
    free(value);
    *value = NULL;
  }

  return;
}

#define EXPAND_AS_TEST(name, body)				\
START_TEST(name)						\
{								\
  body								\
}								\
END_TEST

#define TESTS								\
EXPAND_AS_TEST(for_all_returns_true,					\
  int expected = true;							\
  int result = false;							\
									\
  result = for_all(&generate_null, &return_true, NULL);			\
									\
  ck_assert_int_eq(expected, result);					\
)									\
EXPAND_AS_TEST(for_all_not_null_returns_false,				\
  int expected = false;							\
  int result = true;							\
									\
  result = for_all(&generate_null, &not_null, NULL);			\
									\
  ck_assert_int_eq(expected, result);					\
)									\
EXPAND_AS_TEST(for_all_generator_returns_false,				\
  int expected = false;							\
  int result = true;							\
									\
  result = for_all(&generate_null, &not_null, NULL);			\
									\
  ck_assert_int_eq(expected, result);					\
)									\
EXPAND_AS_TEST(for_all_generate_int_less_than_ten_returns_false,	\
  int expected = false;							\
  int result = true;							\
									\
  result = for_all(&generate_int, &less_than_ten, NULL);		\
									\
  ck_assert_int_eq(expected, result);					\
)

TESTS
#undef EXPAND_AS_TEST

Suite *quickcheck_suite (void) {
  Suite *s = suite_create ("quickcheck");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
#define EXPAND_AS_TEST(name, body)  \
  tcase_add_test (tc_core, name);
  TESTS
#undef EXPAND_AS_TEST
  suite_add_tcase (s, tc_core);

  return s;
}

int main (void) {
  int number_failed;
  Suite *s = quickcheck_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}


