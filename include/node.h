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

class Node{
    public:
        vector<int> finger_table;
        int predecessor;
        //construtor to Node class
        Node(int finger_size);

        void fix_finger(int id);
        int notify(int id);
        int stabilize(int id);
        int fix(int id);
        void show();
};

#endif
