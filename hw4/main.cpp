#include <iostream>
#include <fstream>
#include <string>
#include "point.h"
#include "plane.h"

using namespace std;

string file_order;
int row=0,column=0,pin_num=0,obs_num=0;
//行數，列數，點數，障礙數

int *_map;

point *pin;
plane *obs;

int check_obs(int,int);

int main()
{
    string input_file_name="prog4-input-.txt";
    string output_file_name="prog4-output-.txt";
    //開讀檔名
	cout<<"input the order of file"<<endl;
	cin>>file_order;
	//輸入要讀取的檔案序
	input_file_name.insert(12, file_order);
	output_file_name.insert(13, file_order);
	//合成真正的檔名
	ifstream fin (&input_file_name[0]);
	ofstream fout(&output_file_name[0]);
	//開讀寫檔案流
	if(!fin) {cout<<"File read Error!!"<<endl;}
	if(!fout){cout<<"File write Error!!"<<endl;}
    //檢查是否開流成功
    cout << "program start!" << endl;

    //while(obs_num == 0)
    for(int a=0;a<4;a++)
    {
        //建立區域變數(儲存輸入值用)
        string in;int temp;
        fin>>in>>temp;
        cout<<in<<" "<<temp<<endl;
        //判斷
        if(in == ".row"){row = temp;}
        if(in == ".column"){column = temp;}
        if(in == ".pin"){
            //將 總數 存入 點數 中
            pin_num = temp;
            //動態建立 點 陣列
            pin = new point[pin_num];
            //將檔案中的資訊存入 點_陣列 中
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
    //輸出所取得的資訊
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

    //地圖建立
    /*  0->可以走的地
        1->為obs障礙物
        2->為pin點     */
    _map = new int [row*column];
    //將整張地圖都寫入0
    for (int a=0;a<row;a++){
        for (int b=0;b<column;b++){
            *(_map+a*(column)+b)=0;

        }
    }
    //標示障礙物
    for (int a=0;a<obs_num;a++){
        obs[a].write_into_map(_map,row,column);
    }
    //標示點
    for (int a=0;a<pin_num;a++){
        pin[a].write_into_map(_map,row,column);
    }

    //印出地圖
    cout<<endl;
    for (int a=0;a<row;a++){
        for(int b=0;b<column;b++){
            cout<<*(_map+a*(column)+b)<<" ";
        }
        cout<<endl;
    }

    return 0;
}

