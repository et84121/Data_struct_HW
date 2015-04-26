#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <iomanip>
#include <vector>
#include "point.h"
#include "plane.h"

using namespace std;
//- - - - - - �Ĥ@���q�Ϊ��ܼ�
string file_order;
int row=0,column=0,pin_num=0,obs_num=0;
//��ơA�C�ơA�I�ơA��ê��

point *pin;
plane *obs;
//- - - - - -�ĤG���q�Ϊ��ܼ�
point *_map;
//- - - - - -�ĤT���q�Ϊ��ܼ�
queue<point> wave_f; //wave front
vector<point> answer_route;
vector<point> answer_route_line;
int finded = 0;//���S�����t�@���I
int route_finded = 0;


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
    _map = new point [row*column];
    //�N��i�a�ϳ��g�J0
    for (int a=0;a<row;a++){
        for (int b=0;b<column;b++){
            _map[(a*column)+b].data = 0;
            _map[(a*column)+b].x = b;
            _map[(a*column)+b].y = a;
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

    for (int a=0;a<row;a++){
        for (int b=0;b<column;b++){
            _map[(a*column)+b].x = b;
            _map[(a*column)+b].y = a;
        }
    }

    //�L�X�a��
    cout<<endl;
    for (int a=0;a<row;a++){
        for(int b=0;b<column;b++){
            cout<< (_map+a*(column)+b)->data<< setw(2) <<" ";
        }
        cout<<endl;
    }


    //�}�l��M�_���I
    cout<<endl<<"- - - - -"<<endl;

    wave_f.push(_map[pin[0].y*(column)+pin[0].x]);
    while(finded == 0){
        int _x = wave_f.front().x;
        int _y = wave_f.front().y;
        int _index;

        cout<<"wave_f x:"<<_x<<" y:"<<_y<<endl;

        //�k
        _index = (_y)*(column)+(_x+1);
        if( ((_x+1)>=0)&&((_x+1)<column)
        &&  ((_y)>=0) &&((_y)<row) )  //����ˬd
            {
                if(_map[_index].x == pin[1].x && _map[_index].y == pin[1].y)
                {
                        finded = 1;
                        break;
                }
                if(_map[_index].data == 0) //�ˬd�O�_���i�H�樫����
                {
                    _map[_index].data = _map[(_y)*(column)+(_x)].data + 1 ;
                    wave_f.push(_map[_index]);
                    cout<<"push �� _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }
            }
        //��
        _index = (_y)*(column)+(_x-1);
        if( ((_x-1)>=0)&&((_x-1)<column)
        &&  ((_y)>=0) &&((_y)<row) ) //����ˬd
            {
                if(_map[_index].x == pin[1].x && _map[_index].y == pin[1].y)
                {
                        finded = 1;
                        break;
                }
                if(_map[_index].data == 0)
                {
                    _map[_index].data = _map[(_y)*(column)+(_x)].data + 1;
                    wave_f.push(_map[_index]);
                    cout<<"push �k _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }
            }
        //�W
        _index = (_y+1)*(column)+(_x);
        if( ((_x)>=0)&&((_x)<column)
        &&  ((_y+1)>=0) &&((_y+1)<row) ) //����ˬd
            {
                if(_map[_index].x == pin[1].x && _map[_index].y == pin[1].y)
                {
                        finded = 1;
                        break;
                }
                if(_map[_index].data == 0)
                {
                    _map[_index].data = _map[(_y)*(column)+(_x)].data + 1;
                    wave_f.push(_map[_index]);
                    cout<<"push �W _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }
            }
        //�U
        _index = (_y-1)*(column)+(_x);
        if( ((_x)>=0)&&((_x)<column)
        &&  ((_y-1)>=0) &&((_y-1)<row) ) //����ˬd
            {
                if(_map[_index].x == pin[1].x && _map[_index].y == pin[1].y)
                {
                        finded = 1;
                        break;
                }
                if(_map[_index].data == 0)
                {
                    _map[_index].data = _map[(_y)*(column)+(_x)].data + 1;
                    wave_f.push(_map[_index]);
                    cout<<"push �U _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }
            }
        //if(wave_f.empty()!=1)
            wave_f.pop();
    }

    cout<<endl<<"- - - - -"<<endl;
    //�L�X���ܫ᪺�a��
    cout<<"  ";
    for (int a=0;a<row;a++){
        for(int b=0;b<column;b++){
            cout<< (_map+a*(column)+b)->data << dec << setw(3) ;
        }
        cout<<endl;
    }

    cout<<endl<<"- - - - -"<<endl;
    //�f�Ѹ��|
    answer_route.push_back(wave_f.front());
    while(route_finded == 0){
        int _x = answer_route.back().x;
        int _y = answer_route.back().y;
        int route_data = answer_route.back().data;
        int _index;

        cout<<"answer_route x:"<<_x<<" y:"<<_y<<endl;

        //�k
        _index = (_y)*(column)+(_x+1);
        if( ((_x+1)>=0)&&((_x+1)<column)
        &&  ((_y)>=0) &&((_y)<row) )  //����ˬd
            {
                if(_map[_index].x == pin[0].x && _map[_index].y == pin[0].y)
                {
                    route_finded = 1;
                    break;
                }
                if(_map[_index].data == route_data-1)
                {
                    answer_route.push_back(_map[_index]);
                    cout<<"push �� _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }

            }
        //��
        _index = (_y)*(column)+(_x-1);
        if( ((_x-1)>=0)&&((_x-1)<column)
        &&  ((_y)>=0) &&((_y)<row) )  //����ˬd
            {
                if(_map[_index].x == pin[0].x && _map[_index].y == pin[0].y)
                {
                    route_finded = 1;
                    break;
                }
                if(_map[_index].data == route_data-1)
                {
                    answer_route.push_back(_map[_index]);
                    cout<<"push �k _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }

            }
        //�W
        _index = (_y+1)*(column)+(_x);
        if( ((_x)>=0)&&((_x)<column)
        &&  ((_y+1)>=0) &&((_y+1)<row) )  //����ˬd
            {
                if(_map[_index].x == pin[0].x && _map[_index].y == pin[0].y)
                {
                    route_finded = 1;
                    break;
                }
                if(_map[_index].data == route_data-1)
                {
                    answer_route.push_back(_map[_index]);
                    cout<<"push �W _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }

            }
        //�U
        _index = (_y-1)*(column)+(_x);
        if( ((_x)>=0)&&((_x)<column)
        &&  ((_y-1)>=0) &&((_y-1)<row) )  //����ˬd
            {
                if(_map[_index].x == pin[0].x && _map[_index].y == pin[0].y)
                {
                    route_finded = 1;
                    break;
                }
                if(_map[_index].data == route_data-1)
                {
                    answer_route.push_back(_map[_index]);
                    cout<<"push �U _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }
            }
    }

    //���J�Y�����I
    answer_route.insert(answer_route.begin(), _map[pin[1].y*column+pin[1].x] );
    answer_route.insert(answer_route.end(), _map[pin[0].y*column+pin[0].x] );

    for(unsigned int a=1;a<answer_route.size();a++){
        if(answer_route[a].y == answer_route[a+1].y  && answer_route[a-1].x == answer_route[a].x){
            cout<<"change!! x:"<<answer_route[a].y<<" y:"<<answer_route[a].x<<endl;
            answer_route_line.push_back(answer_route[a]);
        }
        if(answer_route[a].x == answer_route[a+1].x  && answer_route[a-1].y == answer_route[a].y){
            cout<<"change!! x:"<<answer_route[a].y<<" y:"<<answer_route[a].x<<endl;
            answer_route_line.push_back(answer_route[a]);
        }
    }

    //�[�Y�[��
    answer_route_line.insert(answer_route_line.begin(),pin[1]);
    cout<<"_map[(pin[1].y*column)+pin[1].x] x:"<<_map[(pin[1].y*column)+pin[1].x].x<<" y:"<<_map[(pin[1].y*column)+pin[1].x].y<<" index:"<<(pin[1].y*column)+pin[1].x<<endl;
    cout<<"pin[1] x:"<<pin[1].x<<" y:"<<pin[1].y<<endl;
    answer_route_line.insert(answer_route_line.end(),_map[(pin[0].y*column)+pin[0].x]);

    for(unsigned int a = 0 ;a<answer_route_line.size();a++){
        cout<<"ans x:"<<answer_route_line[a].y<<" y:"<<answer_route_line[a].x<<endl;
    }

    cout<<".length "<<answer_route.size()<<endl;


    return 0;
}

