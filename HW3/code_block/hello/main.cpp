#include <iostream>
#include <fstream>
#include <string>
#include "Polynomial.h"
using namespace std;

int main()
{
    int terms,exp;
    float coef;
    string file_order;
    Polynomial a ;
    Polynomial b ;
    Polynomial c ;
//    Polynomial d ;

    string input_file_name="prog3-input-.txt";
	string output_file_name="prog3-output-.txt";
	cout<<"input the order of file"<<endl;
	cin>>file_order;
	input_file_name.insert(12, file_order);
	output_file_name.insert(13, file_order);
	ifstream fin (&input_file_name[0]);
	ofstream fout(&output_file_name[0]);
	if(!fin) {cout<<"File read Error!!"<<endl;}
	if(!fout){cout<<"File write Error!!"<<endl;}

    cout << "Hello world!" << endl;
    cout << "How many terms in a" << endl;
    fin >> terms;

    for(int counter = 0 ; counter < terms ; counter++){
        fin >> coef >> exp ;
        a.NewTerm(coef,exp);
    }
    fin >> terms;
    for(int counter = 0 ; counter < terms ; counter++){
        fin >> coef >> exp ;
        b.NewTerm(coef,exp);
    }

    c = a.Add(b);
    cout<<"a polynomial:";
    fout<<"a polynomial:";
//    a.sort_out_terms();
    a.print_all_terms();
    a.print_all_terms_in_flie(&fout);
    cout<<"b polynomial:";
    fout<<"b polynomial:";
  //  b.sort_out_terms();
    b.print_all_terms();
    b.print_all_terms_in_flie(&fout);
    cout<<"c polynomial:";
    fout<<"c polynomial:";
    c.print_all_terms();
    c.print_all_terms_in_flie(&fout);
//    c.sort_out_terms();
//    c.print_all_terms();
    cout<<"d_mult polynomial:";
 //   d = a.Mult(b);

   // d.print_all_terms();

    return 0;
}
