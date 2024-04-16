#pragma once
#include "ListSequence.h"
#include "ArraySequence.h"
#include "MyTuple.h"
#include <iostream>


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

                               
template <size_t I=0 , typename ... TypeForTuple,typename ... Types> 
void zipTupleHelper(size_t& counter ,int& index, Tuple_<TypeForTuple...>& inTuple,const Types& ... args){}


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



template <size_t I=0,typename First,typename ... TypeForTuple> 
void unzipTupleHelper(size_t& counter,int& length,Tuple_< MutableArraySequence<TypeForTuple>*...>& inTuple,Sequence< Tuple_< TypeForTuple... > >& toUnzip)
{
    MutableArraySequence<First>* buf  = new MutableArraySequence<First>(length);
    Get<I>(inTuple) = buf;
    for(int i =0;i<length ;i++){
        buf->Set(Get<I>(toUnzip[i]),i);
    }
    std::cout<<"последний" <<std::endl;
    counter++;

}

template <size_t I=0 ,typename First,typename Second,typename ... Types,typename ... TypeForTuple> 
void unzipTupleHelper(size_t& counter,int& length,Tuple_< MutableArraySequence<TypeForTuple>*...>& inTuple,Sequence< Tuple_< TypeForTuple... > >& toUnzip)
{
    MutableArraySequence<First>* buf  = new MutableArraySequence<First>(length);
    Get<I>(inTuple) = buf;
    for(int i =0;i<length ;i++){
        buf->Set(Get<I>(toUnzip[i]),i);
    }
    counter++;
    std::cout<<sizeof...(Types) <<"осталось"<<std::endl;
    //buf->PrintSequence();
    unzipTupleHelper<I+1,Second,Types...>(counter,length,inTuple,toUnzip);
}

template <typename ... TypeForTuple> 
Tuple_< MutableArraySequence<TypeForTuple>*...>*  unzip(Sequence< Tuple_< TypeForTuple... > >& toUnzip){
    Tuple_< MutableArraySequence<TypeForTuple>*...>* result = new Tuple_< MutableArraySequence<TypeForTuple>*...>;
    int seqLength = toUnzip.GetLength();
    size_t counter=0;
    unzipTupleHelper<0,TypeForTuple...>(counter,seqLength,*result,toUnzip);
    return result;
}




