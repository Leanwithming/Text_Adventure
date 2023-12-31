


#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include <string>
#include <forward_list>
#include <list>
#include "GameObject.h"
#include "strings.h"


using std::string;

/**
 * Represents a room (accessible location in the game).
 */
class Room {
    /**
     * Short name used as a header.
     */
    const string* name;
    /**
     * Full description of the room.
     */
    const string* description;
    Room* targets[4];
    std::list<GameObject*> gameobjects;
    std::list<GameObject*>::iterator Iter_O;
    /**
     * Pointer to room that is north of this one.
     */
    //Room* north;
    //Room* south;
    //Room* west;
    //Room* east;
public:
    /**
     * Constructs a new Room.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    Room(const string *_name, const string *_desc);

    /**
     * Removes a destroyed room from the global list if it's there.
     */
    ~Room();

    /**
     * Outputs the name and description of the room
     * in standard format.
     */
    void describe();

    /**
     * List storing all rooms that have been registered via addRoom().
     */

    static std::list<Room*> rooms;


    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static Room* addRoom(const string* _name, const string* _desc);
    static void addRoom(Room* room);
    void addGameObjects(GameObject *gameObject);
    GameObject* getGameObjects(int pos);
    Room* getTargetRoom(int direction) const;
    void setTargetRoom(int direction, Room* targetRoom);
    int getNums();
    void deleteGameObject(int deletePos);
    int checkExist(string keyName);
//    Room* getNorth() const;
//    void setNorth(Room* _north);
//    Room* getSouth() const;
//    void setSouth(Room* _south);
//    Room* getWest() const;
//    void setWest(Room* _west);
//    Room* getEast() const;
//    void setEast(Room* _east);
};

#endif //TEXTADV_ROOM_H
