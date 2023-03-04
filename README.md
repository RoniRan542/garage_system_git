# garage_system_git

In order to run these files you must install the jsonCpp lib : 

in linux terminal: 
```linux 
sudo apt-get install libjsoncpp-dev
```

When the jsonCpp library is installed run this in the command-line:

```linux 
g++ test_garage.cpp garage.cpp garage_system.cpp user.cpp vehicle.cpp -o garage_system.out -ljsoncpp

```

and run the execution file:

```linux
garage_system.out
```
