#include <iostream> 
#include <fstream>
#include <string>
using namespace std;

int main() {
	int a,b;
	while(1){
		string file_name="prog1-input-";
		char x;
		cout<<"which file do you want to read?";
		cin>>x;
		file_name+=x;
		file_name+=".txt";
		cout<<file_name;
		ifstream fin(&file_name[0]);
		for(int j=0;j<=3;j++){
			fin>>a>>b;
			cout<<a<<" "<<b<<endl;
		}
	}	
  return 0;
}
