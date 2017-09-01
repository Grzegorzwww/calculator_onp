#include "onp_parser.h"



/*
 * Autor Grzegorz Warchol
 * grzegorzw@is.net.pl
* Wyrażenie ONP przeglądamy od strony lewej do prawej. Jeśli napotkamy liczbę, to umieszczamy ją na stosie.
* Jeśli napotkamy operator, to ze stosu pobieramy dwie ostatnie liczby,
* wykonujemy na nich działanie zgodne z napotkanym operatorem i wynik umieszczamy z powrotem na stosie.
* Gdy wyrażenie zostanie przeglądnięte do końca, na szczycie stosu będzie znajdował się jego wynik.
*
* Konwersja z Konwencionalnej na ONP
* jeśli element jest liczbą, to trafia on bezpośrednio do reprezentacji wyjściowej wyrażenia
* jeśli element jest operatorem, to trafia na stos, wpierw jednak, ze stosu zdejmowane są kolejno wszystkie operatory,
* których priorytet jest większy bądź równy priorytetowi operatora, który ma być włożony na stos i trafiają one do reprezentacji wyjściowej
* jeśli element jest nawiasem otwierający, to trafia on na stos
* jeśli element jest nawiasem zamykającym, to ze stosu zdejmowane są wszystkie elementy, aż do pierwszego nawiasu otwierającego.
*  Elementy te trafiają do reprezentacji wyjściowej. Nawiasy – otwierający i zamykający – są pomijane.
* na koniec wszystkie elementy pozostałe na stosie, dopisywane są do reprezentacji wyjściowej
*
operator(y)	priorytet
*  ^	4
*  * /	3
*  + –	2
*  =	1
*  (	0
*
*/


ONP_Parser::ONP_Parser()
{



}

ONP_Parser::ONP_Parser(string str) : Equation(str)
{
}

void  ONP_Parser::getEqualtion(string str){


    int i;
    for(i = 0; i < str.size() - 1;i++){
        if(!isspace(str.at(i))){
            if(!isspace(str.at(i+1))){
                if((isdigit(str.at(i)) && isdigit(str.at(i+1)))){
                    continue;
                }else {
                    str.insert(i+1, " ", 1);
                }
            }
        }
    }
    cout << str<<endl;
    Equation = str;

}



