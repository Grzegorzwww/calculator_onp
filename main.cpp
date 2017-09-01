
#include <iostream>
#include <onp_parser.h>

using namespace std;

int main(int argc, char *argv[])
{



        ONP_Parser * parser = new ONP_Parser();

        string text;
        cout<<"Wprowadz rownanie (q aby zakonczyc): ";
        std::getline (std::cin, text);
        while(text.at(0) != 'q'){
            parser->getEqualtion(text);
            cout  << text<< " = ";
            cout <<"ans: " << parser->ans()<<endl;
            cout<<"Wprowadz rownanie (q aby zakonczyc): ";
            std::getline (std::cin, text);
        }
        delete parser;
}
