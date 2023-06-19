#ifndef CM_H
#define CM_H
#include "Client.h"
#include <vector>
class ClientManager {
    private:
        vector<Client> clientList;
    public:
        void addClient();
        void modClient(Client* client);
        vector<Client> *getClientList() { return &clientList; }
        Client* switchClient();
        void saveClients();
        vector<Client>* loadClients();

};
#endif