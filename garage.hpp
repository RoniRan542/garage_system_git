#include <iostream>
#include <unordered_map>
#include <fstream>

#include "user.hpp"

using namespace std;

class Garage
{
public:
    Garage(string backup_users, string backup_vehicles, string backup_profits);
    ~Garage();
    void CreateUser(string name, string position, unsigned long user_id);
    User *GetUser(unsigned long user_id);
    void DeleteUser(unsigned long user_id);
    void BackupUserAdd(User *user);
    void BackupUserDelete(unsigned long user_id);
    bool RestoreSystem(string file_path);

private:
    unordered_map<unsigned long, User *> m_users;
    GarageManager *m_system;
    string m_backup_users;
    string m_backup_vehicles;
    string m_backup_profits;
};
