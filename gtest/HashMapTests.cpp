// HashMapTests.cpp
//
// ICS 45C Fall 2014
// Project #3: Maps and Legends
// Author: Alex Scott (68427591)
//
// Write unit tests for your HashMap class here.  I've provided one test already,
// though I've commented it out, because it won't compile until you've implemented
// three things: the HashMap constructor, the HashMap destructor, and HashMap's
// size() member function.

#include <gtest/gtest.h>
#include "HashMap.hpp"


TEST(TestHashMap, sizeOfNewlyCreatedHashMapIsZero)
{
   HashMap empty;
   ASSERT_EQ(0, empty.size());
}


TEST(TestHashMap, isRemovedValueStillInHashMap)
{
    HashMap hm1;
    std::string key1{"Alex"};
    std::string value1{"hunter2"};
    hm1.add(key1, value1);
    std::string key2{"Scott"};
    std::string value2{"*******"};
    hm1.add(key2, value2);
    hm1.remove(key1);
    ASSERT_FALSE(hm1.contains(key1));
    ASSERT_TRUE(hm1.contains(key2));
    hm1.remove(key2);
    ASSERT_FALSE(hm1.contains(key2));
}

TEST(TestHashMap, hashMapContainsAddedPairs)
{
    HashMap hm1;
    std::string key1{"Alex"};
    std::string value1{"hunter2"};
    hm1.add(key1, value1);
    std::string key2{"Scott"};
    std::string value2{"*******"};
    hm1.add(key2, value2);
    ASSERT_TRUE(hm1.contains(key1));
    ASSERT_TRUE(hm1.contains(key2));
}

TEST(TestHashMap, removeValueNotInHashMap)
{
    HashMap hm1;
    hm1.remove("testing testing");
}

TEST(TestHashMap, doesSizeUpdateAfterAddingOrRemovingValue)
{
    HashMap hm1;
    std::string key1 = "Danielle";
    std::string value1 = "this password";
    hm1.add("Superman manrepuS", "bird");
    hm1.add(key1, value1);
    ASSERT_EQ(2, hm1.size());
    hm1.add("What am I doing right now", "asd9991122##");
    ASSERT_EQ(3, hm1.size());
    hm1.remove("What am I doing right now");
    hm1.remove("Danielle");
    ASSERT_EQ(1, hm1.size());
}


TEST(TestHashMap, checkIfValueInTableAfterCleared)
{
    HashMap hm1;
    std::string key{"hi_world"};
    std::string value{"goodbye_world"};
    hm1.add(key, value);
    ASSERT_TRUE(hm1.contains(key));
    hm1.clearTable();
    ASSERT_FALSE(hm1.contains(key));
}

TEST(TestHashMap, clearEmptyTable)
{
    HashMap hm1;
    hm1.clearTable();
}

TEST(TestHashMap, valueOfKeyNotInHashMap)
{
    HashMap hm1;
    ASSERT_TRUE(hm1.value("Hello World.") == "");
    hm1.add("test1", "value1");
    HashMap hm2;
    hm2 = hm1;
    hm2.remove("test1");
    ASSERT_TRUE(hm2.value("test1") == "");
}

TEST(TestHashMap, copyConstructorCorrectlyCreatesNewMap)
{
    HashMap hm1;
    std::string key1 = "!!!";
    hm1.add(key1, "pass4445");
    hm1.add("UaasdffFF", "PasS!Wo@rDdddddddddddddddd");
    HashMap hm2{hm1};
    hm2.add("NOT IN hm1", ".");
    ASSERT_FALSE(hm1.contains("NOT IN hm1"));
    HashMap hm3 = hm2;
    hm3.remove(key1);
    ASSERT_TRUE(hm1.contains(key1));
    ASSERT_TRUE(hm2.contains(key1));
    ASSERT_FALSE(hm3.contains(key1));
}

