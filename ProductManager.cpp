#include "ProductManager.h"
#include "Product.h"
#include <fstream>
#include <string>
#include <iostream>
void ProductManager::loadProducts() {
    string p_id, p_name, p_count, p_price, p_vat;
    ifstream csv;
    csv.open("products.csv");
    while(!csv.eof()) {
        getline(csv, p_id, ';');
        if(p_id == "") {
            break;
        }
        getline(csv, p_name, ';');
        getline(csv, p_count, ';');
        getline(csv, p_price, ';');
        getline(csv, p_vat);
        products.push_back(Product(std::stoi(p_id), p_name, std::stoi(p_count), std::stof(p_price), std::stof(p_vat)));
    }
    csv.close();
}
void ProductManager::saveProducts() {
    ofstream save;
    save.open("products.csv");
    for(Product p: products) {
        save << p.get_pid() << ";" << p.get_name() << ";" << p.get_count() << ";" << p.get_price() << ";" << p.get_vat() << endl;
    }
    save.close();
}