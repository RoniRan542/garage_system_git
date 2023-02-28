#include <fstream>
#include <iostream>
#include <list>
#include <unordered_map>
#include <set>

#include "vehicle.hpp"

using namespace std;

struct vehicle_year_comp
{
    bool operator()(const Vehicle *lhs, const Vehicle *rhs) const
    {
        return lhs->GetYear() < rhs->GetYear();
    }
};

class GarageManager
{
public:
    GarageManager(string backup_vehicles, string backup_profits);
    void InsertV(Vehicle *vehicle);
    void ChangeVehicleStatus(unsigned long license_id, Status new_status);
    multiset<Vehicle *, vehicle_year_comp> GetVehicles();
    size_t GetTotalProfit();
    void BackupVehicleAdd(Vehicle *vehicle);
    void BackupUpdateVehicle(Vehicle *vehicle);
    void BackupVehicleDelete(unsigned long license_id);
    void BackupUpdateProfit();

    ~GarageManager();

private:
    string m_backup_vehicles;
    string m_backup_profits;
    unordered_map<unsigned long, Vehicle *> license_ids;
    multiset<Vehicle *, vehicle_year_comp> vehicles;
    size_t m_total_profits;
};
