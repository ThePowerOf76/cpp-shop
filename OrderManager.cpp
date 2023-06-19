#include "OrderManager.h"
#include "Order.h"
#include "ProductManager.h"
#include <fstream>
#include <vector>
void OrderManager::addOrder(Client *c, ProductManager *p) {
  Order o(c);
  vector<Product> *avail_products = p->getProducts();
  Product *temp = nullptr;
  int pick, count;
  while (true) {
    for (int i = 0; i < avail_products->size(); i++) {
      temp = &avail_products->at(i);
      cout << temp->get_pid() << ". " << temp->get_name()
           << " Count: " << temp->get_count() << " Price: $"
           << temp->get_price() << " VAT: " << temp->get_vat()*100 << "%" << endl;
    }
    cout << "Pick a number from the list or 0 to confirm order: " << endl;
    cin >> pick;
    if (pick > 0 && pick-1 < avail_products->size()) {
      temp = &avail_products->at(pick - 1);
      cout << "How much would you like to order? 0 to cancel" << endl;
      while (true) {
        cin >> count;
        if (count == 0) {
          break;
        }
        if (temp->get_count() > count) {
          o.addToOrder(temp, count);
          cout << "Order updated successfully." << endl;
          break;
        } else {
          cout << "Not enough products to order." << endl;
        }
      }
    } else if (pick == 0) {
      o.confirmOrder(o.calc_total());
      orders.push_back(o);
      return;
    } else {
      cout << "Wrong pick" << endl;
    }
  }
}
void OrderManager::saveOrders() {
  ofstream file, fileB;
  struct tm temp;
  int id, pid;
  float tota;
  char productSep = ']';
  int pm;
  file.open("orders.csv");
  fileB.open("orders.bin", ios_base::out | ios_base::binary);
  for (auto i : orders) {
    id = i.getClient()->getID();
    file << id << ";";
    fileB.write(reinterpret_cast<char *>(&id), sizeof(id));
    for (auto j : i.getProducts()) {
      pid = j.first->get_pid();
      file << "" << pid << ";" << j.second << ";";
      fileB.write(reinterpret_cast<char *>(&pid), sizeof(pid));
      fileB.write(reinterpret_cast<char *>(&j.second), sizeof(j.second));
    }
    fileB.write(reinterpret_cast<char *>(&productSep), sizeof(productSep));
    temp = i.getOrderTime();
    tota = i.getTotal();
    pm = i.getPaymentMethod();
    file << "/;" << tota << ";" << temp.tm_hour << ";" << temp.tm_min << ";"
         << temp.tm_sec << ";" << temp.tm_mday << ";" << temp.tm_mon << ";"
         << temp.tm_year << ";" << pm << endl;
    fileB.write(reinterpret_cast<char *>(&temp.tm_hour), sizeof(temp.tm_hour));
    fileB.write(reinterpret_cast<char *>(&temp.tm_min), sizeof(temp.tm_min));
    fileB.write(reinterpret_cast<char *>(&temp.tm_sec), sizeof(temp.tm_sec));
    fileB.write(reinterpret_cast<char *>(&temp.tm_mday), sizeof(temp.tm_mday));
    fileB.write(reinterpret_cast<char *>(&temp.tm_mon), sizeof(temp.tm_mon));
    fileB.write(reinterpret_cast<char *>(&temp.tm_year), sizeof(temp.tm_year));
    fileB.write(reinterpret_cast<char *>(&pm), sizeof(pm));
  }
  file.close();
  fileB.close();
}
void OrderManager::modify(Order *order) {
  map<Product*, int, ProductComp> p;
  int cnt = 0, pick, pick2, tmp = 0;
  while (true) {
    p = order->getProducts();
    cout << "Products: " << endl;
    cnt = 0;
    for (auto i : p) {
      cnt++;
      cout << cnt << ". Name: " << i.first->get_name() << endl
           << " Count: " << i.second << endl;
    }
    cout << "Pick a product: (0 to cancel)" << endl;
    cin >> pick;
    if (pick == 0) {
      break;
    } else if (pick > 0 && pick - 1 < p.size()) {
      tmp = 0;
      for (auto i : p) {
        tmp++;
        if (tmp == pick) {
          cout << "Input new amount: (0 to delete product)" << endl;
          cin >> pick2;
          order->modifyOrder(i.first, pick2, i.second);
        }
      }
    } else {
      cout << "Invalid pick" << endl;
    }
  }
}
void OrderManager::loadOrders(vector<Client> *c, ProductManager *p) {
  string id;
  int t;
  ifstream csv;
  string tmp, tmp2;
  bool flag = false;
  struct tm time;
  vector<Product> *avail_products = p->getProducts();
  csv.open("orders.csv");
  if (csv) {
    while (!csv.eof()) {
      getline(csv, id, ';');
      if (id == "") {
        break;
      }
      Order o(&c->at(stoi(id)));

      while (true) {
        if (!flag) {
          getline(csv, tmp, ';');
          if (tmp == "/") {
            break;
          }
        } else {
          getline(csv, tmp2, ';');
          o.addToOrderNoUpdate(&avail_products->at(stoi(tmp) - 1), stoi(tmp2));
        }
        flag = !flag;
      }
      getline(csv, tmp, ';');
      o.setTotal(std::stof(tmp));
      getline(csv, tmp, ';');
      time.tm_hour = std::stoi(tmp);
      getline(csv, tmp, ';');
      time.tm_min = std::stoi(tmp);
      getline(csv, tmp, ';');
      time.tm_sec = std::stoi(tmp);
      getline(csv, tmp, ';');
      time.tm_mday = std::stoi(tmp);
      getline(csv, tmp, ';');
      time.tm_mon = std::stoi(tmp);
      getline(csv, tmp, ';');
      time.tm_year = std::stoi(tmp);
      getline(csv, tmp);
      o.setPaymentMethod(PaymentMethod(std::stoi(tmp)));
      o.setTime(time);
      orders.push_back(o);
    }
    csv.close();
  } else {
    ofstream csv;
    csv.open("orders.csv");
    csv.close();
  }
}
void OrderManager::modifyOrder(Client *c) {
  vector<int> clientsOrderIDs;
  int pick;
  for (int i = 0; i < orders.size(); i++) {
    if (orders.at(i).isMyOrder(c)) {
      clientsOrderIDs.push_back(i);
    }
  }
  while (true) {
    cout << "Pick order ID (0 to cancel): " << endl;
    for (int i = 0; i < clientsOrderIDs.size(); i++) {
      cout << i + 1 << ". Order #" << clientsOrderIDs[i] << endl;
    }
    cin >> pick;
    if (pick > 0 && pick - 1 < clientsOrderIDs.size()) {
      modify(&orders.at(pick - 1));
      break;
    } else if (pick == 0) {
      break;
    } else {
      cout << "Invalid pick" << endl;
    }
  }
}
