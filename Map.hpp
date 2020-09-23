//
//  Map.hpp
//  Shortest_path
//
//  Created by Daniel  Fernandez on 10/19/19.
//  Copyright © 2019 Daniel  Fernandez. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <iostream>
#include <string>
#include <fstream>
#include "Lists/doubleLinkedList.hpp"
#include "Lists/unorderedLinkedList.hpp"

#include "MapNode.hpp"

using namespace std;

class Map {
public:
    //structure to hold the information of a instruction for the user to navigate
    struct Direction {
        //name of the road
        string road;
        
        //length of the road
        double distance;
        
        //heading of the road
        string heading;
        
        //the starting position
        string position;
        
        //the target destination of this segment
        string destination;
        
        bool operator== (const Direction &d)const;
    };
    
    //structure to hold the information of locations to return to the user
    struct Place {
        //name of a location
        string name;
        
        //this integer is the id of the location, or index in the map list
        int location;
        
        bool operator== (const Place &p) { return name == p.name && location == p.location; }
        Place(string n, int index): name(n), location(index) {}
    };
    
    //load data from data file
    bool load(string file_path);
    
    //return shortest distance between a and b
    double distance(int a, int b);
    
    //get the directions from a to b
    unorderedLinkedList<Direction> getDirections(int a, int b);
    
    //return a list of places with similiar name to str, with their IDs
    unorderedLinkedList<Place> find(string str, int max = 5);
    
    //testing
    void printNodes();
    //end testing
    
    Map() {}
private:
    orderedDoubleLinkedList<MapNode> nodes;
    
    //get the heading beetwen two nodes
    string getHeading(const MapNode &A, const MapNode &B);
};



#endif /* Map_hpp */
