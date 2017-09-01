#ifndef MYSTOS_H
#define MYSTOS_H

#include <iostream>
#include <new>


using namespace std;

template <typename T>
class MyStos
{


public:


    MyStos();
    MyStos(T &data);
    bool push(T data);
    T  pop();
    T at(int x);
    T  last();

    bool isempty();
    bool isfull();
    int size();

private:

    class Item_t
    {
    public:
      //Item_t() {}
        Item_t *token_next;
        Item_t *token_prv;
        T data;
        int no;
    };


    enum { MAX = 100};
    Item_t *item;
    Item_t *head;

    int top;

};

template <typename T>
int MyStos<T>::size(){
    return top;

}
template <typename T>
bool MyStos<T>::isempty(){

    return (item == NULL);
}

template <typename T>
bool MyStos<T>::isfull(){
    return (top == MAX);

}
template <typename T>
T MyStos<T>::pop(){
    if(item != NULL){
        Item_t *temp_item = item;
        T data = item->data;
        item->token_next = NULL;
        item = item->token_prv;
        delete temp_item;
        --top;
        return data;
    }
    else {
        //return item->data;
    }
}
template <typename T>
T MyStos<T>::at(int x){
    int i;
    Item_t *temp_item = head;
    for(i = 0; i < top; i++){
        if(i < x - 1){
            temp_item =  temp_item->token_next;
        }
        else
            break;
    }
    return temp_item->data;
}





template <typename T>
T MyStos<T>::last(){
    return item->data;
}




template <typename T>
bool MyStos<T>::push(T data){
    if(item == NULL){
        item = new Item_t;
        item->token_next = NULL;
        item->token_prv = NULL;
        item->data = data;
        head = item;
        ++top;
    }
    else{
        item->token_next = new Item_t;
        item->token_next->data = data;
        item->token_next->token_prv = item;
        item->token_next->token_next = NULL;
        item =  item->token_next;
        ++top;
    }
}


template <typename T>
MyStos<T>::MyStos()
{
    item = NULL;
    top = 0;
}

template <typename T>
MyStos<T>::MyStos(T & data){
    item = new Item_t;
    item->token_prv = NULL;
    item->token_next = NULL;
    item->data = data;
    head = item;
    top = 1;

 }





#endif // MYSTOS_H
