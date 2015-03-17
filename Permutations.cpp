#include <iostream> 
#include <string>
using namespace std;

int count=0;

//Permutation Generator
//permutate a[k]~a[m]
void PG(string a,const int k,const int m){   
	if (k == m){
		for (int i=0;i<=m;i++){
			cout<<a[i]<<" ";
		}
		cout<<endl;
		count++;
	}
	else{
		int c=0;
		for(int i=k;i<m;i++){
			if(a[k]==a[i]){
				i++;
			}
			swap(a[k],a[i]);
			PG(a,k+1,m);
			swap(a[k],a[i]);
		}
	}
}

int main (){	
	while(1){
		count=0;
		cout<<"Type the string you want to permutation"<<endl;
		string p;
		cin>>p;
		PG(p,0,p.size());
		cout<<count<<endl;
	}
	return 0;
}