TEST(TestHashMap, overloadOperatorCorrectlyOverridesNewMap)
{
    HashMap hm1;
    std::string key1 = "Test Username";
    hm1.add(key1, "password555");
    hm1.add("UserName2", "PasS!Wo@rDdddddddddddddddd");
    std::string value444211 = "nopasswordyesPasswordhiPassword";
    hm1.add("TEST_TEST_TEST3", value444211);
    HashMap hm2;
    std::string overloadKey{"This key is only here for now"};
    hm2.add(overloadKey, "values22");
    hm2 = hm1;
    ASSERT_FALSE(hm2.contains(overloadKey));
    hm2.add(overloadKey, "values34");
    hm2.remove(key1);
    hm1 = hm2;
    ASSERT_TRUE(hm1.contains(overloadKey));
    ASSERT_FALSE(hm1.contains(key1)); // removed key1 from hm2, assigned to hm1
}

/* Test the max bucket method */

namespace {
    // super simple hash function so we can easily predict where
    // certain keys will end up, making it easier to test maxBucketSize
    unsigned int easyHashFunc(const std::string& key) {
        unsigned int hashValue = 0;
        for(int i = 0; i < key.length(); i++) {
            int letterIndex = key.at(i);
            hashValue += letterIndex; // just add up the letters
         } // end for
        return hashValue;
    } // end easyHashFunc
}

TEST(TestHashMap, checkMaxBucketSize)
{
    HashMap hm1(easyHashFunc);
    std::string key1{"Alex"};
    std::string value1{"password1"};
    std::string key2{"xelA"};
    std::string value2{"password2"};
    std::string key3{"leAx"};
    std::string value3{"password3"};
    hm1.add(key1, value1);
    hm1.add(key2, value2);
    hm1.add(key3, value3);
    hm1.add("Unrelated1", "UnrelatedPassw0rd1");
    ASSERT_EQ(3, hm1.maxBucketSize());
}

TEST(TestHashMap, checkMaxBucketSizeWhenTwoBucketsAreEqual)
{
    HashMap hm1(easyHashFunc);
    std::string key1{"Alex"};
    std::string value1{"password1"};
    std::string key2{"xelA"};
    std::string value2{"password2"};
    hm1.add(key1, value1);
    hm1.add(key2, value2);
    hm1.add("Aley", "UnrelatedPassw0rd1");
    hm1.add("yelA", "pwwww");
    ASSERT_EQ(2, hm1.maxBucketSize());
}

/* Rehashed table tests */

namespace {

    void fillValues(HashMap& hm, int num) {
        static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        for(unsigned int i = 0; i < num; i++) {
            std::string key{alphanum[i], 'k'};
            std::string value{alphanum[i], 'v'};
            hm.add(key,value);
        }
    }

}

TEST(TestHashMap, ifLoadFactorEqualsMaxDoWeRehash)
{
    HashMap hm1;
    fillValues(hm1, 8);
    ASSERT_EQ(21, hm1.bucketCount());
}


TEST(TestHashMap, checkSizeIfHashTableReHashesDuringAdding)
{
    HashMap hm1;
    fillValues(hm1, 16);
    ASSERT_EQ(16, hm1.size());

}

TEST(TestHashMap, checkBucketAmountAfterRehashing)
{
    HashMap hm1;
    fillValues(hm1, 7);
    ASSERT_EQ(10, hm1.bucketCount());
    std::string rehashKey{"REHASH!"};
    std::string rehashValue{"VALUESS!"};
    hm1.add(rehashKey, rehashValue);
    ASSERT_EQ(21, hm1.bucketCount());
}

TEST(TestHashMap, assignReHashedTableIntoAnotherTable)
{
    HashMap hm1;
    fillValues(hm1, 9);
    HashMap hm2;
    hm2 = hm1;
    ASSERT_EQ(21, hm2.bucketCount());
    ASSERT_EQ(9, hm2.size());
}

TEST(TestHashMap, copyRehashedTableIntoAnotherTable)
{
    HashMap hm1;
    fillValues(hm1, 9);
    HashMap hm2 = hm1;
    ASSERT_EQ(21, hm2.bucketCount());
    ASSERT_EQ(9, hm2.size());
}

TEST(TestHashMap, addAfterRehash)
{
    HashMap hm1;
    fillValues(hm1, 9);
    hm1.add("afterHash", "afterPassword");
    ASSERT_TRUE(hm1.contains("afterHash"));
}

TEST(TestHashMap, removeAfterRehash)
{
    HashMap hm1;
    fillValues(hm1, 9);
    hm1.add("removeThis", "ornot");
    hm1.remove("removeThis");
    ASSERT_FALSE(hm1.contains("removeThis"));
}

