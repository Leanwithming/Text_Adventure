#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include <thread>
#include <future>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include "GameObject.h"
#include "FoodObject.h"
#include <sstream>

using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */


void initGameObjects(){
    auto * o1 = new GameObject(&o1sName, &o1key, &o1desc);
    auto * o2 = new FoodObject(&o2sName, &o2key, &o2desc, -100);
    auto * o3 = new GameObject(&o3sName, &o3key, &o3desc);
    auto * o4 = new FoodObject(&o4sName,&o4key,&o4desc, 20);
    GameObject::addGameObject(o1);
    GameObject::addGameObject(o2);
    GameObject::addGameObject(o3);
    GameObject::addGameObject(o4);
}

void initRooms() {
    std::list<GameObject*>::iterator Iter_O;
    Iter_O = GameObject::gameObjects.begin();
    auto * r2 = new Room(&r2name, &r2desc);
    auto * r1 = new Room(&r1name, &r1desc);
    int i = 0;
    for(;Iter_O != GameObject::gameObjects.end(); ++Iter_O){
        if(i == 0 || i == 2){
            r1->addGameObjects(*Iter_O);
        }
        if(i == 1 || i == 3){
            r2->addGameObjects(*Iter_O);
        }
        i++;
    }
//    auto * r3 = new Room(&r3name, &r3desc);

//    Room::addRoom(r3);
//    0 represent north, 1 represent south, 2 represent west, 3 represent east.
    r1->setTargetRoom(0, r2);
    r2->setTargetRoom(1, r1);
    Room::addRoom(r1);
    Room::addRoom(r2);
//    r2->setTargetRoom(3, r3);
//    r3->setTargetRoom(2, r2);
}


int getObject(string::size_type endOfVerb, string commandBuffer, const string command2[10]){
    std::stringstream stringStream;
    stringStream<<commandBuffer;
    std::string firstBuffer;
    std::string secondBuffer;
    stringStream>>firstBuffer;
    stringStream>>secondBuffer;
    if(secondBuffer.empty()){
        return 0;
    }
    if((currentState->getCurrentRoom()->checkExist(secondBuffer))==0){
        wrapOut(&message7);
        std::cout<<secondBuffer<<" ";
        wrapOut(&message8);
        wrapEndPara();
        return 1;
    }
    if((currentState->checkExist(secondBuffer))==1){
        wrapOut(&message9);
        std::cout<<secondBuffer<<" ";
        wrapOut(&message10);
        wrapEndPara();
        return 1;
    }
    endOfVerb = static_cast<uint8_t>(secondBuffer.find(' '));
    for(int j = 0; j < 4; j++){
        if(secondBuffer.compare(0,endOfVerb, command2[j]) == 0){
            int objectNum = currentState->getCurrentRoom()->getNums();
            for(int k = 0; k < objectNum; k++){
                if ((currentState->getCurrentRoom()->getGameObjects(k)->getKey()->compare(secondBuffer)) == 0){
                    currentState->addInventory(currentState->getCurrentRoom()->getGameObjects(k));
                    wrapOut(&message5);
                    wrapOut(currentState->getCurrentRoom()->getGameObjects(k)->getShortName());
                    wrapOut(&message6);
                    wrapEndPara();
                    currentState->getCurrentRoom()->deleteGameObject(k);
                    return 1;
                }
            }
        }
    }
}

int dropInventoryObject(string::size_type endOfVerb, string commandBuffer, const string command2[10]){
    std::stringstream stringStream;
    stringStream<<commandBuffer;
    std::string firstBuffer;
    std::string secondBuffer;
    stringStream>>firstBuffer;
    stringStream>>secondBuffer;
    if(secondBuffer.empty()){
        return 0;
    }
    if((currentState->checkExist(secondBuffer))==0){
        wrapOut(&message7);
        std::cout<<secondBuffer<<" ";
        wrapOut(&message10);
        wrapEndPara();
        return 1;
    }
    if((currentState->getCurrentRoom()->checkExist(secondBuffer))==1){
        wrapOut(&message11);
        std::cout<<secondBuffer<<" ";
        wrapOut(&message12);
        wrapEndPara();
        return 1;
    }
    endOfVerb = static_cast<uint8_t>(secondBuffer.find(' '));
    for(int j = 0; j < 4; j++){
        if(secondBuffer.compare(0,endOfVerb, command2[j]) == 0){
            int objectNum = currentState->getNums();
            for(int k = 0; k < objectNum; k++){
                if ((currentState->getInventoryObjects(k)->getKey()->compare(secondBuffer)) == 0){
                    currentState->getCurrentRoom()->addGameObjects(currentState->getInventoryObjects(k));
                    wrapOut(&message13);
                    wrapOut(currentState->getInventoryObjects(k)->getShortName());
                    wrapOut(&message14);
                    wrapEndPara();
                    currentState->deleteInventoryObject(k);
                    return 1;
                }
            }
        }
    }
}

int examObject(string::size_type endOfVerb, string commandBuffer, const string command2[10]){
    std::stringstream stringStream;
    stringStream<<commandBuffer;
    std::string firstBuffer;
    std::string secondBuffer;
    stringStream>>firstBuffer;
    stringStream>>secondBuffer;
    if(secondBuffer.empty()){
        return 0;
    }
    if((currentState->checkExist(secondBuffer))==0){
        wrapOut(&message16);
        std::cout<<secondBuffer<<" ";
        wrapOut(&message10);
        wrapEndPara();
        return 1;
    }
    endOfVerb = static_cast<uint8_t>(secondBuffer.find(' '));
    for(int j = 0; j < 4; j++){
        if(secondBuffer.compare(0,endOfVerb, command2[j]) == 0){
            int objectNum = currentState->getNums();
            for(int k = 0; k < objectNum; k++){
                if ((currentState->getInventoryObjects(k)->getKey()->compare(secondBuffer)) == 0){
                    wrapOut(currentState->getInventoryObjects(k)->getDescription());
                    wrapEndPara();
                    return 1;
                }
            }
        }
    }
}

