#ifndef _TARGET_H_
#define _TARGET_H_
#include <iostream>
#include <string>

const int maxDepends = 10;

struct Target {
    std::string name;	// Target name
    std::ostream &out;	// Target ostream
    bool is_leaf;	// Is this a leaf?
    int num_dep;	// Number of dependencies
    int last_update;	// Timestamp
    std::string *keys;	// Array of dependency names
    Target **dep;	// Array of ptr to dependencies 

    Target(const std::string &name, std::ostream &out=std::cout);
    ~Target();
    bool isLeaf() const;
    void addDepend(Target *d);
    void update(int time);
    int lastUpdated() const;
    void build();
};

#endif

