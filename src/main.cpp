
#include "node.h"
#include "chord.h"
#include<sstream>
#include<fstream>
#include<iterator>
#include <memory>

using namespace std;

extern map<int,Node *> chord_db;
int total_possible_nodes;
bool isNumber(string str){
	for(int i=0;i<str.length();i++){
		if(!isdigit(str[i])){
			return false;
		}
	}
	return true;
}

//process individual command
void process_command(string cmd,int n){
	istringstream iss(cmd);
    vector<string> v((istream_iterator<string>(iss)),istream_iterator<string>());
	if(v[0].compare("end")==0){
		#ifdef DEBUG_ENABLE
			cout<< "Ending this Chord!"<<endl;
		#endif
		exit(0);
	} else if(v[0].compare("add")==0 && v.size()==2 && isNumber(v[1])){
		unique_ptr<Chord> cd = make_unique<Chord>();
		int new_id = stoi(v[1]);
		#ifdef DEBUG_ENABLE
			cout<<"adding the element" <<  stoi(v[1])<<endl;
		#endif
		cd.get()->add_node(new_id,n);
	} else if(v[0].compare("drop")==0 && v.size()==2 && isNumber(v[1])){
		int node_id = stoi(v[1]);
		if(chord_db.find(node_id) != chord_db.end()){
			#ifdef DEBUG_ENABLE
			cout<<"Dropping the elmenent"<<node_id<<endl;
			#endif
			unique_ptr<Chord> cd = make_unique<Chord>();
			cd.get()->drop_node(node_id);
		} else {
			cout<<"ERROR: Node "<< node_id <<" does not exist"<<endl;
		}
	} else if(v[0].compare("join")==0 && v.size()==3 && isNumber(v[1]) && isNumber(v[2])){
		int fromNode = stoi(v[1]);
		int toNode = stoi(v[2]);
		#ifdef DEBUG_ENABLE
		cout<<"Joining Node from "<< stoi(v[1]) <<" to "<<stoi(v[2])<<endl;
		#endif
		if(chord_db.find(fromNode)!=chord_db.end() && chord_db.find(toNode)!=chord_db.end()){
			chord_db[fromNode]->join_node(chord_db[toNode]);
		}else {
			cout<<"ERROR: Node "<<fromNode <<" does not exist" <<endl;
		}
	} else if(v[0].compare("fix")==0 && v.size()==2 && isNumber(v[1])){
		int node_id = stoi(v[1]);
		if(chord_db.find(node_id) != chord_db.end()){
			chord_db[node_id]->fix_finger();	
			#ifdef DEBUG_ENABLE
			cout<<" fixing the finger table for "<<stoi(v[1])<<endl;
			#endif
		} else {
			cout<<"ERROR: Node "<< node_id <<" does not exist"<<endl;
		}
	} else if(v[0].compare("stab")==0 && v.size()==2 && isNumber(v[1])){
		int node_id = stoi(v[1]);
		if(chord_db.find(node_id) != chord_db.end()){
			#ifdef DEBUG_ENABLE
			cout<<" stablizing the finger table for "<<stoi(v[1])<<endl;
			#endif
			chord_db[node_id]->stabilize();
		} else {
			cout<<"ERROR: Node "<< node_id <<" does not exist"<<endl;
		}
	} else if(v[0].compare("list")==0 && v.size()==1) {
		#ifdef DEBUG_ENABLE
		cout<<"going to list this node \n";
		#endif
		unique_ptr<Chord> cd = make_unique<Chord>();
		cd.get()->list_nodes();
	} else if(v[0].compare("show")==0 && v.size()==2 && isNumber(v[1])){
		#ifdef DEBUG_ENABLE
		cout<<"showing the details for the node "<<stoi(v[1])<<endl;
		#endif
		int node_id = stoi(v[1]);
		if(chord_db.find(node_id)!=chord_db.end()){
			chord_db[node_id]->show_node();
		}else {
			cout<<"ERROR: Node "<< node_id <<" does not exist"<<endl;
		}
	} else {
		cout<<"ERROR: Invalid format or command doesn't exists\n";
	}
} 

int main(int argc, char *argv[])
{
    int n;
    if(argc ==2 ){
		#ifdef DEBUG_ENABLE
        cout<<"Entering interactive mode\n";
		#endif
        n = atoi(argv[1]);
		total_possible_nodes = pow(2,n);
        string str;
        while(getline(cin,str)){
            //keep on going
            //cout<<str<<endl;
			if(str.compare("end")==0)
				exit(0);
			else if(str.compare("")==0)
				continue;
			process_command(str,n);
        }

    } else if(argc==3) {
		#ifdef DEBUG_ENABLE
        cout<<"Entering batch mode\n";
		#endif
        n = atoi(argv[1]);
		total_possible_nodes = pow(2,n);
        char *fileName = argv[2];
 		ifstream in;
		in.open(fileName); 
		if(!in.is_open()){
			cout<<"Error: Input file is not exists\n";
			return 0;
		}
		string str;

		while(getline(in,str)){
			//cout<<str<<endl;
			if(str.compare("end")==0){
				in.close();
				return 0;
			} else if(str.compare("")==0){
				continue;
			}
			process_command(str,n);
		}
		in.close();
    }
    return 0;
}
