#include "node.h"

extern map<int,Node *> chord_db;
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
        ret_Result+= to_string(i.node) + ",";
    }
    return ret_Result.substr(0,ret_Result.length()-1);
}

void Node::show_node(){
    cout<< "Node "<<id << ": suc "<<finger_table[0].node << ", pre " << (predecessor != -1 ? to_string(predecessor): "None") << ": finger " <<print_finger() <<endl;
}

int Node::find_sucessor(int new_id){
    if(new_id>id && new_id <= finger_table[0].node){
        return finger_table[0].node;
    } else {
        Node *n0 = chord_db[finger_table[0].node]->closet_preceding_node(new_id);
        return n0->find_sucessor(new_id);
    }
}

Node* Node::closet_preceding_node(int new_id){
    for(int i = finger_table.size()-1;i >=0;i--){
        //if last node lies in the range
        if(finger_table[i].node > id && finger_table[i].node < new_id){
            return chord_db[finger_table[i].node];
        }else { //this node is the closest precedessor
            return this;
        }
    }
    return this;
}

void Node::join_node(int new_id){
    predecessor = -1;
    //finger_table[0].node = 0;
}