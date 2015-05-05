#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <iomanip>
#include <vector>
#include "point.h"
#include "plane.h"

using namespace std;
//- - - - - - 第一階段用的變數
string file_order;
int row=0,column=0,pin_num=0,obs_num=0;
//行數，列數，點數，障礙數

point *pin;
plane *obs;
//- - - - - -第二階段用的變數
point *_map;
//- - - - - -第三階段用的變數
queue<point> wave_f; //wave front
vector<point> answer_route;
vector<point> answer_route_line;
int finded = 0;//有沒有找到另一個點
int route_finded = 0;


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

    //開始讀入資料

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
                fin>>in>>y>>x;
                pin[b].x = x;
                pin[b].y = y;
            }
        }
        if(in == ".obs"){
            obs_num = temp;
            obs = new plane[obs_num];
            for(int b=0;b<obs_num;b++){
                int L_x,L_y,R_x,R_y;
                fin>>in>>L_y>>L_x>>R_y>>R_x;
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
    //[end]輸出所取得的資訊


    //地圖建立
    /*  0->可以走的地
        1->為obs障礙物
        2->為pin點     */
    _map = new point [row*column];
    //將整張地圖都寫入0
    for (int a=0;a<row;a++){
        for (int b=0;b<column;b++){
            _map[(a*column)+b].data = 0;
            _map[(a*column)+b].x = b;
            _map[(a*column)+b].y = a;
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
            cout<< _map[a*(column)+b].data<< setw(2) <<" ";
        }
        cout<<endl;
    }


    //開始找尋起終點
    cout<<endl<<"- - - - -"<<endl;

    //將起點推入佇列中
    wave_f.push(_map[pin[0].y*(column)+pin[0].x]);
    //當還沒找到終點時，不斷重複迴圈
    while(finded == 0){
        int _x = wave_f.front().x;
        int _y = wave_f.front().y;
        int _index;

        cout<<"wave_f x:"<<_x<<" y:"<<_y<<endl;

        //右
        _index = (_y)*(column)+(_x+1);
        if( ((_x+1)>=0)&&((_x+1)<column)
        &&  ((_y)>=0) &&((_y)<row) )  //邊界檢查
            {
                //檢查是否為終點
                if(_map[_index].x == pin[1].x && _map[_index].y == pin[1].y)
                {
                        finded = 1;
                        break;
                }
                //檢查是否為可以行走之路
                //可以走的話  就行走並標上號碼
                if(_map[_index].data == 0)
                {
                    _map[_index].data = _map[(_y)*(column)+(_x)].data + 1 ;
                    wave_f.push(_map[_index]);
                    cout<<"push 左 _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }
            }
        //左
        _index = (_y)*(column)+(_x-1);
        if( ((_x-1)>=0)&&((_x-1)<column)
        &&  ((_y)>=0) &&((_y)<row) ) //邊界檢查
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
                    cout<<"push 右 _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }
            }
        //上
        _index = (_y+1)*(column)+(_x);
        if( ((_x)>=0)&&((_x)<column)
        &&  ((_y+1)>=0) &&((_y+1)<row) ) //邊界檢查
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
                    cout<<"push 上 _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }
            }
        //下
        _index = (_y-1)*(column)+(_x);
        if( ((_x)>=0)&&((_x)<column)
        &&  ((_y-1)>=0) &&((_y-1)<row) ) //邊界檢查
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
                    cout<<"push 下 _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }
            }
        //if(wave_f.empty())
            //推掉已經檢查過的點
            wave_f.pop();
    }

    cout<<endl<<"- - - - -"<<endl;

    //印出改變後的地圖
    cout<<" ";
    for (int a=0;a<row;a++){
        for(int b=0;b<column;b++){
            cout<< (_map+a*(column)+b)->data << dec << setw(3) ;
        }
        cout<<endl;
    }
    //印出改變後的地圖[End]


    cout<<endl<<"- - - - -"<<endl;


