
#include <iostream>
#include <set>
#include <sstream>
#include <cstring>
#include <vector>

#include "garage.hpp"
#include "vehicle.hpp"

using namespace std;
int main()
{

    string input;
    Garage my_garage("users.json", "vehicles.json", "profit.json");
    my_garage.CreateUser("Aviya", "Assistant manager", 28377191);
    my_garage.CreateUser("Harry", "Manager", 25748333);
    my_garage.CreateUser("Roni", "Mechanic", 36850600);
    User *aviya = my_garage.GetUser(28377191);
    User *harry = my_garage.GetUser(25748333);
    cout << aviya->GetName() << ", " << aviya->GetPosition() << endl;
    cout << harry->GetName() << ", " << harry->GetPosition() << endl;
    VehicleFactory myFactory;

    while (true)
    {
        cout << "\n********** GARAGE-SYSTEM ***********\n";
        cout << "Enter a command (type 'exit' to quit): ";
        getline(cin, input);

        if (input == "exit")
        {
            break;
        }

        stringstream sstr(input);
        string arg;
        getline(sstr, arg, ',');

        if (strcmp(arg.c_str(), "add") == 0)
        {
            cout << "\n**********ADDING-VEHICLE***********\n";
            cout
                << "You entered: " << input << endl;
            vector<string> args(6);
            int i = 0;
            while (getline(sstr, arg, ','))
            {
                args[i] = arg;
                ++i;
            }

            Vehicle *vehicle = myFactory.CreateVehicle((Type)stoul(args[0], nullptr),
                                                       stoul(args[1], nullptr), args[2], stoul(args[3], nullptr),
                                                       (bool)stoul(args[4], nullptr), stoul(args[5], nullptr));
            aviya->GetSystem()->InsertV(vehicle);
        }
        else if (strcmp(arg.c_str(), "getall") == 0)
        {
            cout << "\n**********VEHICLES-LIST***********\n";
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
        }
        else if (strcmp(arg.c_str(), "process") == 0)
        {
            cout << "\n**********CHANGING STATUS***********\n";
            vector<string> args(2);
            int i = 0;
            while (getline(sstr, arg, ','))
            {
                args[i] = arg;
                ++i;
            }

            harry->GetSystem()->ChangeVehicleStatus(stoul(args[0], nullptr), (Status)stoul(args[1], nullptr));
            cout << "A vehicle is in process or released." << endl;
        }
        else if (strcmp(arg.c_str(), "profit") == 0)
        {
            cout << "\n**********PROFIT***********\n";

            cout << harry->GetSystem()->GetTotalProfit() << endl;
        }
        else
        {
            cout << "\n**********--Error--***********\n";
        }
    }

    cout << "************************\n\n";
    std::cout << "Exiting program." << std::endl;

    return 0;
}
