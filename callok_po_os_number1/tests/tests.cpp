#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

std::vector<unsigned long long> factorials(int n);
std::vector<int> removeDuplicates(const std::vector<int>& input);
struct ListNode;
ListNode* reverseList(ListNode* head);

TEST(FactorialTest, PositiveInput) {
    EXPECT_EQ(factorials(1), (std::vector<unsigned long long>{1}));
    EXPECT_EQ(factorials(2), (std::vector<unsigned long long>{1, 2}));
    EXPECT_EQ(factorials(3), (std::vector<unsigned long long>{1, 2, 6}));
    EXPECT_EQ(factorials(5), (std::vector<unsigned long long>{1, 2, 6, 24, 120}));
}

TEST(FactorialTest, ZeroInput) {
    EXPECT_THROW(factorials(0), std::invalid_argument);
}

TEST(FactorialTest, NegativeInput) {
    EXPECT_THROW(factorials(-5), std::invalid_argument);
}

TEST(RemoveDuplicatesTest, BasicTests) {
    EXPECT_EQ(removeDuplicates({1, 2, 2, 3}), (std::vector<int>{1, 2, 3}));
    EXPECT_EQ(removeDuplicates({1, 1, 1, 1}), (std::vector<int>{1}));
    EXPECT_EQ(removeDuplicates({}), (std::vector<int>{}));
    EXPECT_EQ(removeDuplicates({1, 2, 3, 4, 5}), (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(RemoveDuplicatesTest, OrderPreservation) {
    EXPECT_EQ(removeDuplicates({3, 1, 2, 1, 3}), (std::vector<int>{3, 1, 2}));
}

TEST(ReverseListTest, BasicTests) {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    
    ListNode* reversed = reverseList(head);
    EXPECT_EQ(reversed->value, 3);
    EXPECT_EQ(reversed->next->value, 2);
    EXPECT_EQ(reversed->next->next->value, 1);
    
    delete reversed->next->next;
    delete reversed->next;
    delete reversed;
}

TEST(ReverseListTest, SingleElement) {
    ListNode* head = new ListNode(1);
    ListNode* reversed = reverseList(head);
    EXPECT_EQ(reversed->value, 1);
    delete reversed;
}

TEST(ReverseListTest, EmptyList) {
    ListNode* reversed = reverseList(nullptr);
    EXPECT_EQ(reversed, nullptr);
}

void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
