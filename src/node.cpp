#include "node.h"

Node::Node(int finger_size){
    for(int i=0;i<finger_size;i++){
        struct finger_node temp = {0,0,0};
        finger_table.push_back(temp);
    }
    predecessor = -1;
}

string Node::print_finger(){
    string ret_Result="";
    for(auto i:finger_table){
        ret_Result+= i.node + ",";
    }
    return ret_Result.substr(0,ret_Result.length()-1);
}

void Node::show_node(){
    cout<< "Node "<<id << ": suc "<<finger_table[0].node << ", pre " << (predecessor != -1 ? to_string(predecessor): "None") << ": finger " <<print_finger() <<endl;
}