int eatObject(string::size_type endOfVerb, string commandBuffer, const string command2[10]){
    std::stringstream stringStream;
    stringStream<<commandBuffer;
    std::string firstBuffer;
    std::string secondBuffer;
    stringStream>>firstBuffer;
    stringStream>>secondBuffer;
    if(secondBuffer.empty()){
        return 0;
    }
    if((currentState->checkExist(secondBuffer))==0){
        wrapOut(&message16);
        std::cout<<secondBuffer<<" ";
        wrapOut(&message10);
        wrapEndPara();
        return 1;
    }
    endOfVerb = static_cast<uint8_t>(secondBuffer.find(' '));
    for(int j = 0; j < 4; j++){
        if(secondBuffer.compare(0,endOfVerb, command2[j]) == 0){
            int objectNum = currentState->getNums();
            for(int k = 0; k < objectNum; k++){
                if ((currentState->getInventoryObjects(k)->getKey()->compare(secondBuffer)) == 0){
                    int oStrength = currentState->getInventoryObjects(k)->getEnergy();
                    if(oStrength == 999){
                        wrapOut(&message20);
                        wrapEndPara();
                        return 1;
                    }
                    int pStrength = *(currentState->getStrength());
                    currentState->setStrength(pStrength+=oStrength);
                    wrapOut(&message17);
                    wrapOut(currentState->getInventoryObjects(k)->getShortName());
                    wrapOut(&message18);
                    wrapEndPara();
                    currentState->deleteInventoryObject(k);
                    wrapOut(&message2);
                    std::cout<<*currentState->getStrength()<<std::endl;
                    wrapEndPara();
                    if(*(currentState->getStrength()) <= 0){
                        wrapOut(&message3);
                        wrapEndPara();
                        return 2;
                    }
                    return 1;
                }
            }
        }
    }
}

void timerThread(int *strength){
    int i = 0;
    while(*strength > 0){
        std::this_thread::sleep_for(std::chrono::seconds(60));
        --*strength;
        i += 5;
        wrapEndPara();
        wrapOut(&message2);
        std::cout<<*currentState->getStrength()<<std::endl;
        wrapOut(&message22);
        std::cout<< i <<std::endl;
        wrapEndPara();
        std::cout<<">";
    }
    wrapEndPara();
    wrapOut(&message3);
    wrapEndPara();
    exit(-1);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
}


/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;
    const string command1[20] {
        "north","n","south","s","west","w","east","e"
    };
    const string command2[10]{
        "swd", "wtr", "pap","chi"
    };
    wrapOut(&message2);
    std::cout<<*currentState->getStrength()<<std::endl;
    wrapEndPara();
    std::thread timer(timerThread, currentState->getStrength());

    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);
        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        string::size_type endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));
        /* We could copy the verb to another string but there's no reason to, we'll just compare it in place. */
        /* Command to go north. */
        for (int i = 0; i < 8; i++) {
            if (commandBuffer.compare(0, endOfVerb, command1[i]) == 0) {
                commandOk = true; /* Confirm command has been handled */
                //0, 1 represent north, 2, 3 represent south, 4, 5 represent west, 6, 7 represent east.
                Room *targetRoom = currentState->getCurrentRoom()->getTargetRoom(i / 2);
                if (targetRoom == nullptr) { /* there isn't */
                    wrapOut(&badExit);      /* Output the "can't go there" message */
                    wrapEndPara();
                } else {                    /* There is */
                    currentState->goTo(targetRoom);/* Update state to that room - this will also describe it */
                }
            }
        }
        if (commandBuffer.compare(0, endOfVerb, "get") == 0) {
            int result = getObject(endOfVerb, commandBuffer, command2);
            switch (result) {
                case 0:
                    wrapOut(&badCommand2);
                    wrapEndPara();
                    commandOk = true;
                    break;
                case 1:
                    commandOk = true;
                    break;
            }
        }

        if (commandBuffer.compare(0, endOfVerb, "drop") == 0) {
            int result = dropInventoryObject(endOfVerb, commandBuffer, command2);
            switch (result) {
                case 0:
                    wrapOut(&badCommand2);
                    wrapEndPara();
                    commandOk = true;
                    break;
                case 1:
                    commandOk = true;
                    break;
            }
        }

        if ((commandBuffer.compare(0, endOfVerb, "examine")) == 0) {
            int result = examObject(endOfVerb, commandBuffer, command2);
            switch (result) {
                case 0:
                    wrapOut(&badCommand2);
                    wrapEndPara();
                    commandOk = true;
                    break;
                case 1:
                    commandOk = true;
                    break;
            }
        }

        if ((commandBuffer.compare(0, endOfVerb, "inventory")) == 0) {
            currentState->describeInventory();
            commandOk = true;
        }

        if ((commandBuffer.compare(0, endOfVerb, "eat")) == 0) {
            int result = eatObject(endOfVerb, commandBuffer, command2);
            switch (result) {
                case 0:
                    wrapOut(&badCommand2);
                    wrapEndPara();
                    commandOk = true;
                    break;
                case 1:
                    commandOk = true;
                    break;
                case 2:
                    commandOk = true;
                    gameOver = true;
                    break;
            }
        }

        /* Quit command */
        if ((commandBuffer.compare(0, endOfVerb, "quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if (!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
    timer.detach();
}


int main() {
    initWordWrap();
    initGameObjects();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}