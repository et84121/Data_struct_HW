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
        Polynomial Add(Polynomial poly);//�[�k
		Polynomial Mult(Polynomial poly);//���k((������
		void NewTerm(const float theCoeff, const int theExp);
		void print_all_terms();//�L��ù��W
		void print_all_terms_in_flie(std::ofstream *fout);//�L���ɮ׫��и�
		void sort_out_terms();//�X�֬ۦP���誺��
//		void sort_terms();
    protected:
    private:
        Term *termArray;  //array of nonzero terms
		int capacity ; 	   //size of termArray
		int terms ;		   //# of nonzero terms
		int unsorted;//�O�_���ƦC
};



#endif // POLYNOMIAL_H
