#pragma once
#include "ListSequence.h"
#include "ArraySequence.h"
#include <iostream>
#include <tuple>
#include <cstdarg>

template <typename T,typename U,typename ... Types>
Sequence<U>& map(const Sequence<T>& seq, U (*func)( T,const Types& ...),const Types&...tail){
    MutableArraySequence<U>* result = new MutableArraySequence<U>(seq.GetLength());
    for(int i =0;i<seq.GetLength();i++){
        (*result)[i]=(*func)(seq.Get(i),tail...);
    }
    return *result;
    
}

template <typename T,typename ... Types>
Sequence<T>& where(const Sequence<T>& seq, bool (*func)( T ,const Types& ...),const Types&...tail){
    MutableArraySequence<T>* result = new MutableArraySequence<T>();
    for(int i =0;i<seq.GetLength();i++){
        if((*func)(seq.Get(i), tail...)==true){
            result->Append(seq.Get(i));
        }
    }
    return *result;
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

                //Пока не нужна , переделать через sizeof хвоста
int getArgsSize(int& counter ){ return counter;}

template <typename T,typename ... Types>
int getArgsSize(int& counter ,T first ,Types ... args){
    getArgsSize(counter ,args...);
    counter++;
    return counter;
}
/*template <size_t I=0 , typename ... TypeForTuple,typename First> 
void zipTupleHelper(size_t& counter ,int& index, Tuple_<TypeForTuple...>& inTuple,const First& first){
    Get<I>(inTuple) = first.Get(index);
    counter++;
}*/

                               
template <size_t I=0 , typename ... TypeForTuple> 
void zipTupleHelper(size_t& counter ,int& index, Tuple_<TypeForTuple...>& inTuple){}


template <size_t I=0 ,typename ... TypeForTuple,typename First,typename ... Types> 
void zipTupleHelper(size_t& counter ,int& index, Tuple_<TypeForTuple...>& inTuple,const First& first , const Types& ... args){
    Get<I>(inTuple) = first.Get(index);
    counter++;
    zipTupleHelper<I+1,TypeForTuple...>(counter,index,inTuple,args...);
}
                    // попытаться сделать самостоятельное определение типов
template <typename ... TypeForTuple,typename ... Types> 
Sequence< Tuple_< TypeForTuple... > >* zip(const Types& ... args ){
    //реализовать поиск меньшего массива
    int seqSize = getFirstArg(args...).GetLength();
    MutableArraySequence< Tuple_<TypeForTuple ... > >* result = new MutableArraySequence< Tuple_<TypeForTuple ... > >(seqSize);
    for(int i =0; i< seqSize;i++){ //создать кортеж
        Tuple_<TypeForTuple...>* buf =  new Tuple_<TypeForTuple...> ;
        size_t counter =0;
        zipTupleHelper<0 , TypeForTuple...>(counter,i,*buf,args...);
        result->Set( *buf, i);
        delete buf;
    }
    return result;
}


/*
template <size_t I=0 ,typename ... Types,typename ... TypeForTuple > 
void unzipTupleHelper(size_t& counter ,int& length,Tuple_< MutableArraySequence<TypeForTuple>*...>& inTuple,Sequence< Tuple_< TypeForTuple... > >& toUnzip){
    MutableArraySequence<First>* buf  = new MutableArraySequence<First>;
    Get<I>(inTuple) = buf;
    for(int i =0;i<length-1 ;i++){
        buf->Set(Get<I>(toUnzip.Get(i)),i);
    }
    counter++;
}

template <size_t I=0 ,typename First,typename ... TypeForTuple > 
void unzipTupleHelper(size_t& counter ,int& length,Tuple_< MutableArraySequence<TypeForTuple>*...>& inTuple,Sequence< Tuple_< TypeForTuple... > >& toUnzip){
    MutableArraySequence<First>* buf  = new MutableArraySequence<First>;
    Get<I>(inTuple) = buf;
    for(int i =0;i<length-1 ;i++){
        buf->Set(Get<I>(toUnzip.Get(i)),i);
    }
    counter++;
}
template <size_t I=0 ,typename First,typename ... Types,typename ... TypeForTuple> 
void unzipTupleHelper(size_t& counter ,int& length,Tuple_< MutableArraySequence<TypeForTuple>*...>& inTuple,Sequence< Tuple_< TypeForTuple... > >& toUnzip)
{
    MutableArraySequence<First>* buf  = new MutableArraySequence<First>();
    std::cout<<"__3"<<std::endl;
    Get<I>(inTuple) = buf;
    std::cout<<"__3"<<std::endl;
    for(int i =0;i<length ;i++){
        std::cout<<"__"<<std::endl;
        buf->Set(Get<I>(toUnzip.Get(i)),i);
    }
    //buf->PrintSequence();
    counter++;
    unzipTupleHelper<I+1,Types...>(counter,length,inTuple,toUnzip);
}

template <typename ... TypeForTuple> 
Tuple_< MutableArraySequence<TypeForTuple>*...>*  unzip(Sequence< Tuple_< TypeForTuple... > >& toUnzip){
    Tuple_< MutableArraySequence<TypeForTuple>*...>* result = new Tuple_< MutableArraySequence<TypeForTuple>*...>;
    int seqLength = toUnzip.GetLength();
   // std::cout<<seqLength<<std::endl;
    size_t counter=0;
    std::cout<<"__2"<<std::endl;
    unzipTupleHelper<0,TypeForTuple... >(counter,seqLength,*result,toUnzip);
    std::cout<<"__1"<<std::endl;
    return result;
}
*/


template <size_t I = 0, typename... Tail> 
typename std::enable_if_t<( I >= sizeof...(Tail) )> printTuple(Tuple_<Tail...> tup)//enable if создаёт тип при условии 
{
    return;
}
template <size_t I = 0, typename... Tail> 
typename std::enable_if_t<( I < sizeof...(Tail) )>  printTuple(Tuple_<Tail...> tup)
{
    std::cout << Get<I>(tup) << " ";
    printTuple<I + 1>(tup);
}
template <typename ... TypeForTuple> 
using Tuple_=Tuple<0,TypeForTuple...>;

