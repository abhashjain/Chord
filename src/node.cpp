#include "node.h"
#define SUCCESSOR finger_table[0].node; 

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

int Node:: relativeID(int universal, int local){
    int ret = universal-local;
    if(ret<0){
        ret += ((int) pow(2,finger_table.size()));
    }
    return ret;
}
void Node::show_node(){
    cout<< "Node "<< my_id << ": suc "<<finger_table[0].node << ", pre " << (predecessor != -1 ? to_string(predecessor): "None") << ": finger " <<print_finger() <<endl;
}

//Find the successor of Given Node
int Node::find_sucessor(int new_id){
    cout<<"Inside "<<__FUNCTION__<<" for my_id " << my_id << " and looking for "<< new_id <<endl;
    if(my_id == new_id){
        return this->my_id;
    }
    //When there is single node in network,because node sucessor can't be same as itself
    if(this->my_id==this->finger_table[0].node){
        return this->my_id;
    }
    //New node id lies between the current node id and it's suceessor
    if(new_id > my_id && new_id <= finger_table[0].node){
        return SUCCESSOR;
    } //When Successor is 0 then I handled it differently
    else if ((finger_table[0].node == 0) && (new_id > my_id && new_id <= (int)pow(2,finger_table.size()))){
        return SUCCESSOR;
    }
    else { //find next preding node to the new_id and return it's successor
        Node *n0 = chord_db[finger_table[0].node]->closet_preceding_node(new_id);
        return n0->find_sucessor(new_id);
    }
}
//this function check for round range excluding boundary
bool Node::check_in_range(int id,int start,int end){
    cout<<"Enter "<<__FUNCTION__<< ":my id " <<my_id << " id "<< id << " start " <<start <<" end " << end << endl;
    if(end>start){  //increasing range
        if(id>start && id<end){ //Id will be in id E (start,end)
            return true;
        }
    } else { //need to do rollover 
        if((id>start && id<(int)pow(2,finger_table.size())) || (id>=0 && id < end)){
            return true; 
        }
    }
    return false;
}

Node* Node::find_predecessor(int new_id){
    cout<<"Enter: "<<__FUNCTION__ << " predecessor for "<<new_id <<" myid is "<< my_id <<endl;
    Node* n1 = this;
    int pre = n1->my_id;
    int find_relative_id = relativeID(new_id,n1->my_id);
    int successor_relative_id = relativeID(finger_table[0].node,n1->my_id);
    while(!(find_relative_id > 0 && find_relative_id <= successor_relative_id)){
        pre = n1->my_id;
        n1 = n1->closet_preceding_node(new_id);
        cout<< __FUNCTION__ << ": closet procedeing return " << n1->my_id << " for new_id "<<new_id << " at "<< my_id <<endl;
        if(pre == n1->my_id){
            break;
        }
        find_relative_id = relativeID(new_id,n1->my_id);
        successor_relative_id = relativeID(finger_table[0].node,n1->my_id);
    }
    /* while(!(check_in_range(new_id,n1->my_id,n1->finger_table[0].node && (new_id == finger_table[0].node)))){
        n1 = n1->closet_preceding_node(new_id);
        cout<< __FUNCTION__ << ": closet procedeing return " << n1->my_id << " for new_id "<<new_id << " at "<< my_id <<endl;
        p1=p;
        p=n1->my_id;
        if(p == p1)
            break;
    } */
    return n1;
}

Node* Node::closet_preceding_node(int new_id){
    cout<<"Enter "<<__FUNCTION__<< " my_id " << my_id << " and looking for "<< new_id <<endl;
    int find_id_relative = relativeID(new_id,this->my_id);
    for(int i = finger_table.size()-1;i >=0;i--){
        int ith_id_relative = relativeID(finger_table[i].node,this->my_id);
        if(ith_id_relative >0 && ith_id_relative < find_id_relative){
            return chord_db[finger_table[i].node];
        }
        /* if(check_in_range(finger_table[i].node,my_id,new_id)){
            return chord_db[finger_table[i].node];
        } */
    }
    return this;
}

//use to initialize the finger table for new joining node
void Node::init_finger_table(Node *n1){
    cout<<"Enter: "<<__FUNCTION__ <<" my_id " <<my_id << " doing init from " << n1->my_id<<endl;
    finger_table[0].node = n1->find_sucessor(finger_table[0].start);
    //set my predecessor to sucessor predessor and sucessor predecessor will be current node
    //Like: inserting in between
    predecessor = chord_db[finger_table[0].node]->predecessor;
    chord_db[finger_table[0].node]->predecessor = this->my_id;

    for(int i=0;i<finger_table.size()-1;i++){
        /* int next_relative_id = relativeID(finger_table[i+1].start,my_id);
        int current_relative_id = relativeID(finger_table[i].node,my_id);
        if(next_relative_id >=0 && next_relative_id < current_relative_id){
            finger_table[i+1].node = finger_table[i].node;
        } else {
            finger_table[i+1].node = n1->find_sucessor(finger_table[i+1].start);
        } */
        if(check_in_range(finger_table[i+1].start, my_id, finger_table[i].node) && finger_table[i+1].node == my_id){
            finger_table[i+1].node = finger_table[i].node;
        } else {
            finger_table[i+1].node = n1->find_sucessor(finger_table[i+1].start);
        }
    }
}
void Node::update_others(){
    cout<<"Enter: "<<__FUNCTION__<< " for my_id "<<my_id<<endl;
    for(int i=0;i<finger_table.size();i++){
        int change_id = my_id - (int)pow(2,i);
        if(change_id<0){
            cout<<"Abhash: "<<change_id<<endl;
            change_id = (int)pow(2,finger_table.size())+change_id;
        }
        Node *p = find_predecessor(change_id);
        cout<<"find_predecer return " << p->my_id << " for " << change_id << " for i: "<<i<<endl;
        p->update_finger_table(my_id,i);
    }
}
void Node::update_finger_table(int s,int i){
    cout<<"Enter: "<<__FUNCTION__<< " for my_id " <<my_id <<" s:"<<s <<" i:" <<i<<endl;
    /* if(my_id==s){
        return;
    } */
    /* int update_relative_id = relativeID(s,my_id);
    int finger_i_relative_id = relativeID(finger_table[i].node,my_id);
    if(update_relative_id >= 0 && update_relative_id < finger_i_relative_id){
        cout<< "Changed the entry for " << my_id << " index: "<<i  << " from " <<finger_table[i].node << " to "<<s<<endl;
        finger_table[i].node = s;
        Node *p = chord_db[predecessor];
        p->update_finger_table(s,i);
    } */
    if(check_in_range(s,my_id,finger_table[i].node)){
        cout<< "Changed the entry for " << my_id << " index: "<<i  << " from " <<finger_table[i].node << " to "<<s<<endl;
        finger_table[i].node =s;
        Node *p = chord_db[predecessor];
        p->update_finger_table(s,i);
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
        show_node();
        update_others();
    } else {
        for(int i=0;i<finger_table.size();i++){
            finger_table[i].node = my_id;
        }
        predecessor = my_id;
    }
}


//Function to fix the finger table entry for this node
void Node::fix_finger(){
	for(int i=0;i<finger_table.size();i++){
		finger_table[i].node = find_sucessor(finger_table[i].start);
	}
}