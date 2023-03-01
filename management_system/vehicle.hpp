
#ifndef __Vehicle_Hpp__
#define __Vehicle_Hpp__

#include <iostream>

using namespace std;

enum Status
{
    NEW,
    IN_PROCESS,
    REALEASED
};

enum Type
{
    CAR,
    MOTORCYCLE,
    TRUCK
};

class Vehicle
{
public:
    Vehicle(Type type, unsigned long license_id, string description, int year);
    Status GetStatus() const;
    Type GetType() const;
    string DescribeVehicleProblem() const;
    unsigned long GetLicenseId();
    int GetYear() const;
    void SetStatus(Status status);
    void SetDescription(string description);
    void SetLicenseId(unsigned int license_id);
    void SetYear(int year);
    virtual bool IsExtraSit() = 0;
    virtual unsigned int GetWeight() = 0;

private:
    Status m_status;
    Type m_type;
    string m_description;
    unsigned long m_license_id;
    int m_year;
};

class Car : public Vehicle
{
public:
    Car(unsigned long license_id, string description, int year);
    virtual bool IsExtraSit();
    virtual unsigned int GetWeight();
};

class Motorcycle : public Vehicle
{
public:
    Motorcycle(unsigned long license_id, string description, int year, bool extra_sit);
    virtual bool IsExtraSit();
    virtual unsigned int GetWeight();

private:
    bool m_extra_sit;
};

class Truck : public Vehicle
{
public:
    Truck(unsigned long license_id, string description, int year, unsigned int weight);
    virtual unsigned int GetWeight();
    virtual bool IsExtraSit();

private:
    unsigned int m_weight;
};

#endif //__Vehicle_Hpp__