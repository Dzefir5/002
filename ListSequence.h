#pragma once
#include <stdexcept>
#include <iostream>
#include "LinkedList.h"
#include "Sequence.h"
#include "MyAbs.h"



template <typename T> 
class ListSequence : public Sequence<T>{
protected:
    LinkedList<T>* data;
    virtual  ListSequence<T>* Instance()=0 ;
    virtual const  ListSequence<T>* Instance() const =0;

    ListSequence<T>* appendWithoutInstance(const T& item) {
        ListSequence<T>* result=this;
        result->data->Append(item);
        return result;
    }
public:
    ListSequence (){
        this->data=new LinkedList<T>();
    }
    ListSequence (int count){
        this->data=new LinkedList<T>(count);
    }
    ListSequence (T* items, int count){
        this->data=new LinkedList<T>(items,count);
    }
    ListSequence (const T& elemFill, int count){
        this->data=new LinkedList<T>(elemFill,count);
    }
    ListSequence (const LinkedList<T>& list){
        this->data=new LinkedList<T>(list);
    }
    ListSequence (LinkedList<T>* list){
        this->data=list;
    }
    ListSequence (const Sequence<T>& seq){
        this->data = new LinkedList<T>();
        for(int i =0;i<seq.GetLength();i++){
            appendWithoutInstance(seq.Get(i));
        }
    }

    T GetFirst() const override{
        return this->data->GetFirst();
    }
    T GetLast() const override{
        return this->data->GetLast();
    }
    T Get(int index) const override{
        return this->data->Get(index);
    }

    ListSequence<T>* Set(const T& value,int index) override{
        ListSequence<T>* result = Instance();
        result->data->Set(value,index);
        return result;
    }

    int GetLength() const override{
        return this->data->GetLength();
    }
    ListSequence<T>* Append(const T& item) override{
        ListSequence<T>* result = Instance();
        result->data->Append(item);
        return result;
    }
    ListSequence<T>* Prepend(const T& item) override{
        ListSequence<T>* result = Instance();
        result->data->Prepend(item);
        return result;
    }
    ListSequence<T>* InsertAt(const T& item, int index) override{
        ListSequence<T>* result = Instance();
        result->data->InsertAt(item,index);
        return result;
    }
    ListSequence<T>* RemoveAt(int index) override{
        ListSequence<T>* result = Instance();
        result->data->RemoveAt(index);
        return result;
    }

    ListSequence<T>* Slice(int index, int offset ,const Sequence<T> &seq ) override {
        ListSequence<T>* result = Instance();
        if( MyAbs(index)>=result->GetLength()) throw std::invalid_argument("");
        int start =0 ;
        if(index<0) { start =result->GetLength() + index;  } else { start = index; }
        int i =start;
        for( ; i< std::min(result->GetLength() ,  start+seq.GetLength() );i++) {
            result->data->Set(seq.Get(i-start),i);
        }   
        int removeCount =0;
        for( ;(i< std::min(result->GetLength() ,  start+offset ) ) && ( removeCount<offset-seq.GetLength() );removeCount++){
            result->data->RemoveAt(i);
        }
        return result;
    }

    T& operator[](int index) override{
        return (*(Instance()->data))[index];
    }

    virtual ~ListSequence<T>(){
        delete data;
    }
};

template<typename T>
class MutableListSequence : public ListSequence<T>{
private:
    ListSequence<T>* Instance() override {
        return static_cast<ListSequence<T>*>(this);
    }
    const  ListSequence<T>* Instance() const override  {
        return static_cast<const ListSequence<T>*>(this);
    }
    MutableListSequence<T>* appendWithoutInstance(const T& item) {
        MutableListSequence<T>* result=this;
        result->data->Append(item);
        return result;
    }
public:
    using ListSequence<T>::ListSequence;

     MutableListSequence (const  MutableListSequence<T>& seq){
        this->data = new LinkedList<T>();
        for(int i =0;i<seq.GetLength();i++){
            appendWithoutInstance(seq.Get(i));
        }
    }

    MutableListSequence<T>* Slice(int index, int offset , const Sequence<T> &seq ) override {
        MutableListSequence<T>* result = new MutableListSequence<T>(*this);
        if( MyAbs(index)>result->GetLength()) throw std::invalid_argument("");
        int start =0 ;
        if(index<0) { start =result->GetLength() + index;  } else { start = index; }
        int i =start;
        for( ; i< std::min(result->GetLength() ,  start+seq.GetLength() );i++) {
            result->Set(seq.Get(i-start),i);
        }   
        int removeCount =0;
        
        for( ;(i< std::min(result->GetLength() , start+offset ) ) && ( removeCount<offset-seq.GetLength() );removeCount++){
            result->RemoveAt(i);
        }
        return result;
    }

