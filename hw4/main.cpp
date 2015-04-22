#include <iostream>
#include <fstream>
#include <string>
#include "point.h"
#include "plane.h"

using namespace std;

string file_order;
int row=0,column=0,pin_num=0,obs_num=0;
//��ơA�C�ơA�I�ơA��ê��

int *_map;

point *pin;
plane *obs;

int check_obs(int,int);

int main()
{
    string input_file_name="prog4-input-.txt";
    string output_file_name="prog4-output-.txt";
    //�}Ū�ɦW
	cout<<"input the order of file"<<endl;
	cin>>file_order;
	//��J�nŪ�����ɮק�
	input_file_name.insert(12, file_order);
	output_file_name.insert(13, file_order);
	//�X���u�����ɦW
	ifstream fin (&input_file_name[0]);
	ofstream fout(&output_file_name[0]);
	//�}Ū�g�ɮ׬y
	if(!fin) {cout<<"File read Error!!"<<endl;}
	if(!fout){cout<<"File write Error!!"<<endl;}
    //�ˬd�O�_�}�y���\
    cout << "program start!" << endl;

    //while(obs_num == 0)
    for(int a=0;a<4;a++)
    {
        //�إ߰ϰ��ܼ�(�x�s��J�ȥ�)
        string in;int temp;
        fin>>in>>temp;
        cout<<in<<" "<<temp<<endl;
        //�P�_
        if(in == ".row"){row = temp;}
        if(in == ".column"){column = temp;}
        if(in == ".pin"){
            //�N �`�� �s�J �I�� ��
            pin_num = temp;
            //�ʺA�إ� �I �}�C
            pin = new point[pin_num];
            //�N�ɮפ�����T�s�J �I_�}�C ��
            for(int b=0;b<pin_num;b++){
                int x,y;
                fin>>in>>x>>y;
                pin[b].x = x;
                pin[b].y = y;
            }
        }
        if(in == ".obs"){
            obs_num = temp;
            obs = new plane[obs_num];
            for(int b=0;b<obs_num;b++){
                int L_x,L_y,R_x,R_y;
                fin>>in>>L_x>>L_y>>R_x>>R_y;
                obs[b].L_x = L_x;
                obs[b].L_y = L_y;
                obs[b].R_x = R_x;
                obs[b].R_y = R_y;
            }
        }
    }
    //��X�Ҩ��o����T
    cout<<endl<<"- - -"<<endl;

    cout<<"row:"<<row<<" column:"<<column<<endl<<" -"<<endl;

    for (int a=0;a<pin_num;a++){
        cout<<"pin"<<a<<"_x:"<<pin[a].x<<" pin"<<a<<"_y:"<<pin[a].y<<endl;
    }
    cout<<" -"<<endl;
    for (int a=0;a<obs_num;a++){
        cout<<"obs"<<a<<"_LeftUp x:"<<obs[a].L_x<<" y:"<<obs[a].L_y;
        cout<<" obs"<<a<<"_RightDown x:"<<obs[a].R_x<<" y:"<<obs[a].R_y<<endl;
    }
    cout<<"- - -"<<endl;
    //[end]

    //�a�ϫإ�
    /*  0->�i�H�����a
        1->��obs��ê��
        2->��pin�I     */
    _map = new int [row*column];
    //�N��i�a�ϳ��g�J0
    for (int a=0;a<row;a++){
        for (int b=0;b<column;b++){
            *(_map+a*(column)+b)=0;

        }
    }
    //�Хܻ�ê��
    for (int a=0;a<obs_num;a++){
        obs[a].write_into_map(_map,row,column);
    }
    //�Х��I
    for (int a=0;a<pin_num;a++){
        pin[a].write_into_map(_map,row,column);
    }

    //�L�X�a��
    cout<<endl;
    for (int a=0;a<row;a++){
        for(int b=0;b<column;b++){
            cout<<*(_map+a*(column)+b)<<" ";
        }
        cout<<endl;
    }

    return 0;
}

