//
//  MapNode.hpp
//  Shortest_path
//
//  Created by Daniel  Fernandez on 10/19/19.
//  Copyright © 2019 Daniel  Fernandez. All rights reserved.
//

#ifndef MapNode_hpp
#define MapNode_hpp

#include <string>
#include "Link.hpp"
#include "Lists/unorderedLinkedList.hpp"

using namespace std;

struct MapNode {
    
    string name;
    double weight;
    unorderedLinkedList<Link> links;
    
    double lat, lon;
    
    bool operator== (const MapNode &m)const { return name == m.name; }
    bool operator>= (const MapNode &m)const { return name >= m.name; }
    bool operator> (const MapNode &m)const { return name > m.name; }
    bool operator<= (const MapNode &m)const { return name <= m.name; }
    bool operator< (const MapNode &m)const { return name < m.name; }
    bool operator!= (const MapNode &m)const { return name != m.name; }
    
    MapNode(): name("Unknown"), weight(0) {}
    MapNode(string n, double static_weight): name(n), weight(static_weight) {}
};

#endif /* MapNode_hpp */

