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
    if(chord_db.find(id)!=chord_db.end()){
        chord_db[id]->show_node();
    } else {
        cout<<"ERROR: Node "<< id << "does not exist\n";
    }
}

//Fork a new Node and add it to our DB
void Chord::add_node(int id,int finger_size){
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
    chord_db[id] = newNode;
}

