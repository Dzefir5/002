#pragma once
#include <stdexcept>
#include <iostream>
#include "LinkedList.h"
#include "Sequence.h"

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

    void PrintSequence() const {
        std::cout<<std::endl;
        for(int i =0;i<this->GetLength();i++){
            std::cout<<this->Get(i)<<"_";
        }
        std::cout<<std::endl;
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
public:
    using ListSequence<T>::ListSequence;
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
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(static_cast<const Sequence<T>&>(*this));
        return result;
    }
    const ListSequence<T>* Instance() const override  {
        const ImmutableListSequence<T>* result = new ImmutableListSequence<T>(static_cast<const Sequence<T>&>(*this));
        return result;
    }
public:
    using ListSequence<T>::ListSequence;
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