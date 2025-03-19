#include "../include/order_book.hpp"
#include <vector>
#include <map>

class LockFreeOrderBook : public OrderBook{
    struct Node
    {
        Order order;
        std::atomic<Node*> next;
        Node(Order o) : order(o), next(nullptr){}
    };

    std::atomic<Node*> bid_head;
    std::atomic<Node*> ask_head;

    // price, volume
    std::map<double, uint32_t> bid_levels;
    std::map<double, uint32_t> ask_levels;

public:
    LockFreeOrderBook() : bid_head(nullptr), ask_head(nullptr) {}

    void add_order(Order order) override{
        Node* new_node = new Node(order);
        std::map<double,uint32_t>& levels = (order.type == OrderType::BID) ? bid_levels : ask_levels;

        // Lock free insert
        Node* current_head = (order.type == OrderType::BID) ? bid_head.load() : ask_head.load();
        new_node->next = current_head;

        while(!(order.type == OrderType::BID) ? bid_head.compare_exchange_weak(current_head, new_node) : 
                                                ask_head.compare_exchange_weak(current_head, new_node)){}
        
        // update levels
        levels[order.price] += order.quantity;
    }

    double get_best_bid() const override{
        auto it = bid_levels.begin();
        if(it != bid_levels.end()){
            return it->first;
        }else{
            return 0.0;
        }
    }

    double get_best_ask() const override{
        auto it = ask_levels.begin();
        if(it != ask_levels.end()){
            return it->first;
        }else{
            return 0.0;
        }
    }

    uint32_t get_volume_at(double price) const override{
        auto it = bid_levels.find(price);
        if(it != bid_levels.end()){
            return it->second;
        }else{
            return 0;
        }
    }
};