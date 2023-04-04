#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <list>
#include <set>
#include <unordered_map>
#include <exception>

#include "garage_system.hpp"

using namespace std;
// when creating the manager object I store the paths to the backup files becouse the object will change them
GarageManager::GarageManager(string backup_vehicles, string backup_profits)
    : m_backup_vehicles(backup_vehicles), m_backup_profits(backup_profits)
{
    // empty
}

/*
    when the manager object Insert a new vehicle, the input is a pointer to the new vehicle.
    fhe manager stores it in two places: 1) the hashMap, 2) the multiSet that is sorted by the year of
    manufacturing.
*/
void GarageManager::InsertV(Vehicle *vehicle)
{
    vehicles.insert(vehicle);
    license_ids[vehicle->GetLicenseId()] = vehicle;
    BackupVehicleAdd(vehicle);
}

/*
    when the manager object change the state of a vehicle, the input is a the license_id of the vehicle and
    the new status. I find the right vehicle and change its status. If the vehicle is released I also update
    the total profit. Additionally I also update the backup files in every change.

*/
void GarageManager::ChangeVehicleStatus(unsigned long license_id, Status new_status)
{
    Vehicle *vehicle = license_ids.find(license_id)->second;
    auto vehicle_iter = vehicles.find(vehicle);
    Vehicle *v = *vehicle_iter;
    v->SetStatus(new_status);
    BackupUpdateVehicle(v);
    if (new_status == Status::REALEASED)
    {
        Type curr_type = v->GetType();

        switch (curr_type)
        {
        case Type::CAR:
            m_total_profits += 2000;
            break;
        case Type::MOTORCYCLE:
            m_total_profits += 1000;
            break;
        case Type::TRUCK:
            m_total_profits += 3000;
            break;
        default:
            break;
        }
        vehicles.erase(vehicle_iter);
        BackupUpdateProfit();
    }
}
/*
    the user gets a set of vehicles organized by year of manufacturing.
 */
multiset<Vehicle *, vehicle_year_comp> GarageManager::GetVehicles()
{
    return vehicles;
}

size_t GarageManager::GetTotalProfit()
{
    return m_total_profits;
}

void GarageManager::BackupVehicleAdd(Vehicle *vehicle)
{
    if (ifstream(m_backup_vehicles))
    {
        ifstream jsonFile(m_backup_vehicles);
        Json::Value vehicles(Json::arrayValue);
        jsonFile >> vehicles;

        for (Json::Value::ArrayIndex i = 0; i < vehicles.size(); ++i)
        {
            if (vehicle->GetLicenseId() == vehicles[i]["license_id"].asInt())
            {
                cout << " Already exists!" << endl;
                return;
            }
        }

        Json::Value jVehicle;
        if (vehicle->GetType() == Type::MOTORCYCLE)
        {
            jVehicle["extra_sit"] = vehicle->IsExtraSit();
        }
        else if (vehicle->GetType() == Type::TRUCK)
        {
            jVehicle["weight"] = vehicle->GetWeight();
        }

        jVehicle["license_id"] = vehicle->GetLicenseId();
        jVehicle["Type"] = vehicle->GetType();
        jVehicle["description"] = vehicle->DescribeVehicleProblem();
        jVehicle["Year"] = vehicle->GetYear();
        jVehicle["status"] = vehicle->GetStatus();

        vehicles.append(jVehicle);
        ofstream file(m_backup_vehicles);
        file << vehicles.toStyledString();
        file.close();
    }
    else
    {
        Json::Value vehicles(Json::arrayValue);
        Json::Value jVehicle;
        if (vehicle->GetType() == Type::MOTORCYCLE)
        {
            jVehicle["extra_sit"] = vehicle->IsExtraSit();
        }
        else if (vehicle->GetType() == Type::TRUCK)
        {
            jVehicle["weight"] = vehicle->GetWeight();
        }

        jVehicle["license_id"] = vehicle->GetLicenseId();
        jVehicle["Type"] = vehicle->GetType();
        jVehicle["description"] = vehicle->DescribeVehicleProblem();
        jVehicle["Year"] = vehicle->GetYear();
        jVehicle["status"] = vehicle->GetStatus();
        vehicles.append(jVehicle);

        ofstream vehiclesNewFile(m_backup_vehicles);
        vehiclesNewFile << vehicles.toStyledString();
        vehiclesNewFile.close();
    }
}

void GarageManager::BackupUpdateVehicle(Vehicle *vehicle)
{
    ifstream jsonFile(m_backup_vehicles);
    Json::Value vehicles(Json::arrayValue);
    jsonFile >> vehicles;

    // find the vehicle in the dictionary
    for (Json::Value::ArrayIndex i = 0; i < vehicles.size(); ++i)
    {
        if (vehicle->GetLicenseId() == vehicles[i]["license_id"].asInt())
        {
            if (vehicle->GetType() == Type::MOTORCYCLE)
            {
                vehicles[i]["extra_sit"] = vehicle->IsExtraSit();
            }
            else if (vehicle->GetType() == Type::TRUCK)
            {
                vehicles[i]["weight"] = vehicle->GetWeight();
            }
            vehicles[i]["license_id"] = vehicle->GetLicenseId();
            vehicles[i]["Type"] = vehicle->GetType();
            vehicles[i]["description"] = vehicle->DescribeVehicleProblem();
            vehicles[i]["Year"] = vehicle->GetYear();
            vehicles[i]["status"] = vehicle->GetStatus();

            cout << " Vehicle updated!" << endl;
        }
    }

    ofstream vehiclesNewFile(m_backup_vehicles);
    vehiclesNewFile << vehicles.toStyledString();
    vehiclesNewFile.close();
}

void GarageManager::BackupVehicleDelete(unsigned long license_id)
{
    ifstream jsonFile(m_backup_vehicles);
    Json::Value vehicles(Json::arrayValue);
    jsonFile >> vehicles;
    Json::Value new_array(Json::arrayValue);

    // find the vehicle in the dictionary
    for (Json::Value::ArrayIndex i = 0; i < vehicles.size(); ++i)
    {
        if (license_id != vehicles[i]["license_id"].asInt())
        {
            new_array.append(vehicles[i]);
        }
    }

    ofstream vehiclesNewFile(m_backup_vehicles);
    vehiclesNewFile << new_array.toStyledString();
    vehiclesNewFile.close();
}

void GarageManager::BackupUpdateProfit()
{
    Json::Value profits;
    profits["total profit"] = m_total_profits;
    ofstream vehiclesNewFile(m_backup_profits);
    vehiclesNewFile << profits.toStyledString();
    vehiclesNewFile.close();
}

GarageManager::~GarageManager()
{
    //// TODO: delete vehicles
}