double ONP_Parser::ans(){

    string text_in;
    string znak;
    char possible_chars[7] = {'^', '*', '/','+','-','(',')'};
    char temp_char_array[128];
    int j = 0;

    MyStos<ONP_Token> wyjscie;
    MyStos<ONP_Token> stos;

    if(!Equation.empty()){
        text_in = Equation;
    }else{
        cerr << "Brak lub zle wpisane rownanie "<<endl;
    }


    for(int i = 0; i <= text_in.size(); i++){
        znak = text_in[i];
        if(isspace(*znak.c_str()) || (i == text_in.size() )){
            if(j > 0){
                double liczba = atof(temp_char_array);
                //cout << "liczba = "<< liczba << endl;
                ONP_Token token(Liczba, liczba, '\0');
                wyjscie.push(token);
            }
            j = 0;
            continue;
        }

        if(!isdigit(*znak.c_str())  && !isspace(*znak.c_str()) && *znak.c_str() != '.'){
            int k = 0;
            while(k < 7 ){
                if(*znak.c_str() == possible_chars[k]){
                    //cout << "possible_chars[k] "<<possible_chars[k];
                    ONP_Token token(Znak, 0.0, possible_chars[k]);
                    addOPToStack(stos, wyjscie, token);
                }
                k++;
            }
        }
        else if(isdigit(*znak.c_str()) || *znak.c_str() == '.'){
            temp_char_array[j++] = *znak.c_str();
        }
    }

    if(!stos.isempty()){
        ONP_Token temp;
        for(int i = 0; i < stos.size() +1; i++){
            temp = stos.pop();
            wyjscie.push(temp);
        }
    }

    //show(stos);
    //show(wyjscie);

    MyStos<ONP_Token> wyjscie_2;
    while(!wyjscie.isempty()){
        wyjscie_2.push(wyjscie.pop());
    }

    double ans= 0 ;
    //cout << "wyjscie_2.size() = "<<wyjscie_2.size()<<endl;
    CountONP(wyjscie_2, ans);
    //cout << "ans = "<<ans<<endl;

    return ans;


}








 bool CountONP(MyStos<ONP_Token> &stack, double &wynik){
     int i;
     MyStos<double> count_stack;
     ONP_Token temp_token;
     double ans;
     double x, y;

     while( !stack.isempty()){
         temp_token = stack.pop();

         switch(temp_token.token_type)
         {
         case Liczba :
             count_stack.push(temp_token.value);
             break;
         case Znak :
             x = count_stack.pop();
             y = count_stack.pop();
             switch(temp_token.znak)
             {
             case '+':
                 ans = (x + y);
                 count_stack.push(ans);
                 if(count_stack.size() == 1 ) wynik = ans;
                 break;
             case '-':
                 ans = (x - y);
                 count_stack.push(ans);
                 if(count_stack.size() == 1 ) wynik = ans;
                 break;
             case '*':
                 ans = (x * y);
                 count_stack.push(ans);
                 if(count_stack.size() == 1 ) wynik = ans;
                 break;
             case '/':
                 if(y != 0){
                     ans = (x / y);
                     count_stack.push(ans);
                     if(count_stack.size() == 1 ) wynik = ans;
                 }else{
                     count_stack.push(0);
                     if(count_stack.size() == 1 ) wynik = ans;
                 }
                 break;
             case '^':
                 ans = pow(x, y);
                 count_stack.push(ans);
                 if(count_stack.size() == 1 ) wynik = ans;
                 break;
             }
         }
         if(count_stack.isempty()){
             return true;
         }
     }
 }



 bool addOPToStack( MyStos<ONP_Token> &stos, MyStos<ONP_Token> &wy, ONP_Token &token_to_add){
     map<char, unsigned char> chars_priority;
     chars_priority[')'] = 1;
     chars_priority['('] = 1;
     chars_priority['-'] = 2;
     chars_priority['+'] = 2;
     chars_priority['/'] = 3;
     chars_priority['*'] = 3;
     chars_priority['^'] = 4;

     ONP_Token temp;
     int stack_priority = 0;
     int token_priority = 0;
     if(!stos.isempty()){
         if(stos.last().token_type == Znak ){
             if(token_to_add.znak == '('){
                 stos.push(token_to_add);
                 return true;
             }
             if(token_to_add.znak == ')'){
                 if(!stos.isempty() ){
                     temp = stos.pop();
                     while( temp.znak != '('){
                         wy.push(temp);
                         temp = stos.pop();
                     }
                 }
                 if(!stos.isempty() && stos.last().znak == '(')
                     stos.pop();
                 return true;
             }
             else{
                 while(!stos.isempty()){
                     stack_priority = (int )chars_priority[stos.last().znak];
                     token_priority = (int)chars_priority[token_to_add.znak];
                     if(stack_priority >= token_priority){
                         temp = stos.pop();
                         wy.push(temp);
                         continue;
                     }
                     else
                         break;
                 }
                 stos.push(token_to_add);
             }
         }
     }
     else {
         stos.push(token_to_add);
     }
     return true;
 }
















 ostream & operator<<(ostream &os, ONP_Token &f)
 {
     os <<": ("<<f.znak<<", "<<f.value<<")" <<endl;
     return os;
 }

 void show(MyStos<ONP_Token> &to_disp){

     while(!to_disp.isempty()){
         if( to_disp.last().token_type == Znak){
             cout << to_disp.last().znak <<", ";
         }else if(to_disp.last().token_type == Liczba){
             cout << to_disp.last().value <<", ";
         }
         to_disp.pop();
     }
     cout << endl;
 }

