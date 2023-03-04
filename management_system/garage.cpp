#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <unordered_map>
#include <exception>

#include "garage.hpp"

using namespace std;
// When starting a garage we create a ManageSystem object and create the backup files
Garage::Garage(string backup_users, string backup_vehicles, string backup_profits)
    : m_backup_users(backup_users), m_backup_vehicles(backup_vehicles), m_backup_profits(backup_profits)
{
    m_system = new GarageManager(backup_vehicles, backup_profits);
}

// When ending a garage we must free the manage_system pointer from memory and also delete users.
Garage::~Garage()
{
    delete m_system;
    // TODO: delete users
}
// users are stored in a hashMap as id:User(ptr) and we get their address
User *Garage::GetUser(unsigned long user_id)
{
    return m_users[user_id];
}

// when creating a user object in memory we insert its address in the hashMap and also update the backup file
void Garage::CreateUser(string name, string position, unsigned long user_id)
{
    User *user = new User(name, position, user_id, m_system);
    m_users.insert(pair<unsigned long, User *>(user_id, user));
    BackupUserAdd(user);
}

// when we delete a user we find it in the hashMap by its id and delete it. Additionally we update the backup file
void Garage::DeleteUser(unsigned long user_id)
{
    if (m_users.find(user_id) != m_users.end())
    {
        m_users.erase(user_id);
    }
    BackupUserDelete(user_id);
}
/*
this function reads the json file into a json obj, appends the new json-user obj and stores the new backup file.
The input is a pointer to the user in order to extract its details.
 */
void Garage::BackupUserAdd(User *user)
{
    if (ifstream(m_backup_users))
    {
        ifstream jsonFile(m_backup_users);
        Json::Value users(Json::arrayValue);
        jsonFile >> users;
        for (Json::Value::ArrayIndex i = 0; i < users.size(); ++i)
        {
            if (user->GetID() == users[i]["id"].asInt())
            {
                cout << " Already exists!" << endl;
                return;
            }
        }

        Json::Value juser;
        juser["name"] = user->GetName();
        juser["position"] = user->GetPosition();
        juser["id"] = user->GetID();
        users.append(juser);
        ofstream file(m_backup_users);
        file << users.toStyledString();

        file.close();
    }
    else
    {
        Json::Value users(Json::arrayValue);
        Json::Value juser;
        juser["name"] = user->GetName();
        juser["position"] = user->GetPosition();
        juser["id"] = user->GetID();
        users.append(juser);

        ofstream usersNewFile(m_backup_users);
        usersNewFile << users.toStyledString();
        usersNewFile.close();
    }
}

void Garage::BackupUserDelete(unsigned long user_id)
{
    ifstream jsonFile(m_backup_users);
    Json::Value users(Json::arrayValue);
    jsonFile >> users;
    Json::Value new_users(Json::arrayValue);
    for (Json::Value::ArrayIndex i = 0; i < users.size(); ++i)
    {
        if (user_id != users[i]["id"].asInt())
        {
            new_users.append(users[i]);
        }
    }
    ofstream usersNewFile(m_backup_users);
    usersNewFile << new_users.toStyledString();
    usersNewFile.close();
}

/*
bool Garage::RestoreSystem(string file_path)
{
    ifstream jsonFile(m_backup_users);
    Json::Value users(Json::arrayValue);
    jsonFile >> users;
} */
