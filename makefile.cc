#include <iostream>
#include <string>
#include <cassert>
#include "makefile.h"
using namespace std;

Makefile::Makefile(ostream &out) :
    out(out), num_targets(0), 
    keys(new string[20]),       // array of names
    targets(new Target*[20]),   // array of ptrs to Targets
    timestamp(0) {}

// Deleting all targets from Makefile preventing possible double freeing
Makefile::~Makefile() {
    for (int i=0; i<num_targets; ++i) { delete targets[i]; }
    delete[] targets;
    delete[] keys;
}

// Helper that links string array with Target* array, i.e. returning 
// a pointer to the correct Target given name; return nullptr if DNE.
Target* Makefile::find_target(string name) const { 
    Target *t = NULL;
    for (int i=0; i<num_targets; ++i) {
        if (keys[i].compare(name) == 0) 
            t = targets[i]; 
    }
    return t;
}

void Makefile::addDepend(const string &t, const string &d) {

    // Look up both Targets
    Target *left_target = find_target(t);
    Target *right_target = find_target(d);

    // First wave of exception handling
    bool fail = false;

    if ((!left_target) && (num_targets == maxTargets)) {
        out << "Max targets exceeded" << endl;
        fail = true;
    } 
    if ((!right_target) && (num_targets == maxTargets)) {
        out << "Max targets exceeded" << endl;
        fail = true;
    }

    if (fail) return;

    // If left DNE, declare and initialize it
    if (!left_target) {
        Target *targetL = new Target(t, out);  
        keys[num_targets] = t;           
        targets[num_targets] = targetL; 
        num_targets++;                  
        left_target = targetL;          
    }

    // Second wave of exception handling
    if ((!right_target) && (num_targets == maxTargets)) {
        out << "Max targets exceeded" << endl;
        return;
    }

    // If right DNE, declare and initialize it
    if (!right_target) {
        Target *targetR = new Target(d, out);  
        keys[num_targets] = d;           
        targets[num_targets] = targetR; 
        num_targets++;                  
        right_target = targetR;         
    }

    // Finally, call Target::addDepend
    left_target->addDepend(right_target);
}

// Update a non-leaf Target
void Makefile::changeTarget(const string &t) {
    Target *target = find_target(t);
    timestamp++;
    if (target->is_leaf) {
        target->update(timestamp);
    } else {
        out << "Cannot update non-leaf object" << endl;
    }
}

// Update a leaf Target
void Makefile::rebuild(const std::string &t) {
    find_target(t)->build();
}


