#include <iostream>
#include "Room.h"
#include "wordwrap.h"

/**
 * Stores a static list of all rooms.
 */
std::list<Room*> Room::rooms;

/**
 * Room default constructor.
 * @param _name Room's name.
 * @param _desc Room's description.
 */
Room::Room(const string *_name, const string *_desc) :
        name(_name), description(_desc), targets{nullptr, nullptr, nullptr, nullptr} {};


/**
 * Remove destroyed rooms from the static list.
 */
Room::~Room() {
    Room::rooms.remove(this);
}

/**
 * Prints the description of a room (the name and long description)
 */
void Room::describe(){
    Iter_O = gameobjects.begin();
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();
    if(*Iter_O != nullptr){
        wrapOut(&message1);
        wrapEndPara();
        for(; Iter_O != gameobjects.end(); ++Iter_O){
            GameObject* doing = *Iter_O;
            wrapOut(doing->getShortName());
            std::list<GameObject*>::iterator Iter_O1 = Iter_O;
            if(++Iter_O1 != gameobjects.end()){
                wrapOut(&message4);
            }
        }
        wrapEndPara();
    }
}

void Room::addGameObjects(GameObject *gameObject){
    gameobjects.push_back(gameObject);
}

GameObject* Room::getGameObjects(int pos) {
    Iter_O = gameobjects.begin();
    int i = 0;
    for(; Iter_O != gameobjects.end(); ++Iter_O){
        if(i == pos){
            return(*Iter_O);
        }
        i++;
    }
}

/**
 * Statically creates a room and then adds it to the global list.
 * @param _name Name for the new room.
 * @param _desc Description for the new room.
 * @return A pointer to the newly created room.
 */
Room* Room::addRoom(const string* _name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);
    return newRoom;
}
/**
 * Adds an existing room to the static list.
 * @param room Pointer to the room to add.
 * @return
 */
void Room::addRoom(Room* room) {
    Room::rooms.push_back(room);
}

Room* Room::getTargetRoom(int direction) const {
    return this->targets[direction];
}

void Room::setTargetRoom(int direction, Room* targetRoom){
    this->targets[direction] = targetRoom;
}

int Room::getNums() {
    Iter_O = gameobjects.begin();
    int i = 0;
    for(; Iter_O != gameobjects.end(); ++Iter_O){
        i++;
    }
    return i;
}

void Room::deleteGameObject(int deletePos) {
    Iter_O = gameobjects.begin();
    int i = 0;
    for(; Iter_O != gameobjects.end(); ++Iter_O){
        if(i == deletePos){
            gameobjects.remove(*Iter_O);
            break;
        }
        i++;
    }
}

int Room::checkExist(std::string keyName) {
    Iter_O = gameobjects.begin();
    for(; Iter_O != gameobjects.end(); Iter_O++){
        GameObject* doing = *Iter_O;
        if((doing->getKey()->compare(keyName))==0){
            return 1;
        }
    }
    return 0;
}
/**
 * Gets the north exit of a room.
 * @return The room that is north of this one, or NULL if there is no exit.
 */
//Room* Room::getNorth() const {
//    return this->north;
//}

/**
 * Sets the north exit of a room.
 * @param _north Pointer to the room to be north of this one.
 */

//void Room::setNorth(Room* _north) {
//    this->north = _north;
//}
//
//Room* Room::getSouth() const {
//    return this->south;
//}
//
//void Room::setSouth(Room* _south) {
//    this->south = _south;
//}
//
//Room* Room::getWest() const {
//    return this->west;
//}
//
//void Room::setWest(Room* _west) {
//    this->west = _west;
//}
//
//Room* Room::getEast() const {
//    return this->east;
//}
//
//void Room::setEast(Room* _east) {
//    this->east = _east;
//}