#include "FoodObject.h"

FoodObject::FoodObject(const string* sName, const string* key, const string* desc,int energy):
        GameObject(sName,key, desc), energy(energy) {};

int FoodObject::getEnergy() {
    return this->energy;
}