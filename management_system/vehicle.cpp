#include "vehicle.hpp"

Vehicle::Vehicle(Type type, unsigned long license_id, string description, int year)
    : m_type(type),
      m_license_id(license_id),
      m_description(description),
      m_year(year),
      m_status(Status::NEW)
{
    // empty
}
Status Vehicle::GetStatus() const
{
    return m_status;
}
Type Vehicle::GetType() const
{
    return m_type;
}

string Vehicle::DescribeVehicleProblem() const
{
    return m_description;
}

unsigned long Vehicle::GetLicenseId()
{
    return m_license_id;
}

int Vehicle::GetYear() const
{
    return m_year;
}

void Vehicle::SetStatus(Status status)
{
    m_status = status;
}

void Vehicle::SetDescription(string description)
{
    m_description = description;
}

void Vehicle::SetLicenseId(unsigned int license_id)
{
    m_license_id = license_id;
}

void Vehicle::SetYear(int year)
{
    m_year = year;
}

bool Vehicle::IsExtraSit()
{
    return false;
}

unsigned int Vehicle::GetWeight()
{
    return 0;
}

Car::Car(unsigned long license_id, string description, int year)
    : Vehicle(Type::CAR, license_id, description, year)
{
    // empty
}

Motorcycle::Motorcycle(unsigned long license_id, string description, int year, bool extra_sit)
    : Vehicle(Type::MOTORCYCLE, license_id, description, year), m_extra_sit(extra_sit)
{
    // empty
}

bool Motorcycle::IsExtraSit()
{
    return m_extra_sit;
}

Truck::Truck(unsigned long license_id, string description, int year, unsigned int weight)
    : Vehicle(Type::TRUCK, license_id, description, year), m_weight(weight)
{
    // empty
}

unsigned int Truck::GetWeight()
{
    return m_weight;
}