#ifndef _Node
#define _Node

#include<iostream>
#include<set>
#include<vector>
#include<map>
#include<algorithm>
#include <limits.h>
#include <stdlib.h>

using namespace std;
struct finger_node{
    int start;
    int interval;
    int node;
};
class Node{
    public:
        vector<finger_node> finger_table;
        int predecessor;
        int id;
        //construtor to Node class
        Node(int finger_size);

        void fix_finger(int id);
        int notify(int id);
        int stabilize(int id);
        int fix(int id);
        void show_node();
        string print_finger();
};

#endif
