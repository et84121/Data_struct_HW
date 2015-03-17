#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int funtion(int a){
	int count = 1;
	cout << a << " ";
	while (a>1){
		if (a % 2 == 1){
			a = (3 * a) + 1;
		}
		else{
			a = a / 2;
		}
		count += 1;
		cout << a << " ";
	}
	cout << "count=" << count << endl;
	return count;
}

int f_max_count(int a, int b){
	int max_count = 0;
	//To sure that a is bigger than b
	if (b>a){
		int c = b;
		b = a; a = c;
	}

	for (int j = a; a >= b; a--){
		int temp = funtion(a);
		max_count = temp>max_count ? temp : max_count;
	}
	cout << "max=" << max_count << endl;
	return max_count;
}

int main() {
	int a, b;
	string file_order;
	while (1){
		string input_file_name = "prog1-input-.txt";
		string output_file_name = "prog1-output-.txt";
		cout << "input the order of file" << endl;
		cin >> file_order;
		input_file_name.insert(12, file_order);
		output_file_name.insert(13, file_order);
		ifstream fin(&input_file_name[0]);
		ofstream fout(&output_file_name[0]);
		if (!fin) { cout << "File read Error!!" << endl; }
		if (!fout){ cout << "File write Error!!" << endl; }

		while ((fin >> a >> b) && (a != 0) && (b != 0)){
			fout << a << " " << b << " " << f_max_count(a, b) << endl;
		}
		cout << "The end." << endl << endl;
	}
}