#include "node.h"
#include "chord.h"
#include<sstream>
#include<fstream>
#include<iterator>

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
		cout << "Ending this Chord!\n";
		exit(0);
	} else if(v[0].compare("add")==0 && v.size()==2 && isNumber(v[1])){
		unique_ptr<Chord> cd = make_unique<Chord>();
		int new_id = stoi(v[1]);
		cout<<"adding the element" << stoi(v[1])<<endl;
		cd.get()->add_node(new_id,n);
	} else if(v[0].compare("drop")==0 && v.size()==2 && isNumber(v[1])){
		cout<<"Dropping the elmenent"<<stoi(v[1])<<endl;
	} else if(v[0].compare("join")==0 && v.size()==3 && isNumber(v[1]) && isNumber(v[2])){
		int fromNode = stoi(v[1]);
		int toNode = stoi(v[2]);
		cout<<"Joining Node from "<< stoi(v[1]) <<" to "<<stoi(v[2])<<endl;
		if(chord_db.find(fromNode)!=chord_db.end() && chord_db.find(toNode)!=chord_db.end()){
			chord_db[fromNode]->join_node(chord_db[toNode]);
		}else {
			cout<<"ERROR: Node "<<fromNode <<"does not exist";
		}
	} else if(v[0].compare("fix")==0 && v.size()==2 && isNumber(v[1])){
		cout<<" fixing the finger table for "<<stoi(v[1])<<endl;
	} else if(v[0].compare("stab")==0 && v.size()==2 && isNumber(v[1])){
		cout<<"stablizing the finger table for "<<stoi(v[1])<<endl;
	} else if(v[0].compare("list")==0 && v.size()==1) {
		cout<<"going to list this node \n";
		unique_ptr<Chord> cd = make_unique<Chord>();
		cd.get()->list_nodes();
	} else if(v[0].compare("show")==0 && v.size()==2 && isNumber(v[1])){
		cout<<"showing the details for the node "<<stoi(v[1])<<endl;
		int node_id = stoi(v[1]);
		if(chord_db.find(node_id)!=chord_db.end()){
			chord_db[node_id]->show_node();
		}else {
			cout<<"ERROR: Node "<< node_id <<"does not exist";
		}
	} else {
		cout<<"Invalid format or command doesn't exists\n";
	}
} 

int main(int argc, char *argv[])
{
    int n;
    if(argc ==2 ){
        cout<<"Entering interactive mode\n";
        n = atoi(argv[1]);
		total_possible_nodes = pow(2,n);
        string str;
        while(getline(cin,str)){
            //keep on going
            //cout<<str<<endl;
			if(str.compare("end")==0)
				exit(0);
			process_command(str,n);
        }

    } else if(argc==3) {
        cout<<"Entering batch mode\n";
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
			}
			process_command(str,n);
		}
		in.close();
    }
    return 0;
}

