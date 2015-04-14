#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <fstream>


class Polynomial;

class Term {
	friend Polynomial;

	private:
		float coef;//coefficient
		int exp;   //exponet
};

class Polynomial
{
    public:
        Polynomial();
        ~Polynomial();
        Polynomial Add(Polynomial poly);//加法
		Polynomial Mult(Polynomial poly);//乘法((未完成
		void NewTerm(const float theCoeff, const int theExp);
		void print_all_terms();//印到螢幕上
		void print_all_terms_in_flie(std::ofstream *fout);//印到檔案指標裡
		void sort_out_terms();//合併相同次方的項
//		void sort_terms();
    protected:
    private:
        Term *termArray;  //array of nonzero terms
		int capacity ; 	   //size of termArray
		int terms ;		   //# of nonzero terms
		int unsorted;//是否未排列
};



#endif // POLYNOMIAL_H