    Sequence<  Sequence<T>* >* Split( bool (*func)(T input) ) const  {
        MutableListSequence< Sequence<T>* >* result = new MutableListSequence< Sequence<T>* >();
        MutableListSequence<T>* buf = new MutableListSequence<T>();
        for(int i = 0 ; i<this->GetLength();i++){
            buf->Append(this->Get(i));
            if( (*func)(this->Get(i)) == true){
                result->Append(buf);
                buf = new MutableListSequence<T>();
            } 
        }
        result->Append(buf);
        return result;
    }

    //Sequence<  Sequence<T>* >* Split( bool (*func)(T input) ) override {}
    MutableListSequence<T>* Concat(const Sequence <T>& array) const override{
        MutableListSequence<T>* result = new MutableListSequence<T>(static_cast<const Sequence<T>&>(*this));
        for(int i=0;i<array.GetLength();i++){  result->Append(array.Get(i));  }
        return result;
    } 
    MutableListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex<0||endIndex<startIndex) throw std::invalid_argument("");
        if(endIndex>=this->GetLength()) throw std::out_of_range("");
        MutableListSequence<T>* result = new MutableListSequence<T>(this->data->GetSubList(startIndex,endIndex));
        return result;
    }
};


template<typename T>
class ImmutableListSequence : public ListSequence<T>{
private:
    ListSequence<T>* Instance() override {
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*this);
        return result;
    }
    const ListSequence<T>* Instance() const override  {
        const ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*this);
        return result;
    }
    ImmutableListSequence<T>* appendWithoutInstance(const T& item) {
        ImmutableListSequence<T>* result=this;
        result->data->Append(item);
        return result;
    }
public:
    using ListSequence<T>::ListSequence;

     ImmutableListSequence (const ImmutableListSequence <T>& seq){
        this->data = new LinkedList<T>();
        for(int i =0;i<seq.GetLength();i++){
            appendWithoutInstance(seq.Get(i));
        }
    }
    ImmutableListSequence<T>* Slice(int index, int offset , const Sequence<T> &seq ) override {
        MutableListSequence<T>* result = new MutableListSequence<T>(*this);
        if( MyAbs(index)>result->GetLength()) throw std::invalid_argument("");
        int start =0 ;
        if(index<0) { start =result->GetLength() + index;  } else { start = index; }
        int i =start;
        for( ; i< std::min(result->GetLength() ,  start+seq.GetLength() );i++) {
            result->Set(seq.Get(i-start),i);
        }   
        int removeCount =0;
        
        for( ;(i< std::min(result->GetLength() , start+offset ) ) && ( removeCount<offset-seq.GetLength() );removeCount++){
            result->RemoveAt(i);
        }
        ImmutableListSequence<T>* res = new ImmutableListSequence<T>(*result);
        delete result;
        return res;
    }
    Sequence<  Sequence<T>* >* Split( bool (*func)(T input) ) const  {
        MutableListSequence< Sequence<T>* >* result = new MutableListSequence< Sequence<T>* >();
        MutableListSequence<T>* buf = new MutableListSequence<T>();
        for(int i = 0 ; i<this->GetLength();i++){
            buf->Append(this->Get(i));
            if( (*func)(this->Get(i)) == true){
                result->Append(buf);
                buf = new MutableListSequence<T>();
            }
        }
        result->Append(buf);
        ImmutableListSequence< Sequence<T>* >* finalresult = new ImmutableListSequence< Sequence<T>* >(*result);
        delete result;
        return finalresult;
    }

    ImmutableListSequence<T>* Concat(const Sequence <T>& seq) const override{
        MutableListSequence<T>* buf = new MutableListSequence<T>(static_cast<const Sequence<T>&>(*this));
        for(int i=0;i<seq.GetLength();i++){   buf->Append(seq.Get(i));   }
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*buf);
        delete buf;
        return result;
    } 
    ImmutableListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex<0||endIndex<startIndex) throw std::invalid_argument("");
        if(endIndex>=this->data->GetLength()) throw std::out_of_range("");
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(this->data->GetSubList(startIndex,endIndex));
        return result;
    }
};