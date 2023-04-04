# garage_system_git

In order to run these files you must install the jsonCpp lib :

in linux terminal:

```linux
sudo apt-get install libjsoncpp-dev
```

When the jsonCpp library is installed run this in the command-line:

```linux
g++ ui_test_garage.cpp garage.cpp garage_system.cpp user.cpp vehicle.cpp -o garage_system.out -ljsoncpp

```

and run the execution file:

```linux
garage_system.out
```

## GARAGE-SYSTEM BASIC MANUAL

After the system go up you can execute the following operations:

- Adding a vehicle
- Updating vehicle's status
- Presenting all vehicles(in detailes) currentely in the system
- Presenting current profit of the garage
- You can always exit the program by the 'exit' command

### Adding a vehicle:

There are three types of vehicles you can register into the system:
(0) CAR
(1) MOTORCYCLE
(2) TRUCK

For registering a new vehicle you have to use this specific format:

```linux
add,type-of-vehicle(0/1/2),license-number,problem-description,year-of-manufacturing,extra-sit(if eligible),weight(if eligible).
```

for exmaple, for a suzuky swift car with a flat tier:

```linux
add,0,9804763,suzuky swift with a flat tier,2008,0,0
```

Notice that there aren't spaces between commas and parameters.
Also notice that the last two parameters are set to 0 because they are not eligible in a car.
The extara sit is eligible only for the motorcycle type (0 - no extra sit, 1 - extra sit exist)
The weight parameter is eligible only for trucks (put 0 if not eligible)

### Updating vehicle's status

There are three states for a vehicle in the garage:
(0) NEW
(1) IN_PROCESS
(2) REALEASED

A vehicle that was just registered is in the NEW state. In order to change the state use the update command like this:

```linux
update,license-number,1/2 (1: in-process, 2: released)
```

for example in order to change a vehicle to be 'In process':

```linux
update,9804763,1
```

### To present all current vehicles use this command:

```linux
getall
```

### To present current profit of the garage use this command:

```linux
profit
```
