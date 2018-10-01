// HashMap_SanityCheckTests.cpp
//
// ICS 45C Fall 2014
// Project #3: Maps and Legends
// Author: Alex Scott (68427591)
//
// This is a set of "sanity checking" unit tests for your HashMap
// implementation, provided primarily as a mechanism for ensuring
// that your implementation is compatible with the unit tests that
// we'll be using to test your implementation during grading.  The
// goal here is to ensure that you have all of the necessary member
// functions, and that you haven't made changes that you shouldn't.
//
// All of the tests are initially commented out, because none of them
// links successfully.  (Interestingly, they all compile successfully,
// because HashMap.hpp declares all of the necessary member functions,
// but they will all result in link errors, since there are no
// implementations of any of HashMap's member functions until you
// write them.)
//
// As you implement member functions, you can start uncommenting unit
// tests -- and try to challenge yourself to understand which tests
// can be uncommented at which times, which is a useful exercise in
// learning more about how C++ compilers and linkers work, and what
// you can and can't do with partially-implemented classes.
//
// Note, too, that some of these tests attempt to do seemingly
// unnecessary things, like calling size() and then immediately
// incrementing it.  This is a simple mechanism to avoid compiler
// warnings about unused variables, while preserving the ability to
// declare those variables (and their types) to ensure that the
// return types of your member functions are correct.

#include <gtest/gtest.h>
#include <string>
#include "HashMap.hpp"


TEST(HashMap_SanityChecks, canConstructWithNoArguments)
{
   HashMap hm1;
}


TEST(HashMap_SanityChecks, canConstructWithLambdaExpression)
{
   HashMap hm1([](const std::string& s) { return 0; });
}


namespace
{
   unsigned int someHashFunction(const std::string& s)
   {
       return 19;
   }
}


TEST(HashMap_SanityChecks, canConstructWithFunction)
{
   HashMap hm1(someHashFunction);
}


namespace
{
   void foo(HashMap hm)
   {
   }
}


TEST(HashMap_SanityChecks, canCopyConstruct)
{
   HashMap hm1;
   HashMap hm2{hm1};
   HashMap hm3 = hm2;
   foo(hm1);
}


TEST(HashMap_SanityChecks, canAssign)
{
   HashMap hm1;
   HashMap hm2;
   hm1 = hm2;
}


TEST(HashMap_SanityChecks, canAddKeyValuePair)
{
   HashMap hm1;
   std::string key{"Boo"};
   std::string value{"perfect"};
   hm1.add(key, value);
}

TEST(HashMap_SanityChecks, canAddSameKeyValuePair)
{
    HashMap hm1;
    std::string key{"ding"};
    std::string value{"ding"};
    hm1.add(key,value);
}


TEST(HashMap_SanityChecks, canRemove)
{
   HashMap hm1;
   std::string key{"Alex"};
   hm1.remove(key);
}


TEST(HashMap_SanityChecks, canCheckIfContainsKey)
{
   HashMap hm1;
   std::string key{"Boo"};
   bool b = hm1.contains("Boo");
   b = !b;
}


TEST(HashMap_SanityChecks, canGetValueAssociatedWithKey)
{
   HashMap hm1;
   std::string key{"Boo"};
   std::string value = hm1.value(key);
}


TEST(HashMap_SanityCheckTests, canGetSize)
{
   HashMap hm1;
   unsigned int i = hm1.size();
   ++i;
}


TEST(HashMap_SanityCheckTests, canGetBucketCount)
{
   HashMap hm1;
   unsigned int b = hm1.bucketCount();
   ++b;
}


TEST(HashMap_SanityCheckTests, canGetLoadFactor)
{
   HashMap hm1;
   double lf = hm1.loadFactor();
   lf += 1.0;
}


TEST(HashMap_SanityCheckTests, canGetMaxBucketSize)
{
   HashMap hm1;
   unsigned int mbs = hm1.maxBucketSize();
   ++mbs;
}

