#pragma once
#include "ListSequence.h"
#include "ArraySequence.h"
#include <iostream>
#include <tuple>
template <typename T,typename U,typename ... Types>
Sequence<U>* map(const Sequence<T>& seq, U (*func)(T,Types ...),Types...tail){
    MutableArraySequence<U>* result = new MutableArraySequence<U>[seq.GetLength()];
    for(int i =0;i<seq.GetLength();i++){
        result[i]=(*func)(seq.Get(i),const tail&...);
    }
    return result;
    
}

template <typename T,typename ... Types>
Sequence<T>* where(const Sequence<T>& seq, bool (*func)(T,Types ...),Types...tail){
    MutableArraySequence<T>* result = new MutableArraySequence<T>();
    for(int i =0;i<seq.GetLength();i++){
        if((*func)(seq.Get(i),const tail&...)==true){
            result->Append(seq.Get(i));
        }
    }
    return result;
}

template <typename T>
T reduce(const Sequence<T>& seq, T (*func)(const T&,const T&),T start ){
    for(int i=0;i<seq.GetLength();i++){
        start = (*func)(start,seq.Get(i));
    }
    return start;
}

template <typename T , typename ... Types>
const T& getFirstArg(const T& first , const Types& ... args){
    return first;
}

template <typename T , typename ... Types>
int getArgsSize(int& counter,const T& first , const Types& ... args){
    getArgsSize(counter,args...,);
    counter++;
    return counter;
}

template <typename T , typename ... Types>
int getArgsSize(std::tuple<T,T,T>,const T& first , const Types& ... args){
    
    getArgsSize(counter,args...,);
    return counter;
}

template <typename T , typename ... Types>
Sequence<T>* zip(const T& example, const Types& ... args ){
    int seqSize = getFirstArg(args...).GetLength();
    int seqCount = 0; 
    getArgsSize(seqCount,args...);
    MutableArraySequence<T> result = new  MutableArraySequence<T>(seqSize);
    for(int i =0; i<size;i++){
        std::tuple <Types...>
        result->Set( , i);
    }
}

template <typename ... Types>
std::tuple< Types ... >& zipElement( const Types& ... args ){
    std::tuple< Types ... >  result(args...);
    return result;
}
