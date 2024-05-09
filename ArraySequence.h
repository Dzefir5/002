#pragma once
#include <stdexcept>
#include <iostream>
#include "DynamicArray.h"
#include "Sequence.h"
#include "MyAbs.h"
#include "MySwap.h"

template <typename T>
class ArraySequence : public Sequence<T>{
protected:
    DynamicArray<T>* data;
    virtual ArraySequence<T>* Instance()=0 ;
    virtual const ArraySequence<T>* Instance() const =0;
    void swap(ArraySequence& toSwap){
        MySwap(data,toSwap.data);
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
        this->data = new DynamicArray<T>(seq.GetLength());
        for(int i =0;i<seq.GetLength();i++){
            this->data->Set(seq.Get(i),i);
        }
    }
    ArraySequence (const ArraySequence<T>& seq ){
        this->data = new DynamicArray<T>(seq.GetLength());
        for(int i =0;i<seq.GetLength();i++){
            this->data->Set(seq.Get(i),i);
        }
    }
    T GetFirst() const override{
        return (this->data)->Get(0);  
    }
    T GetLast() const override{
        return (this->data)->Get(data->GetLength()-1);
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
        return this->data->GetLength();
    }

    ArraySequence<T>* Append(const T& item) override{
        ArraySequence<T>* result=Instance();
        result->data->Resize(data->GetLength()+1,0);
        result->data->Set(item,data->GetLength()-1);
        return result;
    }
    ArraySequence<T>* Prepend(const T& item)  override{
        ArraySequence<T>* result=Instance();
        result->data->Resize(data->GetLength()+1,1);
        result->data->Set(item,0);
        return result;
    }
    ArraySequence<T>* InsertAt(const T& item, int index) override{
        ArraySequence<T>* result=Instance();
        if(index<0||index>result->GetLength()) 
            throw std::invalid_argument("");
        DynamicArray<T>* buf = new DynamicArray<T>(result->GetLength()+1);

        for(int i=0;i<index;i++){
           buf->Set(result->data->Get(i),i);
        }
        buf->Set(item,index);
        for(int i=index;i<result->GetLength()-1;i++){
            buf->Set(result->data->Get(i),i+1);
        }
        delete result->data;
        result->data = buf;
        return result;
    }
    ArraySequence<T>* RemoveAt(int index) override{
        ArraySequence<T>* result=Instance();
        if(index<0||index>result->GetLength()) 
            throw std::invalid_argument("");
        DynamicArray<T>* buf = new DynamicArray<T>(result->GetLength()-1);

        for(int i=0;i<index;i++){
           buf->Set(result->data->Get(i),i);
        }
        for(int i=index;i<result->GetLength()-1;i++){
            buf->Set(result->data->Get(i+1),i);
        }
        delete result->data;
        result->data = buf;
        return result;
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
    
    MutableArraySequence<T>* Slice(int index, int offset , const Sequence<T> &seq ) override {
        MutableArraySequence<T>* result = new MutableArraySequence<T>(*this);
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
        MutableArraySequence< Sequence<T>* >* result = new MutableArraySequence< Sequence<T>* >();
        MutableArraySequence<T>* buf = new MutableArraySequence<T>();
        for(int i = 0 ; i<this->GetLength();i++){
            buf->Append(this->Get(i));
            if( (*func)(this->Get(i)) == true){
                result->Append(buf);
                buf = new MutableArraySequence<T>();
            } 
        }
        result->Append(buf);
        return result;
    }

    MutableArraySequence<T>* Concat( const Sequence <T>& array) const override{
        MutableArraySequence<T>* result = new MutableArraySequence<T>(this->GetLength() + array.GetLength());
        for(int i=0;i<this->GetLength();i++){
            result->Set(this->Get(i),i);
        }
        for(int i=0;i<array.GetLength();i++){
            result->Set(array.Get(i),i+this->GetLength());
        }
        return result;
    } 
    MutableArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex<0||endIndex<startIndex) throw std::invalid_argument("");
        if(endIndex>=this->data->GetLength()) throw std::out_of_range("");
        MutableArraySequence<T>* result = new MutableArraySequence<T>(&(*(this->data))[startIndex],endIndex-startIndex+1);
        return result;
    }

    MutableArraySequence<T>& operator=(const Sequence<T> &seq){
        MutableArraySequence<T> result (seq);
        swap(*this,result);
        return *this
    }
    
};

template<typename T>
class ImmutableArraySequence : public ArraySequence<T>{
private:
    ArraySequence<T>* Instance() override {
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*this);
        return result;
    }
    const ArraySequence<T>* Instance() const override  {
        const ImmutableArraySequence<T>* result = new const ImmutableArraySequence<T>(*this);
        return result;
    }

public:
    using ArraySequence<T>::ArraySequence;

    ImmutableArraySequence<T>* Slice(int index, int offset , const Sequence<T> &seq ) override {
        MutableArraySequence<T>* result = new MutableArraySequence<T>(*this);
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
        ImmutableArraySequence<T>* res = new ImmutableArraySequence<T>(*result);
        delete result;
        return res;
    }

    Sequence<  Sequence<T>* >* Split( bool (*func)(T input) ) const  {
        MutableArraySequence< Sequence<T>* >* result = new MutableArraySequence< Sequence<T>* >();
        MutableArraySequence<T>* buf = new MutableArraySequence<T>();
        for(int i = 0 ; i<this->GetLength();i++){
            buf->Append(this->Get(i));
            if( (*func)(this->Get(i)) == true){
                result->Append(buf);
                buf = new MutableArraySequence<T>();
            } 
        }
        result->Append(buf);
        ImmutableArraySequence< Sequence<T>* >* finalresult = new ImmutableArraySequence< Sequence<T>* >(*result);
        delete result;
        return finalresult;
    }

    ImmutableArraySequence<T>* Concat( const Sequence <T>& array) const override{
        MutableArraySequence<T>* buf = new MutableArraySequence<T>(this->GetLength() + array.GetLength());
        for(int i=0;i<this->GetLength();i++){
            buf->Set(this->Get(i),i);
        }
        for(int i=0;i<array.GetLength();i++){
            buf->Set(array.Get(i),i+this->GetLength());
        }
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*buf);
        delete buf;
        return result;
    } 
    ImmutableArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex<0||endIndex<startIndex) throw std::invalid_argument("");
        if(endIndex>=this->GetLength()) throw std::out_of_range("");
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(&(*(this->data))[startIndex],endIndex-startIndex+1);
        return result;
    }

    ImmutableArraySequence<T>& operator=(const Sequence<T> &seq){
        ImmutableArraySequence<T> result (seq);
        swap(*this,result);
        return *this
    }
};

