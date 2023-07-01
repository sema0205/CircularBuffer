#include <src/CircularBuffer.h>
#include <src/CircularBufferSpaceOptimized.h>

#include <gtest/gtest.h>
#include <sstream>


TEST(BufferTestSuite, ContainerRequirements) {

    // creates an empty container
    CircularBuffer<int> temp;
    ASSERT_EQ(temp.empty(), true);


    // creates a copy of temp1
    CircularBuffer<int> temp1(5);
    temp1.push_back(6);
    temp1.push_back(1);
    temp1.push_back(2);
    temp1.push_back(3);
    temp1.push_back(4);
    CircularBuffer<int> temp2(temp1);
    ASSERT_EQ(temp2[1], 6);
    ASSERT_EQ(temp2[2], 1);
    ASSERT_EQ(temp2[3], 2);
    ASSERT_EQ(temp2[4], 3);
    ASSERT_EQ(temp2[5], 4);

    // destroys or copy-assigns all elements of test1 from elements of test2
    CircularBuffer<int> test1;
    CircularBuffer<int> test2(5);
    test2.push_back(6);
    test2.push_back(52);
    test2.push_back(52);
    test2.push_back(234);
    test2.push_back(643);
    test2.push_back(65);
    test1 = test2;
    ASSERT_EQ(test2[0], 65);
    ASSERT_EQ(test2[2], 52);
    ASSERT_EQ(test2[3], 52);
    ASSERT_EQ(test2[4], 234);
    ASSERT_EQ(test2[5], 643);


    // 	convertible to bool
    CircularBuffer<int> conv1(3);
    conv1.push_back(42);
    conv1.push_back(42);
    conv1.push_back(42);
    conv1.push_back(42);
    CircularBuffer<int> conv2(3);
    conv2.push_back(42);
    conv2.push_back(62);
    conv2.push_back(235);
    conv2.push_back(42);
    ASSERT_EQ(conv1 == conv2, false);
    ASSERT_EQ(conv1 != conv2, true);

    // exchanges the values of a and b
    CircularBuffer<int> a(3);
    a.push_back(6);
    a.push_back(513);
    a.push_back(531);
    a.push_back(15);
    CircularBuffer<int> b(3);
    b.push_back(324);
    b.push_back(32);
    b.push_back(61);
    b.push_back(42);
    a.swap(b);
    ASSERT_EQ(b[2], 513);
    ASSERT_EQ(b[3], 531);
    ASSERT_EQ(b[0], 15);
    ASSERT_EQ(a[2], 32);
    ASSERT_EQ(a[3], 61);
    ASSERT_EQ(a[0], 42);


    // size check
    CircularBuffer<int> c(5);
    c.push_back(34);
    c.push_back(75);
    c.push_back(654);
    c.push_back(26);
    c.push_back(754);
    ASSERT_EQ(c.size(), std::distance(c.begin(), c.end()));

    // check for empty
    c.clear_buf();
    ASSERT_EQ(c.empty(), c.begin() == c.end());
}




TEST(BufferTestSuite, SequenceContainerRequirements) {

    // push_back circle test
    CircularBuffer<int> temp(5);
    temp.push_back(1);
    temp.push_back(2);
    temp.push_back(3);
    temp.push_back(4);
    temp.push_back(5);
    temp.push_back(6);
    temp.push_back(7);
    temp.push_back(8);
    ASSERT_EQ(temp[4], 4);
    ASSERT_EQ(temp[5], 5);
    ASSERT_EQ(temp[0], 6);
    ASSERT_EQ(temp[1], 7);
    ASSERT_EQ(temp[2], 8);
    ASSERT_EQ(temp.back(), 8);
    ASSERT_EQ(temp.front(), 4);

    // pop_front tests
    temp.pop_front();
    ASSERT_EQ(temp.front(), 5);
    temp.pop_front();
    temp.pop_front();
    temp.pop_front();
    temp.pop_front();
    ASSERT_EQ(temp.empty(), true);
}


TEST(BufferTestSuite, LegacyRandomAccessIteratorRequirements) {

    CircularBuffer<int> temp(6);
    temp.push_back(452);
    temp.push_back(75);
    temp.push_back(72);
    temp.push_back(24);
    temp.push_back(52);
    temp.push_back(542);
    temp.push_back(742);
    temp.push_back(534);
    temp.push_back(256);

    CircularBuffer<int>::iterator it1 = temp.begin();
    ASSERT_EQ(*it1, 24);
    ASSERT_EQ(it1[0], 24);
    it1 += 4;
    ASSERT_EQ(*it1, 534);
    it1++;
    ASSERT_EQ(*it1, 256);
    it1 -= 5;
    CircularBuffer<int>::iterator it2 = temp.end();
    ASSERT_EQ(it2 - it1, temp.size());
    ASSERT_EQ(it2 > it1, true);
    ASSERT_EQ(it2 != it1, true);
    CircularBuffer<int>::iterator it3 = it1;
    ASSERT_EQ(it3 >= it1, true);


    // two option to use for
    std::string test;
    for (const auto& el : temp) {
        test += std::to_string(el) + " ";
    }
    ASSERT_EQ(test, "24 52 542 742 534 256 ");

    test = "";
    for (auto it = temp.begin(); it != temp.end(); it++) {
        test += std::to_string(*it) + " ";
    }
    ASSERT_EQ(test, "24 52 542 742 534 256 ");

}



