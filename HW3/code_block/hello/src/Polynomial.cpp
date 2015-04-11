#include "Polynomial.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Polynomial::Polynomial()
{
    //ctor
    capacity = 1 ; 	   //size of termArray
    terms = 0;
}

Polynomial::~Polynomial()
{
    //dtor
}

void Polynomial::print_all_terms(){
    for (int counter = 0 ; counter < terms; counter++){
        std::cout<<termArray[counter].coef<<"X^"<<termArray[counter].exp<<" ";
        if(counter<terms-1){
            std::cout<<"+ ";
        }
    }
    std::cout<<std::endl;
}
void Polynomial::print_all_terms_in_flie(std::ofstream *fout){
    for (int counter = 0 ; counter < terms; counter++){
        *fout<<termArray[counter].coef<<"X^"<<termArray[counter].exp<<" ";
        if(counter<terms-1){
            *fout<<"+ ";
        }
    }
   *fout<<std::endl;
}

Polynomial Polynomial::Add(Polynomial b)
{
    //return the sum of *this and b
    Polynomial c;
    int aPos = 0;
    int bPos = 0;
    while((aPos<terms)&&(bPos<b.terms))
    {
        if (termArray[aPos].exp == b.termArray[bPos].exp){
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if(t) c.NewTerm(t,termArray[aPos].exp);
            aPos++; bPos++;
        }else if (termArray[aPos].exp<b.termArray[bPos].exp){
            c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
            bPos++;
        }else {
            c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++;
        }
    }
    for(;aPos<terms;aPos++){
        c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
    }
    for(;bPos<b.terms;bPos++){
        c.NewTerm(termArray[bPos].coef,termArray[bPos].exp);
    }
    return c;
}

Polynomial Polynomial::Mult(Polynomial b){
    Polynomial c;

    return c;
}

void Polynomial::NewTerm(const float theCoeff, const int theExp)
{// Add a new term to the end of termArray
    if(terms == capacity || terms == 0)
    {// double capacity of termArray
        capacity *= 2;
        Term *temp = new Term[capacity];// new array
        std::copy(termArray, termArray + terms, temp);
        delete[] termArray;// deallocate old memory
        termArray = temp;
    }
    termArray[terms].coef = theCoeff;
    termArray[terms].exp = theExp;
    terms++;
}// end of NewTerm

