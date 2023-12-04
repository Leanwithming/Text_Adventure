#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H
#include "Room.h"
#include "GameObject.h"
class State {
    Room *currentRoom;
    std::list<GameObject*> inventory;
    std::list<GameObject*>::iterator Iter_O;
    int* strength = new int(3);
public:
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    Room* getCurrentRoom() const;
    int* getStrength () const;
    void setStrength(int num);
    void addInventory(GameObject* gameObject);
    int checkExist(string keyName);
    int getNums();
    void deleteInventoryObject(int deletePos);
    GameObject* getInventoryObjects(int pos);
    void describeInventory();
};


#endif //TEXTADV_STATE_H
