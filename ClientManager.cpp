#include "ClientManager.h"
#include <cstddef>
#include <fstream>
#include <ios>
#include <iostream>
#include <vector>
using namespace std;
void ClientManager::addClient() {
  string i, n, a, g;
  cout << "Podaj imie: " << endl;
  cin >> i;
  cout << "Podaj nazwisko: " << endl;
  cin >> n;
  cout << "Podaj adres: " << endl;
  cin.ignore();
  getline(cin,a);
  cout << "Podaj plec (M/F): " << endl;
  getline(cin,g);
  int size = clientList.size();
  clientList.push_back(Client(size, i, n, a, g.at(0)));
}
void ClientManager::modClient(Client *client) {
  string i, n, a;
  char g;
  cout << "Podaj imie: " << endl;
  cin >> i;
  cout << "Podaj nazwisko: " << endl;
  cin >> n;
  cout << "Podaj adres: " << endl;
    cin.ignore();
  getline(cin,a);
  cout << "Podaj plec (M/F): " << endl;
  cin >> g;
  client->setAddress(a);
  client->setGender(g);
  client->setName(i);
  client->setSname(n);
}
Client *ClientManager::switchClient() {
  for (int i = 0; i < clientList.size(); i++) {
    cout << i + 1 << clientList[i].toString() << endl;
  }
  cout << "Wybierz klienta: ";
  int i;
  do {
    cin >> i;
  } while (i > 0 && i < clientList.size());
  return &clientList[i-1];
}
void ClientManager::saveClients() {
  ofstream save;
  save.open("clients.csv");
  for (Client c : clientList) {
    save << c.getID() << ";" << c.getName() << ";" << c.getSname() << ";"
         << c.getAddress() << ";" << c.getGender() << endl;
  }
  save.close();
  ofstream saveB;
  saveB.open("clientsBinary", ios_base::out | ios_base::binary);
  int id;
  string i, n, a;
  char g;
  for (Client c : clientList) {
    id = c.getID();
    i = c.getName();
    n = c.getSname();
    a = c.getAddress();
    g = c.getGender();
    saveB.write(reinterpret_cast<char *>(&id), sizeof(id));
    saveB.write(reinterpret_cast<char *>(&i), sizeof(i));
    saveB.write(reinterpret_cast<char *>(&n), sizeof(n));
    saveB.write(reinterpret_cast<char *>(&a), sizeof(a));
    saveB.write(reinterpret_cast<char *>(&g), sizeof(g));
  }
  saveB.close();
}
vector<Client> *ClientManager::loadClients() {
  string id, name, surname, address, gender;
  ifstream csv;
  csv.open("clients.csv");
  if (csv) {
    while (!csv.eof()) {
      getline(csv, id, ';');
      if(id == "") {
        break;
      }
      getline(csv, name, ';');
      getline(csv, surname, ';');
      getline(csv, address, ';');
      getline(csv, gender);
        cout.flush();
      clientList.push_back(
          Client(std::stoi(id), name, surname, address, gender.at(0)));
    }
    csv.close();
    return &clientList;
  } else {
    ofstream create("clients.csv");
    string i, n, a;
    char g;
    cout << "Podaj imie: " << endl;
    cin >> i;
    cout << "Podaj nazwisko: " << endl;
    cin >> n;
    cout << "Podaj adres: " << endl;
    cin.ignore();
    getline(cin,a);
    cout << "Podaj plec (M/F): " << endl;
    cin >> g;
    create << 1 << ";" << i << ";" << n << ";" << a << ";" << g << endl;
    clientList.push_back(Client(0, i, n, a, g));
    return &clientList;
  }
}