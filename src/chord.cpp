#include "chord.h"
#include "utils.h"

//main class to handle all the instance for node

void Chord::list_nodes(){
    vector<int> final_node_list;
    for(auto n: chord_db){
        final_node_list.push_back(n.first);
    }
    sort(final_node_list.begin(),final_node_list.end());
    auto print = [](const int &n) {cout<<n<<"\t";};
    std::for_each(final_node_list.begin(),final_node_list.end(),print);
    cout<<endl;
}

void Chord::show_id(int id){
    chord_db[id]->show_node();
}

void Chord::add_node(int id,int finger_size){
    Node *newNode = new Node(finger_size);
    newNode->my_id = id;
    for(int i=0;i<newNode->finger_table.size();i++){
        newNode->finger_table[i].start = id;
        newNode->finger_table[i].interval = 0;
        newNode->finger_table[i].node = id;
    }
    chord_db[id] = newNode;
}

