#ifndef ORDER_H
#define ORDER_H 
#include "Client.h"
#include "Product.h"
#include <utility>
#include <bits/stdc++.h>
#include <ctime>
#include "Utils.h"
struct ProductComp {
       bool operator() (const Product *first, const Product *another) const { return first->get_pid() < another->get_pid(); } 
};
class Order {
    private:
        Client* _client;
        std::map<Product*, int, ProductComp> _products;
        struct tm _order_time;
        float _total_price;
        PaymentMethod _payment_method;
    public: 
        Order(Client* c) {
            _client = c;
        }
        bool addToOrder(Product* product, int count);
        bool addToOrderNoUpdate(Product *product, int count);
        bool modifyOrder(Product* product, int count, int old);
        float calc_total();
        bool isMyOrder(Client* c) { return _client == c; }
        bool confirmOrder(float total);
        Client* getClient() const { return _client; }
        map<Product*, int, ProductComp> getProducts() const { return _products; }
        struct tm getOrderTime() const { return _order_time;}
        string getOrderTimeString() const { return asctime(&_order_time); }
        float getTotal() const { return _total_price; }
        void setTotal(float total) { _total_price = total; }
        PaymentMethod getPaymentMethod() const { return _payment_method; }
        void setPaymentMethod(PaymentMethod payment_method) { _payment_method = payment_method; }
        void setTime(struct tm time) { _order_time = time; }
};

#endif