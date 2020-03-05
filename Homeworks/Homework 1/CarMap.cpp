#include "CarMap.h"

CarMap::CarMap()
{
}

bool CarMap::addCar(std::string license)
{

	return CarMap_m.insert(license, 0);
	
}

double CarMap::miles(std::string license) const
{
	double miles = -1;
	CarMap_m.get(license, miles);
	return miles;
}

bool CarMap::drive(std::string license, double distance)
{
	if (!CarMap_m.contains(license)) {
		return false;
	}
	return CarMap_m.insertOrUpdate(license, distance);
}

int CarMap::fleetSize() const
{
	return CarMap_m.size();
}

void CarMap::print() const
{
	for (int i = 0; i < CarMap_m.size(); i++) {
		std::string k;
		double v;
		CarMap_m.get(i, k, v);
		std::cout << k << ' ' << v << ' ';
	}
}
