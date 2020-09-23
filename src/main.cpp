//
//  main.cpp
//  Shortest_path
//
//  Created by Daniel  Fernandez on 10/19/19.
//  Copyright © 2019 Daniel  Fernandez. All rights reserved.
//

#include <iostream>
#include <string>
#include "Map.hpp"

using namespace std;

//data file
const string DATA_FILE = "./data.map";

//map object
Map map;

//overload operator to print directions
ostream& operator<< (ostream &os, Map::Direction &d);

//type of location:
//START means a starting point
//DESTINATION means the arriving point
enum SELECT_TYPE {START, DESTINATION};

//clear the input buffer
void clearInput();

//clear the screen
//the clear screen command can be changed to system("cls"); for windows
void clearScreen();

//main menu
void mainMenu();

//Prompt the user the location finder
//returns an integer, which is the location of the selected city in the map list
int selectPlace(SELECT_TYPE type);

//print the list of directions from a to b
void printDirections(int a, int b);

int main(int argc, const char * argv[]) {

    //check is the file was loaded
    if(!map.load(DATA_FILE)) {
        cout << "There was an error loading the file." << endl;
        return 0;
    }
    
    //user input
    int input = 0;
    
    do {
        clearScreen();
        mainMenu();
        cout << "[SELECT AN OPTION]: ";
        cin >> input;
        clearInput();
        
        //a and b are the variables to hold the location of the places in the map list
        int a = -1, b = -1;
        
        switch (input) {
            case 1:
                //directions
                clearScreen();
                do {
                    //select the starting point
                    a = selectPlace(START);
                    clearScreen();
                } while (a == -1);
                
                do {
                    //select the destination point
                    b = selectPlace(DESTINATION);
                    clearScreen();
                } while (a == -1);
                
                //print the directions from the selected cities
                printDirections(a, b);
                clearScreen();
                
                break;
                
            case 2:
                //print nodes
                map.printNodes();
                cout << "Press [ENTER] to continue..." << endl;
                cin.get();
                break;
                
            case 3:
                //exit
                break;
                
            default:
                cout << "Bad input. Press [ENTER] to continue..." << endl;
                cin.get();
                break;
        }
        
    } while (input != 3);
    
    return 0;
}

ostream& operator<< (ostream &os, Map::Direction &d) {
    os << "Turn into " << d.road << " at " << d.position << " and head " << d.heading << " towards " << d.destination << " for " << d.distance << " miles. ";
    return os;
}

void clearInput() {
    cin.clear();
    cin.ignore(10, '\n');
}
void clearScreen() {
    system("clear");
}

void mainMenu() {
    cout << "GPS MENU" << endl;
    cout << "1- Get directions" << endl;
    cout << "2- Print places in database" << endl;
    cout << "3- Exit" << endl << endl;
}

int selectPlace(SELECT_TYPE type) {
    
    //variable to hold the user input
    string input;
    
    //change the command base on the type of place being searched
    if(type)
        cout << "Search a destination place: ";
    else
        cout << "Search a starting place: ";
    cin >> input;
    clearInput();
    
    //get the list of places which name is similar to the typed word
    unorderedLinkedList<Map::Place> places = map.find(input);
    if(places.size() == 0) {
        //if size is 0, no results were found
        cout << "No results. Press [ENTER] to continue..." << endl;
        cin.get();
        return -1;
    }
    else {
        //results were found
        cout << "Results: " << endl;
        
        //option number for the user to select a city
        int counter = 1;
        for (Map::Place p : places) {
            //print the result
            cout << counter++ << "- " << p.name << endl;
        }
        
        //select a place
        cout << endl << "Select a place or enter 0 to search again: ";
        int num;
        do {
            //read the selected location
            cin >> num;
            clearInput();
            
            //validate the number entered
            if(num < 0 || num > places.size())
                cout << "Invalid input. Try again: ";
            
            //0 means search again, so do a recursive call and return whatever the next search returns
            if(num == 0)
                return selectPlace(type);
            
        } while (num < 0 || num > places.size());
        
        //selected num-1, since the locations in memory start at 0
        cout << "You have selected " << places[num-1].name << ". Press [ENTER] to continue..." << endl;
        cin.get();
        
        //return the location in the map list of the selected city
        return places[num-1].location;
    }
}
void printDirections(int a, int b) {
    
    unorderedLinkedList<Map::Direction> directions = map.getDirections(a, b);
    
    cout << "--------------------------------------" << endl;
    for(Map::Direction d : directions)
        cout << d << endl;
    cout << endl << "Total distance: " << map.distance(a, b) << " miles." << endl;
    cout << "--------------------------------------" << endl;
    cout << "Press [ENTER] to continue..." << endl;
    cin.get();
}
