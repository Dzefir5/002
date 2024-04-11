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
    virtual Sequence<T>* Set( const T& value,int index )=0;
    virtual Sequence<T>* GetSubsequence( int startIndex, int endIndex )const  =0;
    virtual int GetLength() const =0;
    virtual Sequence<T>*  Append( const T& item )=0;
    virtual Sequence<T>*  Prepend( const T& item )=0;
    virtual Sequence<T>*  InsertAt( const T& item, int index )=0;
    virtual Sequence<T>*  RemoveAt( int index )=0;
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
        return (Instance()->data)->Get(0);  
    }
    T GetLast() const override{
        return (Instance()->data)->Get(data->GetSize()-1);
    }
    T Get(int index) const override{
        return (Instance()->data)->Get(index);
    }
    ArraySequence<T>* Set(const T& value,int index) override{
        ArraySequence<T>* result=Instance();
        result->data->Set(value,index);
        return result;
    }
    int GetLength() const override{
        return Instance()->data->GetSize();
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
    MutableArraySequence<T>* Concat( Sequence <T>& array) const override{
        MutableArraySequence<T>* result = new MutableArraySequence<T>(nullptr);
        for(int i=0;i<array.GetLength();i++){
            result->Append(array[i]);
        }
        //result->data=this->data->Concat(static_cast<MutableArraySequence<T>&>(array).data);
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
        for(int i=0;i<array.GetLength();i++){
            result->Append(array[i]);
        }
        //result->data=this->data->Concat(static_cast<ImmutableArraySequence<T>&>(array).data);
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
    virtual  ListSequence<T>* Instance()=0 ;
    virtual const  ListSequence<T>* Instance() const =0;
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
        return Instance()->data->GetFirst();
    }
    T GetLast() const override{
        return Instance()->data->GetLast();
    }
    T Get(int index) const override{
        return Instance()->data->Get(index);
    }

    LinkedList<T>* Set(const T& value,int index) override{
        LinkedList<T>* result = Instance();
        result->data->Set(value,index);
        return result;
    }

    int GetLength() const override{
        return Instance()->data->GetLength();
    }
    LinkedList<T>* Append(const T& item) override{
        LinkedList<T>* result = Instance();
        result->data->Append(item);
        return result;
    }
    LinkedList<T>* Prepend(const T& item) override{
        LinkedList<T>* result = Instance();
        result->data->Prepend(item);
        return result;
    }
    LinkedList<T>* InsertAt(const T& item, int index) override{
        LinkedList<T>* result = Instance();
        result->data->InsertAt(item,index);
        return result;
    }
    LinkedList<T>* RemoveAt(int index) override{
        LinkedList<T>* result = Instance();
        result->data->RemoveAt(index);
        return result;
    }

    void PrintSequence(){
        std::cout<<std::endl;
        for(int i =0;i<data->GetSize();i++){
            std::cout<<data[i]<<"_";
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
    const ArraySequence<T>* Instance() const override  {
        return static_cast<const ListSequence<T>*>(this);
    }
public:
    using ListSequence<T>::ListSequence;
    MutableListSequence<T>* Concat( Sequence <T>& array) const override{
        MutableListSequence<T>* result = new MutableListSequence<T>();
        for(int i=0;i<array.GetLength();i++){
            static_cast<MutableArraySequence<T>*>(result)->Append(array[i]);
        }
        
        //result->data=this->data->Concat(static_cast<MutableListSequence<T>&>(array).data);
        return result;
    } 
    MutableListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex<0||endIndex<startIndex) throw std::invalid_argument("");
        if(endIndex>=this->data->GetSize()) throw std::out_of_range("");
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
public:
    using ListSequence<T>::ListSequence;
    ImmutableListSequence<T>* Concat( Sequence <T>& array) const override{
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>();
        for(int i=0;i<array.GetLength();i++){
            static_cast<MutableListSequence<T>*>(result)->Append(array[i]);
        }
        //result->data=this->data->Concat(static_cast<ImmutableListSequence<T>&>(array).data);
        return result;
    } 
    ImmutableListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override{
        if(startIndex<0||endIndex<startIndex) throw std::invalid_argument("");
        if(endIndex>=this->data->GetSize()) throw std::out_of_range("");
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(this->data->GetSubList(startIndex,endIndex));
        return result;
    }
};