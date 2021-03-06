/*
*
* Author : Abhash Jain (ajain28) - CSC591 - HW2
* chord.h: Chord Header file
*/
#ifndef _Chord
#define _Chord

#include "node.h"

class Chord{
    public:
    void add_node(int id,int finger_size);
    void list_nodes();
    void show_id(int id);
    void drop_node(int id);
};
#endif
