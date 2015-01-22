/*
Author          : Alex Scott (ID: 68427591)
Description     : Project 3 - Maps and Legends
Class           : ICS45C Fall 2014
File            : UserAuthTests.cpp

Test the UserAuth class
*/
#include <gtest/gtest.h>
#include "UserAuth.hpp"

TEST(TestUserAuth, canConstructWithNoArguments)
{
   UserAuth ua;
}

/* USER-FACING MODE TESTS */

TEST(TestUserAuth, canCreateUser)
{
    UserAuth ua;
    std::string username{"Jeff"};
    std::string password{"hunter2"};
    ASSERT_TRUE(ua.createUser(username, password));
}

TEST(TestUserAuth, userAlreadyExists)
{
    UserAuth ua;
    std::string username{"Alex"};
    std::string password{"star*star*star*star"};
    ua.createUser(username, password);
    ASSERT_FALSE(ua.createUser(username, "AlexIsNotThatCommonOfaName"));
}

TEST(TestUserAuth, canNotLoginBecausePasswordIsNotValid)
{
    UserAuth ua;
    ua.createUser("user1", "pass1");
    ASSERT_FALSE(ua.login("user1", "pass5"));
}

TEST(TestUserAuth, canLoginWithCorrectPassword)
{
    UserAuth ua;
    ua.createUser("user1", "pass1");
    ASSERT_TRUE(ua.login("user1", "pass1"));
}

TEST(TestUserAuth, canLoginWithSpecialCharacterPassword)
{
    UserAuth ua;
    std::string user = "USER_HELLO_ONE";
    std::string password = "!@@*($&XUU#$*HBSR*e906879SUJUUUUU#WWFS";
    ua.createUser(user, password);
    ASSERT_TRUE(ua.login(user, password));
}

TEST(TestUserAuth, canRemoveUser)
{
    UserAuth ua;
    std::string user = "RemoveMe";
    std::string password = "IbetYouCant";
    ua.createUser(user, password);
    ASSERT_TRUE(ua.removeUser(user));
    ASSERT_FALSE(ua.login(user,password)); // should not be able to log in
}

TEST(TestUserAuth, canNotRemoveUser)
{
    UserAuth ua;
    std::string user{"Hi"};
    std::string password{"NotBye"};
    ua.createUser(user, password);
    ASSERT_TRUE(ua.userExists(user));
    ASSERT_FALSE(ua.removeUser("Bye"));
}

TEST(TestUserAuth, canClearAllData)
{
    UserAuth ua;
    std::string user{"IShouldntBeAlive"};
    std::string password{"AndAfterThisHopefullyImNot"};
    ua.createUser(user, password);
    ua.clearAll();
    // try to remove person who isn't there
    ASSERT_FALSE(ua.userExists(user));
}

TEST(TestUserAuth, clearWhenNoUsers)
{
    UserAuth ua;
    ua.clearAll();
}

TEST(TestUserAuth, clearThenAddUser)
{
    UserAuth ua;
    ua.createUser("GoodBye", "CruelWorld");
    ua.clearAll();
    ua.createUser("GoodBye", "CruelWorld");
    ASSERT_TRUE(ua.userExists("GoodBye"));
}

/* DEBUG MODE TESTS */

TEST(TestUserAuth, checkDebugOn)
{
    UserAuth ua;
    ua.debugOn();
    ASSERT_TRUE(ua.getDebugStatus());
}

TEST(TestUserAuth, checkDebugAlreadyOn)
{
    UserAuth ua;
    ua.debugOn();
    ua.debugOn();
}

TEST(TestUserAuth, checkDebugOff)
{
    UserAuth ua;
    ua.debugOn();
    ua.debugOff();
    ASSERT_FALSE(ua.getDebugStatus());
}

TEST(TestUserAuth, checkDebugAlreadyOff)
{
    UserAuth ua;
    ua.debugOff();
    ua.debugOff();
}

TEST(TestUserAuth, checkLoginCount)
{
    UserAuth ua;
    ua.createUser("Jim", "pw11");
    ASSERT_EQ(1, ua.loginCount());

}

TEST(TestUserAuth, checkLoginCountAfterClearingTable)
{
    UserAuth ua;
    ua.createUser("Jim", "pw11");
    ua.createUser("Flim", "zmadsfasdf");
    ua.createUser("hey!", "o_o");
    ua.clearAll();
    ua.createUser("United States of America", "#1");
    ASSERT_EQ(1, ua.loginCount());

}

TEST(TestUserAuth, checkLoginCountAfterRemoving)
{
    UserAuth ua;
    ua.createUser("Jim", "pw11");
    ua.createUser("Flim", "Dimm");
    ASSERT_EQ(2, ua.loginCount());
    ua.removeUser("Jim");
    ASSERT_EQ(1, ua.loginCount());
}

TEST(TestUserAuth, checkBucketCount)
{
    UserAuth ua;
    ua.getBucketCount();
}

TEST(TestUserAuth, checkLoadFactor)
{
    UserAuth ua;
    ua.createUser("hey0.1", "pw0.1");
    ASSERT_EQ(0.1, ua.getLoadFactor());
}

TEST(TestUserAuth, checkMaxBucketSize)
{
    UserAuth ua;
    ua.createUser("tester", "testerpw");
    ua.createUser("!!!!", "???????SSS");
    ua.createUser("!?!?!", "ffff");
    ua.getMaxBucketSize();
}
