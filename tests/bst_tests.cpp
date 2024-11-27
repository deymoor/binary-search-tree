#include "libs/bst.h"
#include <gtest/gtest.h>
#include <vector>

using namespace BinarySearchTree;

TEST(BstTestSuite, PreorderTest1) {
    Bst<int, preorder> bst;
    bst.insert(9);
    bst.insert(10);
    bst.insert(3);
    bst.insert(2);
    bst.insert(7);
    bst.insert(4);
    bst.insert(5);
    bst.insert(8);
    std::vector<int> ans = {9, 3, 2, 7, 4, 5, 8, 10};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, PreorderTest2) {
    Bst<int, preorder> bst;
    bst.insert(1);
    std::vector<int> ans = {1};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, PreorderTest3) {
    Bst<int, preorder> bst;
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    std::vector<int> ans = {1, 2, 3, 4};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, PreorderReverseTest1) {
    Bst<int, preorder> bst;
    bst.insert(9);
    bst.insert(10);
    bst.insert(3);
    bst.insert(2);
    bst.insert(7);
    bst.insert(4);
    bst.insert(5);
    bst.insert(8);
    bst.insert(4);

    std::vector<int> ans = {10, 8, 5, 4, 7, 2, 3, 9};
    auto i = --bst.end();
    int j = 0;
    for (; i != bst.begin(); --i, ++j) {                                                                                                                                                                                                                            bst.insert(4);
    bst.insert(4);
    bst.insert(4);
    bst.insert(4);

        ASSERT_EQ(*i, ans[j]);
    }
    ASSERT_EQ(*i, ans[j]);
}

