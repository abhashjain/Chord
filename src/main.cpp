#include "node.h"
#include "chord.h"
#include<sstream>
#include<fstream>
using namespace std;

int main(int argc, char *argv[])
{
    int n;
    if(argc ==2 ){
        cout<<"Entering interactive mode\n";
        n = atoi(argv[1]);
        string str;
        while(getline(cin,str)){
            //keep on going
            cout<<str<<endl;
			if(str.compare("end")==0)
				exit(0);
        }

    } else if(argc==3) {
        cout<<"Entering batch mode\n";
        n = atoi(argv[1]);
        char *fileName = argv[2];
 		ifstream in;
		in.open(fileName); 
		if(!in.is_open()){
			cout<<"Error: Input file is not exists\n";
			return 0;
		}
		string str;

		while(getline(in,str)){
			cout<<str<<endl;
			if(str.compare("end")==0){
				in.close();
				return 0;
			}
		}
		in.close();
    }
    return 0;
}

