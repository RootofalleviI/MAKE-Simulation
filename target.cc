#include <iostream>
#include <string>
#include "target.h"
using namespace std;

Target::Target(const string &name, ostream &out) :
    name(name), out(out), is_leaf(true), num_dep(0), last_update(0),
    keys(new string[maxDepends]),       // Array of dependency names
    dep(new Target*[maxDepends]) {}     // Array of pointers to dependencies

// Deallocating Targets is handled by the dtor of Makefile
Target::~Target() { 
    delete[] keys;
    delete[] dep; 
}

bool Target::isLeaf() const { return is_leaf; }

int Target::lastUpdated() const { return last_update; }

void Target::update(int time) {
    out << this->name << " updated at time " << time << endl;
    last_update = time;
}

void Target::addDepend(Target *d) {

    // if already a dependency
    for (int i=0; i<num_dep; ++i) {
        if (keys[i] == d->name) { 
            return;
        }
    }

    // if maximum dependency used
    if (num_dep == maxDepends) {
        out << "Max dependencies exceeded" << endl;
        return;
    }

    // add dependency
    keys[num_dep] = d->name;
    dep[num_dep] = d;
    is_leaf = false;
    num_dep++;
}

void Target::build() {
    int time = lastUpdated();
    int temp = time;
    for (int i=0; i<num_dep; ++i) {

        // if not a leaf, build it first!
        if (! dep[i]->is_leaf) {
            dep[i]->build();
        }

        // now check timestamp
        if (dep[i]->last_update > time) {
            time=dep[i]->last_update;
        }
    }

    // if needs update
    if (time > temp) {
        cout << "Building " << name << endl;
        last_update = time;
    }
}

