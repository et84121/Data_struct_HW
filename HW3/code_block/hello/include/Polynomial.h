#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

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
    protected:
    private:
        Term *termArray;  //array of nonzero terms
		int capacity ; 	   //size of termArray
		int terms ;		   //# of nonzero terms
};



#endif // POLYNOMIAL_H
