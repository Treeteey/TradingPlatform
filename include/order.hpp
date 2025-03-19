#pragma
#include <cstdint>

enum class OrderType : uint8_t {
    BID, // buy
    ASK // sell
};

struct Order{
    OrderType type;
    double price;
    uint32_t quantity;
    uint64_t id;
};