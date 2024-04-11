#pragma once
#include <stdexcept>
#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"


template <typename T> 
class Sequence{
public:
    virtual T GetFirst() const =0;
    virtual T GetLast() const=0;
    virtual T Get( int index ) const =0;
    virtual void Set( const T& value,int index )=0;
    virtual Sequence<T>* GetSubsequence( int startIndex, int endIndex )const  =0;
    virtual int GetLength() const =0;
    virtual void Append( const T& item )=0;
    virtual void Prepend( const T& item )=0;
    virtual void InsertAt( const T& item, int index )=0;
    virtual void RemoveAt( int index )=0;
    virtual Sequence <T>* Concat( Sequence<T> &seq ) const = 0; 

    virtual T& operator[](int index) = 0 ;
};

template <typename T>
class ArraySequence : public Sequence<T>{
protected:
    DynamicArray<T>* data;
    virtual ArraySequence<T>* Instance()=0 ;
    virtual const ArraySequence<T>* Instance() const =0;
public:
    ArraySequence (){
        data = new DynamicArray<T>();
    }
    ArraySequence (int count){
        data = new DynamicArray<T>(count);
    }
    ArraySequence(DynamicArray<T>* array) {
		data = array;
	}
    ArraySequence (T* items, int count){
        data = new DynamicArray<T>(items,count);
    }
    ArraySequence (const T& fillElem, int count){
        data = new DynamicArray<T>(fillElem,count);
    }
    ArraySequence (const ArraySequence<T>& arrseq ){
        data = new DynamicArray<T>(*(arrseq.data));
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
    void Set(const T& value,int index) override{
        Instance()->data->Set(value,index);
    }
    int GetLength() const override{
        return this->data->GetSize();
    }
    /*ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex<0||endIndex<startIndex) throw std::invalid_argument("");
        if(endIndex>=data->GetSize()) throw std::out_of_range("");
        ArraySequence<T>* result = new ArraySequence<T>(&(*data)[startIndex],endIndex-startIndex+1);
        return result;
    }*/

    void Append(const T& item) override{
        Instance()->data->Resize(data->GetSize()+1,0);
       (*(Instance()->data))[data->GetSize()-1] = item;
    }
    void Prepend(const T& item)  override{
        data->Resize(data->GetSize()+1,1);
        (*(Instance()->data))[0] = item;
    }
    void InsertAt(const T& item, int index) override{
        Instance()->data->InsertAt(item,index);
    }
    void RemoveAt(int index) override{
        Instance()->data->RemoveAt(index);
    }

    /*ArraySequence<T>* Concat( Sequence <T>& array) const override{
        //DynamicArray<T>* buf = data->Concat(array->data);
        ArraySequence<T>* result = new ArraySequence<T>(nullptr);
        result->data=data->Concat(static_cast<ArraySequence<T>&>(array).data);
        return result;
    } */

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
    /*MutableArraySequence<T>* Concat( Sequence <T>& array) const {
        return static_cast<MutableArraySequence<T>*>(Instance()->Concat(array));
    } */
    MutableArraySequence<T>* Concat( Sequence <T>& array) const override{
        MutableArraySequence<T>* result = new MutableArraySequence<T>(nullptr);
        result->data=this->data->Concat(static_cast<MutableArraySequence<T>&>(array).data);
        return result;
    } 
    MutableArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex<0||endIndex<startIndex) throw std::invalid_argument("");
        if(endIndex>=this->data->GetSize()) throw std::out_of_range("");
        MutableArraySequence<T>* result = new MutableArraySequence<T>(&(*(this->data))[startIndex],endIndex-startIndex+1);
        return result;
    }
    /*MutableArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const {
        return static_cast<MutableArraySequence<T>*>(Instance()->GetSubsequence(startIndex,endIndex));
    }*/

};


template<typename T>
class ImmutableArraySequence : public ArraySequence<T>{
private:
    ArraySequence<T>* Instance() override {
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*this);
        return result;
    }
    const ArraySequence<T>* Instance() const override  {
        const ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*this);
        return result;
    }
public:
    using ArraySequence<T>::ArraySequence;
    ImmutableArraySequence<T>* Concat( Sequence <T>& array) const override{
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(nullptr);
        result->data=this->data->Concat(static_cast<ImmutableArraySequence<T>&>(array).data);
        return result;
    } 
    ImmutableArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex<0||endIndex<startIndex) throw std::invalid_argument("");
        if(endIndex>=this->data->GetSize()) throw std::out_of_range("");
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(&(*(this->data))[startIndex],endIndex-startIndex+1);
        return result;
    }
};




template <typename T> 
class ListSequence : public Sequence<T>{
protected:
    LinkedList<T>* data;

public:
    ListSequence (){
        data=new LinkedList<T>();
    }
    ListSequence (T* items, int count){
        data=new LinkedList<T>(items,count);
    }
    ListSequence (const LinkedList<T>& list){
        data=new LinkedList<T>(list);
    }
    ListSequence (LinkedList<T>* list){
        data=new LinkedList<T>(*list);
    }
    ListSequence (const ListSequence<T>& listseq){
        data=new LinkedList<T>(*(listseq.data));
    }

    T GetFirst() const override{
        return data->GetFirst();
    }
    T GetLast() const override{
        return data->GetLast();
    }
    T Get(int index) const override{
        return data->Get(index);
    }

    void Set(const T& value,int index) override{
        data->Set(value,index);
    }

    ListSequence<T>* GetSubsequence(int startIndex, int endIndex) override{
        ListSequence<T>* result = new ListSequence<T>(data->GetSubList(startIndex,endIndex));
        return result;
    }
    int GetLength() const override{
        return data->GetLength();
    }
    void Append(const T& item) override{
        data->Append(item);
    }
    void Prepend(const T& item) override{
        data->Prepend(item);
    }
    void InsertAt(const T& item, int index) override{
        data->InsertAt(item,index);
    }
    void RemoveAt(int index) override{
        data->RemoveAt(index);
    }

    ListSequence<T>* Concat(Sequence <T>& list) const override{
        //DynamicArray<T>* buf = data->Concat(array->data);
        ListSequence<T>* result = new ListSequence<T>(nullptr);
        result->data=data->Concat(static_cast<ListSequence<T>&>(list).data);
        return result;
    } 

    void PrintSequence(){
        std::cout<<endl;
        for(int i =0;i<data->GetSize();i++){
            std::cout<<data[i]<<"_";
        }
        std::cout<<endl;
    }

    T& operator[](int index) override{
        return (*data)[index];
    }

    virtual ~ListSequence<T>(){
        delete data;
    }
};