TEST(BstTestSuite, PreorderReverseTest2) {
    Bst<int, preorder> bst;
    bst.insert(1);
    std::vector<int> ans = {1};
    auto i = --bst.end();
    int j = 0;
    for (; i != bst.begin(); --i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
    ASSERT_EQ(*i, ans[j]);
}

TEST(BstTestSuite, PreorderReverseTest3) {
    Bst<int, preorder> bst;
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    std::vector<int> ans = {4, 3, 2, 1};
    auto i = --bst.end();
    int j = 0;
    for (; i != bst.begin(); --i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
    ASSERT_EQ(*i, ans[j]);
}

TEST(BstTestSuite, InorderTest1) {
    Bst<int, inorder> bst;
    bst.insert(9);
    bst.insert(10);
    bst.insert(3);
    bst.insert(2);
    bst.insert(7);
    bst.insert(4);
    bst.insert(5);
    bst.insert(8);
    std::vector<int> ans = {2, 3, 4, 5, 7, 8, 9, 10};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, InorderTest2) {
    Bst<int, inorder> bst;
    bst.insert(1);
    std::vector<int> ans = {1};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, InorderTest3) {
    Bst<int, inorder> bst;
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    std::vector<int> ans = {1, 2, 3, 4};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, InorderReverseTest1) {
    Bst<int, inorder> bst;
    bst.insert(9);
    bst.insert(10);
    bst.insert(3);
    bst.insert(2);
    bst.insert(7);
    bst.insert(4);
    bst.insert(5);
    bst.insert(8);
    std::vector<int> ans = {10, 9, 8, 7, 5, 4, 3, 2};
    auto i = --bst.end();
    int j = 0;
    for (; i != bst.begin(); --i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
    ASSERT_EQ(*i, ans[j]);
}

TEST(BstTestSuite, InorderReverseTest2) {
    Bst<int, inorder> bst;
    bst.insert(1);
    std::vector<int> ans = {1};
    auto i = --bst.end();
    int j = 0;
    for (; i != bst.begin(); --i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
    ASSERT_EQ(*i, ans[j]);
}

TEST(BstTestSuite, InorderReverseTest3) {
    Bst<int, inorder> bst;
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    std::vector<int> ans = {4, 3, 2, 1};
    auto i = --bst.end();
    int j = 0;
    for (; i != bst.begin(); --i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
    ASSERT_EQ(*i, ans[j]);
}

TEST(BstTestSuite, PostorderTest1) {
    Bst<int, postorder> bst;
    bst.insert(9);
    bst.insert(10);
    bst.insert(3);
    bst.insert(2);
    bst.insert(7);
    bst.insert(4);
    bst.insert(5);
    bst.insert(8);
    std::vector<int> ans = {2, 5, 4, 8, 7, 3, 10, 9};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, PostorderTest2) {
    Bst<int, postorder> bst;
    bst.insert(1);
    std::vector<int> ans = {1};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, PostorderTest3) {
    Bst<int, postorder> bst;
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    std::vector<int> ans = {4, 3, 2, 1};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, PostorderReverseTest1) {
    Bst<int, postorder> bst;
    bst.insert(9);
    bst.insert(10);
    bst.insert(3);
    bst.insert(2);
    bst.insert(7);
    bst.insert(4);
    bst.insert(5);
    bst.insert(8);
    std::vector<int> ans = {9, 10, 3, 7, 8, 4, 5, 2};
    auto i = --bst.end();
    int j = 0;
    for (; i != bst.begin(); --i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
    ASSERT_EQ(*i, ans[j]);
}

TEST(BstTestSuite, PostorderReverseTest2) {
    Bst<int, postorder> bst;
    bst.insert(1);
    std::vector<int> ans = {1};
    auto i = --bst.end();
    int j = 0;
    for (; i != bst.begin(); --i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
    ASSERT_EQ(*i, ans[j]);
}

TEST(BstTestSuite, PostorderReverseTest3) {
    Bst<int, postorder> bst;
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    std::vector<int> ans = {1, 2, 3, 4};
    auto i = --bst.end();
    int j = 0;
    for (; i != bst.begin(); --i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
    ASSERT_EQ(*i, ans[j]);
}

TEST(BstTestSuite, EmptyTest1) {
    Bst<int, preorder> bst;
    ASSERT_EQ(true, bst.empty());
}

TEST(BstTestSuite, EmptyTest2) {
    Bst<int, preorder> bst;
    bst.insert(1);
    ASSERT_EQ(false, bst.empty());
}

TEST(BstTestSuite, SizeTest1) {
    Bst<int, preorder> bst;
    ASSERT_EQ(0, bst.size());
}

TEST(BstTestSuite, SizeTest2) {
    Bst<int, preorder> bst;
    bst.insert(1);
    ASSERT_EQ(1, bst.size());
}

TEST(BstTestSuite, SizeTest3) {
    Bst<int, preorder> bst;
    bst.insert(1);
    bst.insert(2);
    ASSERT_EQ(2, bst.size());
}

TEST(BstTestSuite, SizeTest4) {
    Bst<int, preorder> bst;
    bst.insert(1);
    bst.insert(2);
    bst.insert(2);
    ASSERT_EQ(2, bst.size());
}

TEST(BstTestSuite, BegEndTest1) {
    Bst<int, preorder> bst;
    ASSERT_EQ(true, bst.begin() == bst.end());
}

TEST(BstTestSuite, BegEndTest2) {
    Bst<int, preorder> bst;
    bst.insert(1);
    ASSERT_EQ(true, bst.begin() != bst.end());
}

TEST(BstTestSuite, MaxSizeTest1) {
    Bst<int32_t, preorder> bst;
    ASSERT_EQ(4611686018427387903, bst.max_size());
}

TEST(BstTestSuite, CopyConstructorTest1) {
    Bst<int, preorder> bst;
    bst.insert(9);
    bst.insert(10);
    bst.insert(3);
    bst.insert(2);
    bst.insert(7);
    bst.insert(4);
    bst.insert(5);
    bst.insert(8);
    Bst <int, preorder> bst2(bst);
    ASSERT_EQ(bst, bst2);
}

TEST(BstTestSuite, CopyConstructorTest2) {
    Bst<int, preorder> bst;
    bst.insert(9);
    bst.insert(10);
    bst.insert(3);
    bst.insert(2);
    bst.insert(7);
    bst.insert(4);
    bst.insert(5);
    bst.insert(8);
    Bst <int, preorder> bst2(bst);
    bst2.insert(34);
    ASSERT_NE(bst, bst2);
}

TEST(BstTestSuite, CopyAssignmentTest1) {
    Bst<int, preorder> bst;
    bst.insert(9);
    bst.insert(10);
    bst.insert(3);
    bst.insert(2);
    bst.insert(7);
    bst.insert(4);
    bst.insert(5);
    bst.insert(8);
    Bst <int, preorder> bst2;
    bst2 = bst;
    ASSERT_EQ(bst, bst2);
}

TEST(BstTestSuite, CopyAssignmentTest2) {
    Bst<int, preorder> bst;
    bst.insert(9);
    bst.insert(10);
    bst.insert(3);
    bst.insert(2);
    bst.insert(7);
    bst.insert(4);
    bst.insert(5);
    bst.insert(8);
    Bst <int, preorder> bst2;
    bst2.insert(34);
    bst2 = bst;
    ASSERT_EQ(bst, bst2);
}

TEST(BstTestSuite, ComparatorTest1) {
    Bst<int, preorder, std::greater<int>> bst;
    bst.insert(9);
    bst.insert(10);
    bst.insert(3);
    bst.insert(2);
    bst.insert(7);
    bst.insert(4);
    bst.insert(5);
    bst.insert(8);
    std::vector<int> ans = {9, 10, 3, 7, 8, 4, 5, 2};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, ConstructViaIteratorTest1) {
    std::vector<int> a = {1, 9, 10, 3, 2, 7, 4, 5, 8, 11};
    Bst<int, preorder> bst(a.begin() + 1, a.end() - 1);
    std::vector<int> ans = {9, 3, 2, 7, 4, 5, 8, 10};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, ConstructViaIteratorTest2) {
    std::vector<int> a = {1, 9, 10, 3, 2, 7, 4, 5, 8, 11};
    Bst<int, preorder, std::greater<int>> bst(a.begin() + 1, a.end() - 1, std::greater<int>());
    std::vector<int> ans = {9, 10, 3, 7, 8, 4, 5, 2};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, ConstructViaInitListTest1) {
    Bst<int, preorder> bst({9, 10, 3, 2, 7, 4, 5, 8});
    std::vector<int> ans = {9, 3, 2, 7, 4, 5, 8, 10};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, AssignmentViaInitListTest1) {
    Bst<int, preorder> bst;
    bst.insert(12);
    bst = {9, 10, 3, 2, 7, 4, 5, 8};
    std::vector<int> ans = {9, 3, 2, 7, 4, 5, 8, 10};
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, FindTest1) {
    Bst<int, preorder> bst({9, 10, 3, 2, 7, 4, 5, 8});
    ASSERT_EQ(*bst.find(3), 3);
}

TEST(BstTestSuite, FindTest2) {
    Bst<int, preorder> bst({9, 10, 3, 2, 7, 4, 5, 8});
    auto i = bst.find(1);
    auto j = bst.end();
    ASSERT_EQ(true, i == j);
}


TEST(BstTestSuite, EraseTest1) {
    Bst<int, preorder> bst = {9, 10, 3, 2, 7, 4, 5, 8};
    std::vector<int> ans = {9, 3, 2, 7, 4, 8, 10};
    bst.erase(5);
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, EraseTest2) {
    Bst<int, preorder> bst = {9, 10, 3, 2, 7, 4, 5, 8};
    bst.erase(5);
    bst.erase(4);
    bst.erase(8);
    bst.erase(7);
    bst.erase(2);
    bst.erase(3);
    bst.erase(10);
    bst.erase(9);
    ASSERT_EQ(true, bst.empty());
}

TEST(BstTestSuite, EraseTest3) {
    Bst<int, preorder> bst = {9, 10, 3, 2, 7, 4, 5, 8};
    ASSERT_EQ(0, bst.erase(12));
}

TEST(BstTestSuite, EraseTest4) {
    Bst<int, preorder> bst;
    ASSERT_EQ(0, bst.erase(0));
}

TEST(BstTestSuite, EraseTest5) {
    Bst<int, preorder> bst = {9, 10, 3, 2, 7, 4, 5, 8};
    std::vector<int> ans = {9, 3, 2, 7, 5, 8, 10};
    bst.erase(4);
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, EraseTest6) {
    Bst<int, preorder> bst = {9, 10};
    std::vector<int> ans = {10};
    bst.erase(9);
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, EraseTest7) {
    Bst<int, preorder> bst = {9, 10, 3, 2, 7, 4, 5, 8};
    std::vector<int> ans = {9, 3, 2, 8, 4, 5, 10};
    bst.erase(7);
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, EraseTest8) {
    Bst<int, preorder> bst = {9, 10, 3, 2, 7, 4, 5, 8};
    std::vector<int> ans = {9, 4, 2, 7, 5, 8, 10};
    bst.erase(3);
    int j = 0;
    for (auto i = bst.begin(); i != bst.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans[j]);
    }
}

TEST(BstTestSuite, MergeTest1) {
    Bst<int, preorder> bst1;
    Bst<int, preorder> bst2;
    bst1 = {3, 1, 4, 2, 5};
    bst2 = {5, 6, 7, 3, 4, 1};
    std::vector<int> ans1 = {3, 1, 2, 4, 5, 6, 7};
    std::vector<int> ans2 = {5, 3, 1, 4};
    bst1.merge(bst2);
    int j = 0;
    for (auto i = bst1.begin(); i != bst1.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans1[j]);
    }
    j = 0;
    for (auto i = bst2.begin(); i != bst2.end(); ++i, ++j) {
        ASSERT_EQ(*i, ans2[j]);
    }
}

TEST(BstTestSuite, LowerBoundTest1) {
    Bst<int, preorder> bst = {9, 10, 3, 2, 7, 4, 5, 8};
    ASSERT_EQ(2, *bst.lower_bound(1));
}

TEST(BstTestSuite, LowerBoundTest2) {
    Bst<int, preorder> bst = {9, 10, 3, 2, 7, 4, 5, 8};
    ASSERT_EQ(true, bst.lower_bound(11) == bst.end());
}

TEST(BstTestSuite, UpperBoundTest1) {
    Bst<int, preorder> bst = {9, 10, 3, 2, 7, 4, 5, 8};
    ASSERT_EQ(4, *bst.upper_bound(3));
}

TEST(BstTestSuite, UpperBoundTest2) {
    Bst<int, preorder> bst = {9, 10, 3, 2, 7, 4, 5, 8};
    ASSERT_EQ(true, (bst.upper_bound(12) == bst.end()));
}