/*
*
* Author : Abhash Jain (ajain28) - CSC591 - HW2
* chord.cpp: Constitute a ring - class file for Chord
*
*/
#include "chord.h"
#include "utils.h"

//main class to handle all the instance for node

void Chord::list_nodes(){
    vector<int> final_node_list;
    for(auto n: chord_db){
        if(n.second != NULL && n.second->isJoined){
            final_node_list.push_back(n.first);
            #ifdef DEBUG_ENABLE
            n.second->show_node();
            #endif
        }
    }
    sort(final_node_list.begin(),final_node_list.end());
    if(final_node_list.size()!=0)
        cout<<"Nodes: ";
    else
        cout<<"Empty Node list!";
    //auto print = [](const int &n) {cout<<n<<", ";};
    //std::for_each(final_node_list.begin(),final_node_list.end(),print);
    for(unsigned int i=0;i<final_node_list.size();i++){
        if(i==final_node_list.size()-1){
            cout<<final_node_list[i];
        } else {
            cout<<final_node_list[i]<<", ";
        }
    }
    cout<<endl;
}

void Chord::show_id(int id){
    if(chord_db.find(id)!=chord_db.end()){
        if(chord_db[id]==NULL){
            //Cleanup if the node somehow still there and null
            chord_db.erase(id);
            cout<<"ERROR: Node "<< id <<" does not exist\n";
            return;
        }
        chord_db[id]->show_node();
    } else {
        cout<<"ERROR: Node "<< id << " does not exist\n";
    }
}

//Fork a new Node and add it to our DB
void Chord::add_node(int id,int finger_size){
    if(chord_db[id]==NULL){
        //Cleanup from poising of Node
        chord_db.erase(id);
    }
    Node *newNode = new Node(finger_size);
    newNode->my_id = id;
    for(int i=0;i<finger_size;i++){
        newNode->finger_table[i].start = ((int)(id+pow(2,i)) % ((int)pow(2,finger_size)));
        newNode->finger_table[i].node = id;
    }
    for(int i=0;i<finger_size-1;i++){
        newNode->finger_table[i].interval = newNode->finger_table[i+1].start;
    }
    newNode->finger_table[finger_size-1].interval = newNode->my_id;
    newNode->predecessor = id;
    newNode->isJoined = false;
    if(chord_db.size()==0){
        newNode->isJoined =true;
    }
    chord_db[id] = newNode;
}

void Chord::drop_node(int id){
    if(chord_db[id]==NULL){
        //Cleanup from poising of Node
        chord_db.erase(id);
        cout<<"ERROR: Node "<< id << "does not exist\n";
        return;
    }
    Node *n = chord_db[id];
    chord_db[n->finger_table[0].node]->predecessor = n->predecessor;
    chord_db[n->predecessor]->finger_table[0].node = n->finger_table[0].node;
    delete n;
    chord_db.erase(id);
}