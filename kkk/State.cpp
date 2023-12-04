#include "State.h"

/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    this->currentRoom->describe();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(Room *startRoom) : currentRoom(startRoom) {};

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(Room *target) {
    this->currentRoom = target;
    this->announceLoc();
}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
Room* State::getCurrentRoom() const {
    return this->currentRoom;
}

int* State::getStrength() const{
    return this->strength;
}
void State::setStrength(int num) {
    *strength = num;
    if(*strength > 100){
        *strength = 100;
        wrapOut(&message21);
        wrapEndPara();
    }
}

void State::addInventory(GameObject* gameObject) {
    inventory.push_back(gameObject);
}

int State::checkExist(string keyName) {
    Iter_O = inventory.begin();
    for(; Iter_O != inventory.end(); Iter_O++){
        GameObject* doing = *Iter_O;
        if((doing->getKey()->compare(keyName))==0){
            return 1;
        }
    }
    return 0;
}

int State::getNums() {
    Iter_O = inventory.begin();
    int i = 0;
    for(; Iter_O != inventory.end(); Iter_O++){
        i++;
    }
    return i;
}

void State::deleteInventoryObject(int deletePos) {
    Iter_O = inventory.begin();
    int i = 0;
    for(; Iter_O != inventory.end(); ++Iter_O){
        if(i == deletePos){
            inventory.remove(*Iter_O);
            break;
        }
        i++;
    }
}

GameObject* State::getInventoryObjects(int pos) {
    Iter_O = inventory.begin();
    int i = 0;
    for(; Iter_O != inventory.end(); ++Iter_O){
        if(i == pos){
            return(*Iter_O);
        }
        i++;
    }
}

void State::describeInventory(){
    Iter_O = inventory.begin();
    if(*Iter_O != nullptr){
        wrapOut(&message15);
        wrapEndPara();
        for(; Iter_O != inventory.end(); ++Iter_O){
            GameObject* doing = *Iter_O;
            wrapOut(doing->getShortName());
            std::list<GameObject*>::iterator Iter_O1 = Iter_O;
            if(++Iter_O1 != inventory.end()){
                wrapOut(&message4);
            }
        }
        wrapEndPara();
    }else{
        wrapOut(&message19);
        wrapEndPara();
    }
}