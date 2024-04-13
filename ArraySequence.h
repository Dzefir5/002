#pragma once
#include <stdexcept>
#include <iostream>
#include "DynamicArray.h"
#include "Sequence.h"

template <typename T>
class ArraySequence : public Sequence<T>{
protected:
    DynamicArray<T>* data;
    virtual ArraySequence<T>* Instance()=0 ;
    virtual const ArraySequence<T>* Instance() const =0;

    ArraySequence<T>* AppendWithoutInstance(const T& item) {
        ArraySequence<T>* result=this;
        result->data->Resize(data->GetSize()+1,0);
        (*(result->data))[data->GetSize()-1] = item;
        return result;
    }
public:
    ArraySequence (){ 
        this->data = new DynamicArray<T>();
    }
    ArraySequence (int count){
        this->data = new DynamicArray<T>(count);
    }
    ArraySequence (T* items, int count){
        this->data = new DynamicArray<T>(items,count);
    }
    ArraySequence (const T& fillElem, int count){
        this->data = new DynamicArray<T>(fillElem,count);
    }
    ArraySequence (const Sequence<T>& seq ){
        this->data = new DynamicArray<T>();
        for(int i =0;i<seq.GetLength();i++){
            AppendWithoutInstance(seq.Get(i));
        }
    }
    T GetFirst() const override{
        return (this->data)->Get(0);  
    }
    T GetLast() const override{
        return (this->data)->Get(data->GetSize()-1);
    }
    T Get(int index) const override{
        return (this->data)->Get(index);
    }
    ArraySequence<T>* Set(const T& value,int index) override{
        ArraySequence<T>* result=Instance();
        result->data->Set(value,index);
        return result;
    }
    int GetLength() const override{
        return this->data->GetSize();
    }

    ArraySequence<T>* Append(const T& item) override{
        ArraySequence<T>* result=Instance();
        result->data->Resize(data->GetSize()+1,0);
        (*(result->data))[data->GetSize()-1] = item;
        return result;
    }
    ArraySequence<T>* Prepend(const T& item)  override{
        ArraySequence<T>* result=Instance();
        result->data->Resize(data->GetSize()+1,1);
        (*(result->data))[0] = item;
        return result;
    }
    ArraySequence<T>* InsertAt(const T& item, int index) override{
        ArraySequence<T>* result=Instance();
        result->data->InsertAt(item,index);
        return result;
    }
    ArraySequence<T>* RemoveAt(int index) override{
        ArraySequence<T>* result=Instance();
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

    T& operator[](int index) override {
        return (*(Instance()->data))[index];
    }

    virtual ~ArraySequence() {
		delete data;
	}
};  

template<typename T>
class MutableArraySequence : public ArraySequence<T>{
private:
    ArraySequence<T>* Instance() override {
        return static_cast<ArraySequence<T>*>(this);
    }
    const ArraySequence<T>* Instance() const override  {
        return static_cast<const ArraySequence<T>*>(this);
    }
public:
    using ArraySequence<T>::ArraySequence;
    /*MutableArraySequence (const Sequence <T>& seq){ // спросить про наследование конструкторов
        this->data = new DynamicArray<T>();
        std::cout<<"----==="<<std::endl;
        for(int i =0;i<seq.GetLength();i++){
            this->Append( seq.Get(i) );
        }
    }*/
    MutableArraySequence<T>* Concat( const Sequence <T>& array) const override{
        MutableArraySequence<T>* result = new MutableArraySequence<T>(static_cast<const Sequence<T>&>(*this));
        if(result->data==this->data) std::cout<<"error";
        for(int i=0;i<array.GetLength();i++){   result->Append(array.Get(i));   }
        return result;
    } 
    MutableArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex<0||endIndex<startIndex) throw std::invalid_argument("");
        if(endIndex>=this->data->GetSize()) throw std::out_of_range("");
        MutableArraySequence<T>* result = new MutableArraySequence<T>(&(*(this->data))[startIndex],endIndex-startIndex+1);
        return result;
    }
};

template<typename T>
class ImmutableArraySequence : public ArraySequence<T>{
private:
    ArraySequence<T>* Instance() override {
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(static_cast<const Sequence<T>&>(*this));
        return result;
    }
    const ArraySequence<T>* Instance() const override  {
        const ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(static_cast<const Sequence<T>&>(*this));
        return result;
    }
public:
    using ArraySequence<T>::ArraySequence;
    /*ImmutableArraySequence (const Sequence <T>& seq){ // спросить про наследование конструкторов
        std::cout<<"----))))"<<std::endl;
        this->data = new DynamicArray<T>();
        for(int i =0;i<seq.GetLength();i++){
            this->Append( seq.Get(i) );
        }
    }*/
    ImmutableArraySequence<T>* Concat( const Sequence <T>& array) const override{
        MutableArraySequence<T>* buf = new MutableArraySequence<T>(static_cast<const Sequence<T>&>(*this));
        for(int i=0;i<array.GetLength();i++){   buf->Append(array.Get(i));   }
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*buf);
        delete buf;
        return result;
    } 
    ImmutableArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex<0||endIndex<startIndex) throw std::invalid_argument("");
        if(endIndex>=this-GetLength()) throw std::out_of_range("");
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(&(*(this->data))[startIndex],endIndex-startIndex+1);
        return result;
    }
};

