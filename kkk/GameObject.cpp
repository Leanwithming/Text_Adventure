#include <iostream>
#include "GameObject.h"
#include <string>

using std::string;
std::list<GameObject*> GameObject::gameObjects;

GameObject::GameObject(const string* sName, const string* key, const string* desc) :
        shortName(sName), keyWord(key), description(desc){}


const string* GameObject::getShortName(){
    return this->shortName;
}

void GameObject::addGameObject(GameObject *gameObject) {
    GameObject::gameObjects.push_back(gameObject);
}

GameObject* GameObject::addGameObject(const string* sName, const string* key, const string* desc) {
    auto *newGameObject = new GameObject(sName, key, desc);
    GameObject::gameObjects.push_back(newGameObject);
    return newGameObject;
}

const string* GameObject::getKey() {
    return this->keyWord;
}

const string* GameObject::getDescription() {
    return this->description;
}

int GameObject::getEnergy() {
    return 999;
}