//逆解路徑 answer_route 為一個 vector 容器

    answer_route.push_back(wave_f.front());
    //當還沒找到起點時  持續進行此迴圈
    while(route_finded == 0){
        int _x = answer_route.back().x;
        int _y = answer_route.back().y;
        int route_data = answer_route.back().data;
        int _index;

        cout<<"answer_route x:"<<_x<<" y:"<<_y<<endl;

        //右
        _index = (_y)*(column)+(_x+1);
        if( ((_x+1)>=0)&&((_x+1)<column)
        &&  ((_y)>=0) &&((_y)<row) )  //邊界檢查
            {
                //檢查是否找到起點
                if(_map[_index].x == pin[0].x && _map[_index].y == pin[0].y)
                {
                    route_finded = 1;
                    break;
                }
                //逆解編碼
                if(_map[_index].data == route_data-1 && route_data -1 != answer_route.back().data)
                {
                    answer_route.push_back(_map[_index]);
                    cout<<"push 左 _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }

            }
        //左
        _index = (_y)*(column)+(_x-1);
        if( ((_x-1)>=0)&&((_x-1)<column)
        &&  ((_y)>=0) &&((_y)<row) )  //邊界檢查
            {
                if(_map[_index].x == pin[0].x && _map[_index].y == pin[0].y)
                {
                    route_finded = 1;
                    break;
                }
                if(_map[_index].data == route_data-1 && route_data -1 != answer_route.back().data)
                {
                    answer_route.push_back(_map[_index]);
                    cout<<"push 右 _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }

            }
        //上
        _index = (_y+1)*(column)+(_x);
        if( ((_x)>=0)&&((_x)<column)
        &&  ((_y+1)>=0) &&((_y+1)<row) )  //邊界檢查
            {
                if(_map[_index].x == pin[0].x && _map[_index].y == pin[0].y)
                {
                    route_finded = 1;
                    break;
                }
                if(_map[_index].data == route_data-1 && route_data -1 != answer_route.back().data)
                {
                    answer_route.push_back(_map[_index]);
                    cout<<"push 上 _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }

            }
        //下
        _index = (_y-1)*(column)+(_x);
        if( ((_x)>=0)&&((_x)<column)
        &&  ((_y-1)>=0) &&((_y-1)<row) )  //邊界檢查
            {
                if(_map[_index].x == pin[0].x && _map[_index].y == pin[0].y)
                {
                    route_finded = 1;
                    break;
                }
                if(_map[_index].data == route_data-1 && route_data -1 != answer_route.back().data)
                {
                    answer_route.push_back(_map[_index]);
                    cout<<"push 下 _index:"<<_index<<" x:"<<_map[_index].x<<" y:"<<_map[_index].y<<" data:"<<_map[_index].data<<endl;
                }
            }
    }

    //插入頭尾的點
    answer_route.insert(answer_route.begin(), _map[pin[1].y*column+pin[1].x] );
    answer_route.insert(answer_route.end(), _map[pin[0].y*column+pin[0].x] );
    //檢查轉彎的點  把轉彎的poing 抓出來
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

    //加頭加尾
    answer_route_line.insert(answer_route_line.begin(),pin[1]);
    answer_route_line.insert(answer_route_line.end(),_map[(pin[0].y*column)+pin[0].x]);

    cout<<".edge "<<answer_route_line.size()-1<<endl;

    for(int a = (int)answer_route_line.size()-2;a>=0;a--){
        cout<<answer_route_line[a+1].y<<" "<<answer_route_line[a+1].x<<" "<<answer_route_line[a].y<<" "<<answer_route_line[a].x<<endl;
    }

    cout<<".length "<<answer_route.size()-1<<endl;

    //完成指定格式的資料輸出

    fout<<".edge "<<answer_route_line.size()-1<<endl;
    for(int a = (int)answer_route_line.size()-2;a>=0;a--){
        fout<<answer_route_line[a+1].y<<" "<<answer_route_line[a+1].x<<" "<<answer_route_line[a].y<<" "<<answer_route_line[a].x<<endl;
    }
    fout<<".length "<<answer_route.size()-1<<endl;

    //完成指定格式的資料輸出[End]

    return 0;
}
