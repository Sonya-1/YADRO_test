#include "Club.h"
#include "Club.cpp"
#include "TimeUtility.h"
#include "TimeUtility.cpp"
#include <gtest/gtest.h>

using namespace std;

TEST(TimeTest, time_formation) { 
    TimeUtility tu;
    int time = 581;
    ASSERT_EQ("09:41", tu.time_format(time));
}

TEST(ClubTest, client_in) { 
    Club cl; 
    client cl1 = client("client1");
    client cl2 = client("client2");
    cl.clients.push_back(cl1);
    cl.clients.push_back(cl2);   
    string s = "client2";
    
    ASSERT_EQ(true, cl.client_in_club(s));

}

TEST(ClubTest, client_find) { 
    Club cl; 
    client cl1 = client("client1");
    client cl2 = client("client2");
    cl.clients.push_back(cl1);
    cl.clients.push_back(cl2);    
    string s = "client3";
    
    ASSERT_EQ(NULL, cl.find_client(s));
}

TEST(ClubTest, client_remove) { 
    Club cl; 
    client cl1 = client("client1");
    client cl2 = client("client2");
    client cl3 = client("client3");
    cl.clients.push_back(cl1);
    cl.clients.push_back(cl2);
    cl.clients.push_back(cl3);    
    string s = "client2";
    cl.remove_client(cl.clients, s);
    
    ASSERT_EQ(2, cl.clients.size());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
