#pragma once
#include "ListSequence.h"
#include "ArraySequence.h"
#include <iostream>
#include <tuple>
#include <cstdarg>

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

int getArgsSize(int& counter ){ return counter;}
template <typename T,typename ... Types>
int getArgsSize(int& counter ,T first ,Types ... args){
    getArgsSize(counter ,args...);
    counter++;
    return counter;
}
template <size_t I=0 , typename ... TypeForTuple> 
void createTupleHelper(size_t& counter ,int& index, std::tuple<TypeForTuple...>& inTuple){
    std::cout << "end" <<std::endl;
}

template <size_t I=0 ,typename ... TypeForTuple,typename T,typename ... Types> 
void createTupleHelper(size_t& counter ,int& index, std::tuple<TypeForTuple...>& inTuple,T& first , const Types& ... args){
    std::get<I>(inTuple) = first.Get(index);
    counter++;
    createTupleHelper<I+1,TypeForTuple...>(counter,index,inTuple,args...);
}




template <typename ... TypeForTuple,typename ... Types> 
Sequence< std::tuple< TypeForTuple... > >* zip(const Types& ... args ){
    int seqSize = getFirstArg(args...).GetLength();
    //int seqCount = getArgsSize(seqCount,args...);
    MutableArraySequence< std::tuple<TypeForTuple ... > >* result = new MutableArraySequence< std::tuple<TypeForTuple ... > >(seqSize);
    for(int i =0; i< seqSize;i++){ //создать кортеж
        std::tuple<TypeForTuple...>* buf =  new std::tuple<TypeForTuple...> ;
        size_t counter =0;
        createTupleHelper<0 , TypeForTuple...>(counter,i,*buf,args...);
        result->Set( *buf, i);
        delete buf;
    }
    return result;
}

template <size_t I = 0, typename... Tail>
void printTuple(std::tuple<Tail...> tup)
{
 
    // Print element of tuple
    std::cout << std::get<I>(tup) << " ";
 
    // Go to next element
    printTuple<I + 1>(tup);
}

/*template <typename ... Types>
std::tuple< Types ... >& zipElement( const Types& ... args ){
    std::tuple< Types ... >*  result=new std::tuple< Types ... >(args...);
    return *result;
}
*/

