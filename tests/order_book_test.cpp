#include <gtest/gtest.h>
#include "../src/lock_free_order_book.cpp"

TEST(OrderBookTest, AddBidIncreasesVolume){
    LockFreeOrderBook book;
    book.add_order({OrderType::BID, 100.5, 100, 1});
    ASSERT_EQ(book.get_volume_at(100.5), 100);
}

TEST(OrderBookTest, BestBidUpdatesCorrectly) {
    LockFreeOrderBook book;
    book.add_order({OrderType::BID, 100.0, 50, 2});
    book.add_order({OrderType::BID, 101.0, 30, 3});
    ASSERT_DOUBLE_EQ(book.get_best_bid(), 101.0);
}