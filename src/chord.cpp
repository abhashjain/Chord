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

void Chord::show_all(){
    for(auto m: chord_db){
        
    }
}