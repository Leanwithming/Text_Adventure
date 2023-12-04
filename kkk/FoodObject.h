#ifndef TEXTADV_FOODOBJECT_H
#define TEXTADV_FOODOBJECT_H
#include "GameObject.h"

class FoodObject : public GameObject{
    int energy;
public:
    FoodObject(const string* sName, const string* key, const string* desc,int energy);
    int getEnergy();
};






#endif //TEXTADV_FOODOBJECT_H
