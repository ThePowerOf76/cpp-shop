#ifndef PM_H
#define PM_H
#include "Product.h"
#include <vector>
using namespace std;
class ProductManager {
    private:
        vector<Product> products;
    public:
        vector<Product> *getProducts() { return &products; }
        void loadProducts();
        void saveProducts();
        


};
#endif