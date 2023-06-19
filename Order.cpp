#include "Order.h"
#include "Utils.h"
#include <ctime>
#include <utility>
bool Order::addToOrder(Product *product, int count) {
  if (product->get_count() >= count || count <= 0) {
    if (_products.count(product) > 0) {
      
      _products.find(product)->second += product->order(count);
    } else {
      _products.insert(pair<Product*, int>(product, product->order(count)));
    }
    return true;
  }
  return false;
}
bool Order::addToOrderNoUpdate(Product *product, int count) {
  if (product->get_count() >= count || count <= 0) {
    if (_products.count(product) > 0) {
      
      _products.find(product)->second += count;
    } else {
      _products.insert(pair<Product*, int>(product, count));
    }
    return true;
  }
  return false;
}
bool Order::modifyOrder(Product *product, int count, int old) {
  if (count <= 0) {
    return false;
  }
  if (count == 0) {
    product->order(-1*old);
    _products.erase(product);
  } else {
    if(count > old) {
      product->order(count - old);
    } else {
      product->order(-1*(old - count));
    }
    _products.find(product)->second = count;
    
  }
  return true;
}
bool Order::confirmOrder(float total) {
  cout << "Select payment method: \n1. Cash\n2. Card\n3. Blik\n4. Paypal\n5. Giftcard" << endl;
  bool loop = true;
  int pick;
  while(loop) {
    cin >> pick;
    if(pick > 0 && pick < 11) {
      _payment_method = PaymentMethod(pick);
      break;
    }
    cout << "Invalid payment method" << endl;
  }
  const auto now = std::chrono::system_clock::now();
  const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
  _order_time = *localtime(&t_c);
  _total_price = total;
  return true;

}
float Order::calc_total() {
  _total_price = 0;
  for(auto i: _products) {
    _total_price += (i.first->get_price() * i.second * (1 + i.first->get_vat()));
  }
  return _total_price;
}