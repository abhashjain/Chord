#ifndef _Node
#define _Node

#include<iostream>
#include<set>
#include<vector>
#include<map>
#include<algorithm>
#include <limits.h>
#include <stdlib.h>
#include<math.h>

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
        //int successor;
        int my_id;
        //construtor to Node class
        Node(int finger_size);

        void fix_finger(int id);
        int notify(int id);
        int stabilize(int id);
        int fix(int id);
        void show_node(); //display the node details
        string print_finger(); //print the finger table of the node
        int find_sucessor(int id);
        Node* closet_preceding_node(int id);
        void join_node(int id);
};

#endif
