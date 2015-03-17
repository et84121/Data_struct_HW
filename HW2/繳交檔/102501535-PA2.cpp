#include <iostream>
#include <fstream> 
#include <string>
using namespace std;

int count=0;

int check(string a,int index,int k)					
{
	bool re=true;													
	for(int x=k;x<index;x++) 							 
	{                                                      
		if(a[x]==a[index]){re=false;break;}
	}
	return re;
}


//Permutation Generator
//permutate a[k]~a[m]
void PG(string a,const int k,const int m,ofstream *fout){   
	if (k == m){
		for (int i=0;i<=m;i++){
			cout<<a[i]<<" ";
			*fout<<a[i]<<" ";
		}
		cout<<endl;
		*fout<<endl;
		count++;//�p�ƾ�+1 
	}
	else
		for(int index=k;index<m;index++){
			if(check(a,index,k)){
			swap(a[k],a[index]);
			PG(a,k+1,m,fout);
			swap(a[k],a[index]);
			}
		}
}

int main (){
    string file_order;	//�n�}�Ҫ��ɮקǸ� 
	string p;  //�n�ƧǪ��r�� 
	int length;
	while(1){
		string input_file_name="prog2-input-.txt";  //Ū�ɦW 
		string output_file_name="prog2-output-.txt"; //�g�ɦW 
		cout<<"input the order of file"<<endl;
		cin>>file_order;   
		
		input_file_name.insert(12, file_order);  //�N �ɮקǸ� ���J�ɦW�� 
		output_file_name.insert(13, file_order);
		
		ifstream fin (&input_file_name[0]);  //�}�� 
		ofstream fout(&output_file_name[0]);
		
		if(!fin) {cout<<"File read Error!!"<<endl;}  //�ˬd�O�_�}�ɦ��\ 
		if(!fout){cout<<"File write Error!!"<<endl;}
		
		
		cout<<"Get string form file now"<<endl;
		
		while((fin>>length>>p)&&(length!=0)){  //Ū�ɨçP�_�O�_��奼�F 
			cout<<p<<endl; 
			count=0;//�p�ƾ��k�s 
			PG(p,0,p.size(),&fout);//�i��ƦC�B��
			fout<<count<<endl;
			cout<<count<<endl;
		}
	}
	return 0;
}
