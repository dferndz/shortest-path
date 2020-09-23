//
//  Link.hpp
//  Shortest_path
//
//  Created by Daniel  Fernandez on 10/19/19.
//  Copyright © 2019 Daniel  Fernandez. All rights reserved.
//

#ifndef Link_hpp
#define Link_hpp

#include <string>

using namespace std;

class MapNode;

struct Link {
    string name;
    MapNode *target;
    double weight;
    
    bool operator== (const Link &l) { return name == l.name && target == l.target && weight == l.weight; }
    
    Link(): name("Unknown"), target(nullptr), weight(0) {}
    Link(string n, MapNode *node, double distance): name(n), target(node), weight(distance) {}
};
#endif
