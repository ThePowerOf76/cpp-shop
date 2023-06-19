#ifndef CLIENT_H
#define CLIENT_H
#include <string>
using namespace std;
class Client {
    private:
        int _client_id;
        string _name;
        string _sname;
        string _address;
        char _gender;
    public:
        Client(int id, string name, string sname, string address, char gender) : _client_id(id), _name(name), _sname(sname), _address(address), _gender(gender) {}
        string getName() const { return _name; }
        string getSname() const { return _sname; }
        string getAddress() const { return _address; }
        int getID() const { return _client_id; }
        char getGender() const { return _gender; }
        void setName(string name) { _name = name; }
        void setSname(string sname) { _sname = sname; }
        void setAddress(string address) { _address = address; }
        void setGender(char gender) { _gender = gender; }
        string toString() const { return _name + " " + _sname + " " + _address + " " + _gender; }
};
#endif