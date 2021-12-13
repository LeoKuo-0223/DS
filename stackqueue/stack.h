#include<iostream>
#define NUM 50
using namespace std;

template<class T>
class Stack{    //declare the Stack Class
   public:
         Stack();
         bool isEmpty() const;
         void push(T);
         void pop();
         T Top() const;
     private:
         int top;
         T *array = new T[NUM];
 };

template<class T>
Stack<T>::Stack(){ //constructor of Stack class
     top=-1;         //empty stack with top value -1
}

template<class T>
bool Stack<T>::isEmpty() const{        //read only function for checking the stack is empty or not
     return top== -1;
}

template<class T>
void Stack<T>::push(T item){          //push integer into the stack
     if(top==top-1) cout<<"stack is full";
     else array[++top]=item;
}

template<class T>
void Stack<T>::pop(){      //pop out the top object from stack
     if(isEmpty()); //cout<<"stack is empty";
     else array[top--];
 }

template<class T>
T Stack<T>::Top() const{     //read the top object in the stack
     if(isEmpty()) ;//cout<<"stack is empty";
     else {
         return array[top];
     }
 }
