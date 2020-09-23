//
//  Map.cpp
//  Shortest_path
//
//  Created by Daniel  Fernandez on 10/19/19.
//  Copyright © 2019 Daniel  Fernandez. All rights reserved.
//

#include "Map.hpp"
#include <iomanip>
#include "Lists/arrayListType.h"
#include <iostream>

//operator
bool Map::Direction::operator== (const Direction &d)const {
    return road == d.road && distance == d.distance && heading == d.heading;
}

//load from file
bool Map::load(string file_path) {
    ifstream data(file_path);
    
    //check if file exists
    if(!data)
        return false;
    
    //variable to hold the node info
    MapNode m;
    
    //read nodes
    data >> m.name; // read the placeholder
    
    while(data >> m.name && m.name != "#Links") {
        data >> m.lat >> m.lon; //read lat and lon
        
        nodes.insert(m); //insert the new node
    }
    
    //read links
    
    //variable to read the links
    Link l;
    string nodeA, nodeB;
    
    while(data >> l.name) {
        //read data
        data >> nodeA >> nodeB >> l.weight;
        
        //find pointer to nodes
        linkedListIterator<MapNode> itr;
        
        for(itr = nodes.begin(); itr != nodes.end(); ++itr) {
            if((*itr).name ==nodeA) {
                //the link involves this node
                
                //search the target
                for (linkedListIterator<MapNode> itr_2 = nodes.begin(); itr_2 != nodes.end(); ++itr_2) {
                    if ((*itr_2).name == nodeB) {
                        l.target = itr_2.getPtr();
                        
                        //insert pointer
                        itr.getPtr()->links.insert(l);
                    }
                }
            }
            if((*itr).name ==nodeB) {
                //the link involves this node
                
                //search the target
                for (linkedListIterator<MapNode> itr_2 = nodes.begin(); itr_2 != nodes.end(); ++itr_2) {
                    if ((*itr_2).name == nodeA) {
                        l.target = itr_2.getPtr();
                        
                        //insert pointer
                        itr.getPtr()->links.insert(l);
                    }
                }
            }
            
        }
    }
    return true;
}

//print all nodes
void Map::printNodes() {
    //traverse the nodes
    for (MapNode m : nodes) {
        cout << m.name << endl;
        
        //for each node, print its links
        for(Link l : m.links) {
            cout << "   " << l.target->name << " " << l.weight << " miles." << endl;
        }
        cout << endl;
    }
}

//Shortest distance from a to b
//Use Dijkstra algorithm
//Always follow shortest path FROM STARTING point
double Map::distance(int a, int b) {
    
    //check that both a and b are within bounds
    if(a < 0 || a >= nodes.size() || b < 0 || b >= nodes.size())
        throw std::out_of_range("Index out of range");
    
    //set all weights to -1
    for(linkedListIterator<MapNode> itr = nodes.begin(); itr != nodes.end(); ++itr)
        itr.getPtr()->weight = -1;
    
    //start node
    MapNode *A = &nodes[a];
    
    //destination node
    MapNode *B = &nodes[b];
    
    //list to keep already seen nodes
    unorderedLinkedList<MapNode> seen;
    
    //set initial weight to 0
    nodes[a].weight = 0;
    seen.insert(*A);
    
    //loop until destination is reached
    while (true) {
        double min = 25000.00;
        MapNode *temp = nullptr;
        
        //loop through the nodes with weight different that -1, which are the ones that I have already arrived
        for (MapNode m : nodes) {
            if (m.weight != -1) {
                //loop thru the links
                for (Link l : m.links) {
                    
                    //if the weight until this target is less than min, then this is the path to follow
                    if((m.weight + l.weight) < min && seen.seqSearch(*(l.target)) == -1) {
                        //keep the min weight in min variable
                        min = m.weight + l.weight;
                        temp = l.target;
                    }
                }
            }
        }
        
        //set the new weight of target
        temp->weight = min;
        
        //mark target as already seen
        seen.insert(*temp);
        
        //if found the destination node, then exit
        if(temp->name == B->name)
            return temp->weight;
        
    }
    
    return 0;
}

