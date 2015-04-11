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
        Polynomial Add(Polynomial poly);
		Polynomial Mult(Polynomial poly);
		void NewTerm(const float theCoeff, const int theExp);
		void print_all_terms();
		void print_all_terms_in_flie(std::ofstream *fout);
    protected:
    private:
        Term *termArray;  //array of nonzero terms
		int capacity ; 	   //size of termArray
		int terms ;		   //# of nonzero terms
};



#endif // POLYNOMIAL_H
