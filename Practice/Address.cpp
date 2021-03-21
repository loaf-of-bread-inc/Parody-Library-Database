//
//  Address.cpp
//  Practice
//
//  Created by Jaden  Andrews  on 3/18/21.
//

#include <stdio.h>
#include <iostream>

using namespace std;

class Address
{
private:
    int sType;
    int streetNum;
    string streetName;
    string streetType[6] {"Dr", "Rd", "St", "Ln", "Blvd", "Ave"};
public:
    Address(int streetNum = 0, string streetName = "", int sType = 0)
    {
        this->streetNum = streetNum;
        this->streetName = streetName;
        this->sType = sType;
    }
    int read_streetNum ()
    {
        return this->streetNum;
    }
    string read_address ()
    {
        return to_string(streetNum) + " " + streetName + " " + streetType[sType];
    }
    void write_streetNum (int streetNum)
    {
        this->streetNum = streetNum;
    }
    void write_address (int streetNum, string streetName, int sType)
    {
        this->streetNum = streetNum;
        this->streetName = streetName;
        this->sType = sType;
    }
};
