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
    cout<< "Node "<< my_id << ": suc "<<finger_table[0].node << ", pre " << (predecessor != -1 ? to_string(predecessor): "None") << ": finger " <<print_finger() <<endl;
}

int Node::find_sucessor(int new_id){
    cout<<"Inside "<<__FUNCTION__<<" for my_id " << my_id << " and looking for "<< new_id <<endl;
    // Node *n1 = find_predecessor(new_id);
    // return n1->finger_table[0].node;
    if(this->my_id==this->finger_table[0].node){
        return this->my_id;
    }
    if(new_id>my_id && new_id <= finger_table[0].node){
        return finger_table[0].node;
    } else {
        Node *n0 = chord_db[finger_table[0].node]->closet_preceding_node(new_id);
        return n0->find_sucessor(new_id);
    }
}

bool Node::check_in_range(int id,int start,int end){
    cout<<"Inside "<<__FUNCTION__<<endl;
    if(end>start){
        if(id>start && id<=end){
            return true;
        }
    } else { //need to do rollover
        if((id>start && id<(int)pow(2,finger_table.size())) || (id>=0 && id<=end)){
            return true; 
        }
    }
    return false;
}

Node* Node::find_predecessor(int new_id){
    cout<<"Inside "<<__FUNCTION__ << "doing for "<<new_id <<" myid is "<< my_id <<endl;
    Node* n1 = this;
    while(!check_in_range(new_id,n1->my_id,n1->finger_table[0].node)){
        cout<<"calling procedin node function\n";
        n1 = n1->closet_preceding_node(new_id);
    }
    return n1;
}

Node* Node::closet_preceding_node(int new_id){
    cout<<"Inside "<<__FUNCTION__<< " for my_id " << my_id << " and looking for "<< new_id <<endl;
    for(int i = finger_table.size()-1;i >=0;i--){
        //if last node lies in the range
        //check in the round range
        if(new_id > my_id){
            if(finger_table[i].node > my_id && finger_table[i].node < new_id){
                return chord_db[finger_table[i].node];
            }
        } else {
            if((finger_table[i].node > my_id && finger_table[i].node < (int)pow(2, finger_table.size())) || 
                (finger_table[i].node >=0 && finger_table[i].node < new_id) ){
                    return chord_db[finger_table[i].node];
                }
        }
        // if(finger_table[i].node > my_id && finger_table[i].node < new_id){
        //     return chord_db[finger_table[i].node];
        // }
    }
    return this;
}
void Node::init_finger_table(Node *n1){
    cout<<"Inside "<<__FUNCTION__<<endl;
    finger_table[0].node = n1->find_sucessor(finger_table[0].start);
    predecessor = chord_db[finger_table[0].node]->predecessor;
    chord_db[finger_table[0].node]->predecessor = this->my_id;
    for(int i=0;i<finger_table.size()-1;i++){
        if(finger_table[i+1].start >= my_id && finger_table[i+1].start<finger_table[i].node){
            finger_table[i+1].node = finger_table[i].node;
        } else {
            finger_table[i+1].node = n1->find_sucessor(finger_table[i+1].start);
        }
    }
}
void Node::update_others(){
    cout<<"Inside "<<__FUNCTION__<<endl;
    for(int i=0;i<finger_table.size();i++){
        Node *p = find_predecessor((my_id-(int)pow(2,i)));
        cout<<"find_predecer return " << p->my_id << "for " << (my_id-(int)pow(2,i)) <<endl;
        p->update_finger_table(my_id,i);
    }
}
void Node::update_finger_table(int s,int i){
    cout<<"Inside "<<__FUNCTION__<< " for my_id " <<my_id <<" s "<<s <<" i " <<i<<endl;
    if(finger_table[i].node > my_id){
        if(s >=my_id && s<finger_table[i].node){
            finger_table[i].node =s;
            Node *p = chord_db[predecessor];
            p->update_finger_table(s,i);
        }
    } else {
        if((s >= my_id && s < (int) pow(2,finger_table.size())) || 
            (s>0 && s< finger_table[i].node)){
                finger_table[i].node =s;
                Node *p = chord_db[predecessor];
                p->update_finger_table(s,i);
            }
    }
    // if(s >=my_id && s<finger_table[i].node){
    //     finger_table[i].node =s;
    //     Node *p = chord_db[predecessor];
    //     p->update_finger_table(s,i);
    // }
}

void Node::join_node(Node *n1){
    //predecessor = -1;
    //finger_table[0].node = 0;
    if(n1){
        cout<<"join node\n";
        init_finger_table(n1);
        update_others();
    } else {
        for(int i=0;i<finger_table.size();i++){
            finger_table[i].node = my_id;
        }
        predecessor = my_id;
    }
}