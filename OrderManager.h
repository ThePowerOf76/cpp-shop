#ifndef OM_H
#define OM_H
#include <vector>
#include "Client.h"
#include "Order.h"
#include "ProductManager.h"
using namespace std;
class OrderManager {
    private: 
        vector<Order> orders;
        void modify(Order *order);
    public:
       void addOrder(Client *c, ProductManager *p);
       vector<Order> getOrders() const { return orders; }
       void modifyOrder(Client* c);
       void saveOrders();
       void loadOrders(vector<Client> *c, ProductManager *p);
};
#endif