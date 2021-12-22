// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(list_empty) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST(list_empty_with_one_node) {
    List<int> empty_list;
    empty_list.push_back(3);
    ASSERT_FALSE(empty_list.empty());
}

TEST(list_size_adding) {
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.push_back(2002);
    ASSERT_EQUAL(3, not_empty.size());
}

TEST(list_size_removing) {
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.push_back(2002);

    not_empty.clear();
    ASSERT_EQUAL(0, not_empty.size());
}

TEST(list_size_empty) {
    List<int> empty_list;
    ASSERT_EQUAL(0, empty_list.size());
}

TEST(list_front) {
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.push_back(2002);

    ASSERT_EQUAL(2, not_empty.front());
}

TEST(list_back) {
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.push_back(2002);

    ASSERT_EQUAL(2002, not_empty.back());
}

// TEST(list_back_empty) {
//     List<int> empty_list;
//     ASSERT_EQUAL(nullptr, empty_list.back());
// }

// TEST(list_front_empty) {
//     List<int> empty_list;
//     ASSERT_EQUAL(nullptr, empty_list.front());
//}

TEST(list_push_front) {
    List<int> not_empty;
    not_empty.push_front(2);
    not_empty.push_front(12);
    not_empty.push_front(2002);

    ASSERT_EQUAL(2002, not_empty.front());
}

TEST(list_push_back) {
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.push_back(2002);

    ASSERT_EQUAL(2002, not_empty.back());
}

TEST(list_pop_front) {
    List<int> not_empty;
    not_empty.push_front(2);
    not_empty.push_front(12);
    not_empty.pop_front();

    ASSERT_EQUAL(2, not_empty.front());
}

TEST(list_pop_back) {
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.pop_back();

    ASSERT_EQUAL(2, not_empty.back());
}

TEST(list_pop_front_one){
    List<int> not_empty;
    not_empty.push_back(2);

    not_empty.pop_front();
    ASSERT_TRUE(not_empty.empty())
}

TEST(list_pop_back_one){
    List<int> not_empty;
    not_empty.push_back(2);
    
    not_empty.pop_back();
    ASSERT_TRUE(not_empty.empty())
}

TEST(list_clear) {
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.push_back(2002);

    not_empty.clear();
    ASSERT_TRUE(not_empty.empty());
}



TEST(iterator_erase_if_front) {
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.push_back(2002);

    List<int>::Iterator i = not_empty.begin();
    
    not_empty.erase(i);
    ASSERT_TRUE(not_empty.front() = 12);
    ASSERT_TRUE(not_empty.back() = 2002);
}

TEST(iterator_erase_if_back) {
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.push_back(2002);

    List<int>::Iterator i = not_empty.begin();
    
    ++++i;

    not_empty.erase(i);
    ASSERT_TRUE(not_empty.front() = 2);
    ASSERT_TRUE(not_empty.back() = 12);
}

TEST(iterator_erase_one_element) {
    List<int> not_empty;
    not_empty.push_back(2);

    List<int>::Iterator i = not_empty.begin();
    
    not_empty.erase(i);
    ASSERT_TRUE(not_empty.empty());
}

TEST(iterator_insert_if_front){
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.push_back(2002);

    List<int>::Iterator i = not_empty.begin();
    
    not_empty.insert(i, 24);
    ASSERT_TRUE(not_empty.front() = 21);
    ASSERT_TRUE(not_empty.back() = 2002);
}

TEST(iterator_insert_only_one){
    List<int> empty;

    List<int>::Iterator i = empty.begin();
    
    empty.insert(i, 24);
    ASSERT_TRUE(empty.front() = 24);
    ASSERT_TRUE(empty.back() = 24);
}

TEST(iterator_insert_if_back){
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.push_back(2002);

    List<int>::Iterator i = not_empty.end();
    
    not_empty.insert(i, 1999);
    ASSERT_TRUE(not_empty.front() = 2);
    ASSERT_TRUE(not_empty.back() = 1999);
}

TEST(iterator_erase_rando){
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.push_back(12);

    List<int>::Iterator i = not_empty.begin();
    
    not_empty.erase(++i);
    int numElements = 0;

    for (List<int>::Iterator j = not_empty.begin(); j != not_empty.end(); ++j){
        if(*j == 12){
            numElements +=1;
        }
    }

    ASSERT_EQUAL(1, numElements);

}

TEST(iterator_insert_rando){
    List<int> not_empty;
    not_empty.push_back(2);
    not_empty.push_back(12);
    not_empty.push_back(2002);
    not_empty.push_back(6);
    not_empty.push_back(9);
    not_empty.push_back(4);

    List<int>::Iterator i = not_empty.end();
    
    not_empty.insert(i, 1999);
    int numElements = 0;
    
    for (List<int>::Iterator j = not_empty.begin(); j != not_empty.end(); ++j){
        if(*j == 1999){
            numElements +=1;
        }
    }

    ASSERT_EQUAL(1, numElements);
}

TEST(equality_iterators){
    List<int> listy;
    listy.push_back(1);
    listy.push_back(2);

    List<int>::Iterator i = listy.begin();
    List<int>::Iterator j = listy.begin();

    ++i;

    ASSERT_TRUE(*i != *j);
    ASSERT_FALSE(*i == *j);

    --i;

    ASSERT_FALSE(*i != *j);
    ASSERT_TRUE(*i == *j);

}

TEST_MAIN()