//similar to previous, but this function also keeps track of the path, using the Direction struct
unorderedLinkedList<Map::Direction> Map::getDirections(int a, int b) {
    unorderedLinkedList<Map::Direction> dir;
    
    if(a < 0 || a >= nodes.size() || b < 0 || b >= nodes.size())
        throw std::out_of_range("Index out of range");
    
    //set all weights to -1
    for(linkedListIterator<MapNode> itr = nodes.begin(); itr != nodes.end(); ++itr)
        itr.getPtr()->weight = -1;
    
    //start node
    MapNode *A = &nodes[a];
    
    //destination node
    MapNode *B = &nodes[b];
    
    //list to keep seen nodes
    unorderedLinkedList<MapNode> seen;
    
    //set initial weight to 0
    nodes[a].weight = 0;
    seen.insert(*A);
    
    //list to keep the paths
    arrayListType<unorderedLinkedList<Direction>> paths;
    
    //loop until destination is reached
    while (true) {
        double min = INT_MAX;
        MapNode *temp = nullptr;
        Direction d;
        
        for (MapNode m : nodes) {
            if (m.weight != -1) {
                //loop thru the links
                for (Link l : m.links) {
                    
                    if((m.weight + l.weight) < min && seen.seqSearch(*(l.target)) == -1) {
                        min = m.weight + l.weight;
                        temp = l.target;
                        
                        //also keep the Direction info for this link
                        d.road = l.name;
                        d.distance = l.weight;
                        d.heading = getHeading(m, *l.target);
                        d.position = m.name;
                        d.destination = temp->name;
                    }
                }
            }
        }
        
        //set the new weight of target and keep going
        temp->weight = min;
        seen.insert(*temp);
        
        
        int path = -1;
        bool inserted = false;
        
        //if the direction styarts from the begining, then is a new path
        if(d.position == A->name) {
            unorderedLinkedList<Map::Direction> dir;
            dir.insert(d);
            paths.insert(dir);
            path = paths.listSize() - 1;
            inserted = true;
        } else {
            //if not, try to find a direction that ends where the currect one starts
            for(int i = 0; i < paths.listSize(); i++) {
                if (paths[i].last().destination == d.position) {
                    paths[i].insert(d);
                    path = i;
                    inserted = true;
                    break;
                }
            }
        }
        
        if(!inserted) {
            //if not found, then find a direction that contains the starting point of this location
            for(int i = 0; i < paths.listSize(); i++) {
                bool created = false;
                
                for(int k = 0; k < paths[i].size(); k++) {
                    if(paths[i][k].position == d.position) {
                        //if found, then copy the path
                        unorderedLinkedList<Map::Direction> cpy_dir = paths[i];
                        //remove everything from where this direction starts
                        cpy_dir.removeFrom(k);
                        //insert the new direction
                        cpy_dir.insert(d);
                        //push the directions list as a possible path to the destination
                        paths.insert(cpy_dir);
                        
                        //set path to point to this path
                        path = paths.listSize() - 1;
                        created = true;
                        break;
                    }
                }
                if(created)
                    break;
            }
        }
        
        //if found, return the path that led to the destination
        if(temp->name == B->name) {
            return paths[path];
        }
        
    }
    
    return dir;
}

//get the heading from the latitude and longitude
string Map::getHeading(const MapNode &A, const MapNode &B) {
    //get the change in lat
    double dlat = B.lat - A.lat;
    
    //get the change in longitude
    double dlon = B.lon - A.lon;
    
    if(dlat > 0 && dlon > 0)
        return "Norteast";
    if(dlat > 0 && dlon < 0)
        return "Northwest";
    if(dlat < 0 && dlon > 0)
        return "Southeast";
    if(dlat < 0 && dlon < 0)
        return "Southwest";
    return "none";
}

//search algorithm
unorderedLinkedList<Map::Place> Map::find(string str, int max) {
    
    //list to keep the results
    unorderedLinkedList<Map::Place> results;
    
    //variable to return the position in the list of each location
    int location = 0;
    
    for (MapNode m : nodes) {
        
        //variable to create an all-case-lower of each term
        string lc_name = "";
        string lc_search = "";
        
        //name and str to lower case
        for(size_t i = 0; i < m.name.length(); ++i)
            lc_name += (tolower(m.name[i]));
        
        for(size_t i = 0; i < str.length(); ++i)
            lc_search += (tolower(str[i]));
        
        //find any city name that contains this string
        if(lc_name.find(lc_search) != string::npos) {
            //if matches, insert it as a possible place
            results.insert(Place(m.name, location));
            
            //if max number of terms, then return
            if(results.size() >= max)
                break;
        }
        location++;
    }
    
    return results;
}


