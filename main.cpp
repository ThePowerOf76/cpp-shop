#include "ClientManager.h"
#include "OrderManager.h"
#include "ProductManager.h"
#include <ctime>
#include <vector>
int main() {
    ClientManager c;
    ProductManager p;
    OrderManager o;
    p.loadProducts();
    c.loadClients();
    o.loadOrders(c.getClientList(), &p);
    Client* current = nullptr; 
    string _pick;
    int pick;
    current = &c.getClientList()->at(0);
    while(true) {
        cout << "Logged in as: " << current->getName() << " " << current->getSname() << " " << current->getAddress() << " " << current->getGender() << endl;
        cout << "1. Add client\n2. Modify client\n3. Change client\n4. Add order\n5. Change order\n6. View products\n7. View orders\n8. Save\n9. Exit" << endl;
        std::getline(std::cin, _pick);
        pick = std::atoi(&_pick[0]);
        cout << (int) _pick[0] << endl;
        switch(pick) {
            case 1: 
                c.addClient();
                break;
            case 2:
                c.modClient(current);
                break;
            case 3:
                current = c.switchClient();
                break;
            case 4:
                o.addOrder(current, &p);
                break;
            case 5:
                o.modifyOrder(current);
                break;
            case 6:
                for(auto i : *p.getProducts()) {
                    cout << "PID: " << i.get_pid() << " Name: " << i.get_name() << " Price:" << i.get_price() << " Quantity: " << i.get_count() << " VAT: " << i.get_vat()*100 << "%" << endl;
                }
                break;
            case 7: {
                int i = 0, pick;
                for(auto order: o.getOrders()) {
                    i++;
                    cout << "Order ID: " << i << " Client ID: " << order.getClient()->getID() << " Products: [Expand] Total: " << order.getTotal() << " Order time: " << order.getOrderTimeString() << " Payment Method ID: " << order.getPaymentMethod() << endl;
                }
                while(true) {
                    cout << "Input order ID to expand product list or 0 to cancel." << endl;
                    cin >> pick;
                    if(pick == 0) {
                        break;
                    } else if(pick < 0 || pick > o.getOrders().size()) {
                        cout << "Invalid order ID." << endl;
                    } else {
                        i = 0;
                        for(auto order: o.getOrders()) {
                        i++;
                        if(i == pick) {
                            for(auto prod: order.getProducts()) {
                                cout << prod.first->get_name() << " Amount: " << prod.second << endl;
                            }
                        }
                }
                    }
                }
                break;
            }
            case 8:
                c.saveClients();
                o.saveOrders();
                p.saveProducts();
                break;
            case 9:
                c.saveClients();
                o.saveOrders();
                p.saveProducts();
                return 0;
            default:
                break;
        }
    }
}