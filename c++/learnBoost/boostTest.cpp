
#define BOOST_TEST_MODULE MY TEST
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>

void test(int n)
{
  if (n == 42) {
    return;
  }
  throw std::runtime_error(
    "Not the answer");
}

BOOST_AUTO_TEST_CASE(my_test)
{
  BOOST_TEST_MESSAGE("Testing");
  BOOST_TEST(1 + 1 == 2);
  BOOST_CHECK_THROW(
    test(41), std::runtime_error);
  BOOST_CHECK_NO_THROW(test(42));

  int expected = 5;
  BOOST_TEST(2 + 2 == expected);
  BOOST_CHECK(2 + 2 == expected);
}

BOOST_AUTO_TEST_CASE(null_test)
{
}

BOOST_AUTO_TEST_CASE(first_test)
{
  int i = 1;
  BOOST_TEST(i);
  BOOST_TEST(i == 2);
}