TEST(BufferTestSuite, CircularBufferSpaceOptimized) {

    // check for doubling size after adding in full container
    CircularBufferSpaceOptimized<int> temp(5);
    ASSERT_EQ(temp.max_size(), 5);
    ASSERT_EQ(temp.size(), 0);
    temp.push_back(1);
    temp.push_back(2);
    temp.push_back(3);
    temp.push_back(4);
    temp.push_back(5);
    ASSERT_EQ(temp.max_size(), 5);
    ASSERT_EQ(temp.size(), 5);
    temp.push_back(6);
    ASSERT_EQ(temp.max_size(), 10);
    ASSERT_EQ(temp.size(), 6);
    temp.push_back(7);
    temp.push_back(8);
    temp.push_back(9);
    temp.push_back(10);
    ASSERT_EQ(temp.max_size(), 10);
    ASSERT_EQ(temp.size(), 10);
    temp.push_back(11);
    ASSERT_EQ(temp.max_size(), 20);
    ASSERT_EQ(temp.size(), 11);
}



TEST(BufferTestSuite, STLFunctions) {


    // std::equal
    CircularBuffer<int> temp(5);
    temp.push_back(34);
    temp.push_back(25);
    temp.push_back(436);
    temp.push_back(23);
    temp.push_back(246);
    temp.push_back(23);
    temp.push_back(345);
    temp.push_back(26);
    temp.push_back(756);

    /* | 23 | 345 | 26 | 756 |  | 246 |
    //                         Ʌ    Ʌ
    //                         |    |
    //                        end  begin
    */

    CircularBuffer<int> temp2(5);
    temp2.push_back(34);
    temp2.push_back(25);
    temp2.push_back(436);
    temp2.push_back(23);
    temp2.push_back(246);
    temp2.push_back(23);
    temp2.push_back(345);
    temp2.push_back(26);
    temp2.push_back(646); // diff


    ASSERT_EQ(std::equal(temp.begin(), temp.end(), temp2.begin(), temp2.end()), false);
    temp2[3] = 756;
    ASSERT_EQ(std::equal(temp.begin(), temp.end(), temp2.begin(), temp2.end()), true);



    // std::distance with diff iterators positions
    ASSERT_EQ(std::distance(temp2.begin(), temp2.end()), 5);
    auto it1 = temp2.begin() + 2;
    auto it2 = temp2.end() - 1;
    ASSERT_EQ(std::distance(it1, it2), 2);
    it1 = temp2.begin();
    it2 = temp.end() - 3;
    ASSERT_EQ(std::distance(it1, it2), 2);

    // std::fill
    CircularBuffer<int> test3(5);
    test3.push_back(51);
    test3.push_back(31);
    test3.push_back(235);
    test3.push_back(35);
    test3.push_back(643);
    test3.push_back(1351);
    test3.push_back(5436);
    std::fill(test3.begin(), test3.end() - 2, 4);
    ASSERT_EQ(test3[0], 1351);
    ASSERT_EQ(test3[1], 5436);
    ASSERT_EQ(test3[3], 4);
    ASSERT_EQ(test3[4], 4);
    ASSERT_EQ(test3[5], 4);

    // std::find
    CircularBuffer<int>::iterator it5 = test3.end();
    auto it6 = std::find(test3.begin(), test3.end(), 5436);
    ASSERT_TRUE(it6 == it5);

}

TEST(BufferTestSuite, SortFunctions) {

    CircularBuffer<int> temp(5);
    temp.push_back(1);
    temp.push_back(2);
    temp.push_back(3);
    temp.push_back(5);
    temp.push_back(4);
    temp.push_back(8);
    temp.push_back(7);
    temp.push_back(6);

    /* | 8 | 7 | 6 |  | 5 | 4 |
    //              Ʌ   Ʌ
    //              |   |
    //            end  begin
    */

    std::sort(temp.begin(), temp.end());
    ASSERT_EQ(temp[4], 4);
    ASSERT_EQ(temp[5], 5);
    ASSERT_EQ(temp[0], 6);
    ASSERT_EQ(temp[1], 7);
    ASSERT_EQ(temp[2], 8);

    // with same numbers
    temp[4] = 2;
    temp[5] = 2;
    temp[0] = 1;
    temp[1] = 1;
    temp[2] = 8;

    std::sort(temp.begin(), temp.end());
    ASSERT_EQ(std::is_sorted(temp.begin(), temp.end()), true);
    ASSERT_EQ(temp[4], 1);
    ASSERT_EQ(temp[5], 1);
    ASSERT_EQ(temp[0], 2);
    ASSERT_EQ(temp[1], 2);
    ASSERT_EQ(temp[2], 8);
}
