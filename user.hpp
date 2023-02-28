#include <iostream>
#include "garage_system.hpp"

using namespace std;

class User
{
public:
    User(string name, string position, unsigned long id, GarageManager *GarageManager);
    User(const User &other);
    string GetName();
    string GetPosition();
    unsigned long GetID();
    GarageManager *GetSystem();

private:
    GarageManager *m_system;
    string m_name;
    string m_position;
    unsigned long m_id;
};
