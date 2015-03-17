#include <iostream>
#include <fstream>
using namespace std;

int funtion(int a){
	int count=0;
	cout<<a<<" ";
	while( a>1 ){
		if (a%2==1){
			a = (3*a)+1;
		}
		else{
			a = a/2;
		}
		count+=1;
		cout<<a<<" ";
	}
	cout<<"count="<<count<<endl;
	return a;
}

int main() {
	int n;
	cout<<"Please input a number"<<endl;
	cin>>n;
	funtion(n);
	return 0;
}

