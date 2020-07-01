#include <iostream>
#include <vector>


class Road {
public:
    double length();
    int speed();
};

class Car {
public:
    virtual double getFuelConsumption(int speed) const = 0;
    virtual ~Car(){}
};

double getPetrol(std::vector<Road> roads, const Car& car) {
    double consumption;
    for (std::vector<Road>::iterator it = roads.begin() ; it != roads.end() ; ++it) {
        consumption += car.getFuelConsumption(it->speed());
    }
    return consumption;
}
