#pragma
#include "order.hpp"
#include <atomic>
#include <memory>

class OrderBook{
public:
    virtual ~OrderBook() = default;
    // add order to
    virtual void add_order(Order order) = 0;

    virtual double get_best_bid() const = 0;
    virtual double get_best_ask() const = 0;

    virtual uint32_t get_volume_at(double price) const = 0;
};