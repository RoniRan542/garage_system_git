/*
    TODO:In order to run these files you must install the jsonCpp lib: sudo apt-get install libjsoncpp-dev
 */

#include <iostream>
#include <set>
#include "garage.hpp"
#include "vehicle.hpp"

using namespace std;
int main()
{
    Garage my_garage("users.json", "vehicles.json", "profit.json");
    my_garage.CreateUser("Aviya", "Assistant manager", 28377191);
    my_garage.CreateUser("Harry", "Manager", 25748333);
    my_garage.CreateUser("Roni", "Mechanic", 36850600);

    User *aviya = my_garage.GetUser(28377191);
    User *harry = my_garage.GetUser(25748333);
    cout << aviya->GetName() << ", " << aviya->GetPosition() << endl;
    cout << harry->GetName() << ", " << harry->GetPosition() << endl;

    cout << "************************\n\n";
    Vehicle *car1 = new Car(9804763, "Black Suzuki swift", 2008);
    Vehicle *car2 = new Car(9804333, "White Suzuki baleno", 1999);
    Vehicle *car3 = new Car(8219197, "Grean Mercedece", 2011);
    Vehicle *motorcycle1 = new Motorcycle(7775554, "Suzuki Red", 2023, false);
    Vehicle *truck1 = new Truck(5555151, "Semitrayler with flat tire", 2005, 3599);
    Vehicle *truck2 = new Truck(5447151, "Ford: problem with brakes with flat tire", 2002, 3200);

    aviya->GetSystem()->InsertV(car1);
    aviya->GetSystem()->InsertV(car2);
    aviya->GetSystem()->InsertV(car3);
    aviya->GetSystem()->InsertV(motorcycle1);
    aviya->GetSystem()->InsertV(truck1);
    aviya->GetSystem()->InsertV(truck2);

    // After insersion
    multiset<Vehicle *, vehicle_year_comp> vehicles = aviya->GetSystem()->GetVehicles();
    multiset<Vehicle *, vehicle_year_comp>::iterator iter = vehicles.begin();
    for (; iter != vehicles.end(); iter++)
    {
        Vehicle *v = *(iter);
        cout << v->GetStatus() << endl;
        cout << v->GetType() << endl;
        cout << v->DescribeVehicleProblem() << endl;
        cout << "------------" << endl;
    }

    cout << "************************\n\n";
    // Vehicles "In-process"
    harry->GetSystem()->ChangeVehicleStatus(5555151, Status::IN_PROCESS);
    harry->GetSystem()->ChangeVehicleStatus(9804763, Status::IN_PROCESS);
    harry->GetSystem()->ChangeVehicleStatus(8219197, Status::IN_PROCESS);

    // Vehicles "In-process"
    vehicles = harry->GetSystem()->GetVehicles();
    iter = vehicles.begin();
    for (; iter != vehicles.end(); iter++)
    {
        Vehicle *v = *(iter);
        cout << v->GetStatus() << endl;
        cout << v->GetType() << endl;
        cout << v->DescribeVehicleProblem() << endl;
        cout << "------------" << endl;
    }

    cout << "************************\n\n";

    // Vehicles Release
    harry->GetSystem()->ChangeVehicleStatus(5555151, Status::REALEASED);
    harry->GetSystem()->ChangeVehicleStatus(9804763, Status::REALEASED);
    harry->GetSystem()->ChangeVehicleStatus(8219197, Status::REALEASED);

    vehicles = harry->GetSystem()->GetVehicles();
    iter = vehicles.begin();
    for (; iter != vehicles.end(); iter++)
    {
        Vehicle *v = *(iter);
        cout << v->GetStatus() << endl;
        cout << v->GetType() << endl;
        cout << v->DescribeVehicleProblem() << endl;
        cout << "------------" << endl;
    }

    cout << "************************\n\n";
    // Check profit
    cout << harry->GetSystem()->GetTotalProfit() << endl;

    cout << "\n\n************************\n\n";
    // Delete user
    my_garage.DeleteUser(28377191);

    return 0;
}
