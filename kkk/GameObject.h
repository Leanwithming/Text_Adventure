//
// Created by skarn on 2023/11/8.
//

#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H
#include <string>
#include <list>
#include "wordwrap.h"

using std::string;

class GameObject{
    const string* shortName;
    const string* description;
    const string* keyWord;
public:
    static std::list<GameObject*> gameObjects;
    GameObject(const string* sName, const string* key, const string* desc);
    static void addGameObject(GameObject *gameObject);
    static GameObject* addGameObject(const string* sName, const string* key, const string* desc);
    const string* getShortName();
    const string* getKey();
    const string* getDescription();
    virtual int getEnergy();
};

#endif //TEXTADV_GAMEOBJECT_H