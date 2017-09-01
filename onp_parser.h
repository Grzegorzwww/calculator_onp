#ifndef ONP_PARSER_H
#define ONP_PARSER_H

#include <math.h>
#include <ctime>
#include <typeinfo>
#include <stdlib.h>
#include <list>
#include <mystos.h>
#include <map>


typedef enum {Znak, Liczba} Tokentype_t;


class ONP_Token
{

private:

    char znak;
    double value;

    Tokentype_t token_type;

public:






    ONP_Token(Tokentype_t _type, double val = 0.0, char zn = '\0')  {

        if(_type == Liczba){
            znak = '\0';
            value = val;
            token_type  = _type;
            //cout << "konstruktor normalny LICZBA "<<endl;
        }else if(_type == Znak){
            znak = zn;
            value = 0.0;
            token_type  = _type;
            //    cout << "konstruktor normalny ZNAK "<<endl;
        }
    }
    ONP_Token() {/*cout << "pusty konstruktor !"<<endl;*/}


    ONP_Token(const  ONP_Token & obj){
        znak = obj.znak;
        value = obj.value;
        token_type = obj.token_type;
    }

    ONP_Token operator=(ONP_Token f){
        if(this == &f){
            return *this;
        }
        this->value = f.value;
        this->znak = f.znak;
        this->token_type = f.token_type;
        return *this;
    }

    friend ostream & operator<<(ostream &os, ONP_Token &f);
    friend bool addOPToStack(MyStos<ONP_Token> &stos, MyStos<ONP_Token> &wy, ONP_Token &token_to_add);
    friend bool CountONP(MyStos<ONP_Token> &stack, double &wynik);


    friend void show(MyStos<ONP_Token> &to_disp);

};


class ONP_Parser
{

public:
    ONP_Parser();
    ONP_Parser(string str);
    void getEqualtion(string str);
    double ans();
private:

    string Equation;



};

#endif // ONP_PARSER_H
