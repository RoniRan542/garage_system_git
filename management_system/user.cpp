#include "user.hpp"

User::User(string name, string position, unsigned long id, GarageManager *GarageManager)
    : m_system(GarageManager),
      m_name(name),
      m_position(position),
      m_id(id)
{
    // empty
}

User::User(const User &other)
{
    m_id = other.m_id;
    m_name = other.m_name;
    m_position = other.m_position;
    m_system = other.m_system;
}

string User::GetName()
{
    return m_name;
}
string User::GetPosition()
{
    return m_position;
}

unsigned long User::GetID()
{
    return m_id;
}
GarageManager *User::GetSystem()
{
    return m_system;
}