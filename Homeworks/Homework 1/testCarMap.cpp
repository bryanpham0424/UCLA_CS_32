#include "CarMap.h"
#include <cassert>


int main() {
	CarMap CMtest;
	CMtest.addCar("ABC1234");
	CMtest.print();
	CMtest.addCar("21YBNM2");
	CMtest.addCar("56MYBN6");
	CMtest.drive("ABC1234", 40000);
	CMtest.miles("ABC1234");
	CMtest.fleetSize();
	CMtest.print();
}