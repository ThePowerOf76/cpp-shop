#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
using namespace std;
class Product {
    private:
        int p_id;
        string p_name;
        int p_count;
        const float p_price;
        const float p_vat;
    public:
        Product(int id, string p_name, int p_count, const float p_price, const float p_vat) : p_id(id), p_name(p_name), p_count(p_count), p_price(p_price), p_vat(p_vat) {}
        int get_count() { return p_count; }
        int order(int cnt);
        int get_pid() const { return p_id; }
        string get_name() const { return p_name; }
        float get_price() const { return p_price; }
        float get_vat() const { return p_vat; }

};
#endif