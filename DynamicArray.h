#pragma once
#include "MySwap.h"


//Избавиться от memcpy
template <typename T>
class DynamicArray{
//capacity
private:
    int size=0;
    T* elements=nullptr;
    void swap(DynamicArray<T>& toSwap){
        MySwap(size,toSwap.size);
        MySwap(elements,toSwap.elements);
    }
public:
    //Constructors
    DynamicArray():size(0),elements(nullptr){} ;
    DynamicArray(int size):size(size),elements(nullptr){
        if(size<0) throw std::invalid_argument("invalid argument in constructor");
        if(size>0) elements=new T[size];
    }
    DynamicArray( T* items, int count):DynamicArray<T>(count){
        if(items==nullptr) throw std::invalid_argument("invalid argument in constructor");
        for(int i=0;i<count;i++){
            elements[i]=items[i];
        }
    }
    DynamicArray( const T& fillElem, int count):DynamicArray<T>(count){
        for(int i=0;i<size;i++){
            elements[i]=fillElem;
        }
    }
    DynamicArray(const DynamicArray<T>& array):DynamicArray<T>(array.elements,array.size){}

    //Functions
    T Get(int index) const {
        if(size<=index||index<0)throw std::out_of_range("Invalid index");
        return elements[index];
    }

    int GetLength() const { return this->size; }

    void Set(const T& value,int index) {
        if(size<=index||index<0)throw std::out_of_range("Invalid index");
        elements[index]=value;
    }
    void Resize(int newSize,int offset){ 
        if(newSize<0||offset<0||offset+size>newSize)throw std::invalid_argument("Invalid argument in Resize fucntion");
        if(newSize==0){
            delete[] elements;
            elements=nullptr;
            return;
        }
        T* buf = new T[newSize];
        if(elements!=nullptr){
            for(int i=0;i<std::min(size,newSize);i++){
                buf[i+offset]=elements[i];
            }
            delete[] elements;
        }
        elements=buf;
        size=newSize;
    }

    void Resize(int newSize){ 
        if(newSize<0||size>newSize)throw std::invalid_argument("Invalid argument in Resize fucntion");
        if(newSize==0){
            delete[] elements;
            elements=nullptr;
            return;
        }
        T* buf = new T[newSize];
        if(elements!=nullptr){
            for(int i=0;i<std::min(size,newSize);i++){
                buf[i]=elements[i];
            }
            delete[] elements;
        }
        elements=buf;
        size=newSize;
    }

    void InsertAt(const T& item, int index) {
        if(index<0||index>size) throw std::invalid_argument("");
        size++;
        T* buf = new T[size];
        if(elements!=nullptr){
            for(int i=0;i<index;i++){
                buf[i]=elements[i];
            }
            for(int i=index;i<size-1;i++){
                buf[i+1]=elements[i];
            }
        }
        buf[index]=item;
        delete[] elements;
        elements=buf;
    }
    void RemoveAt(int index) {
        if(index<0||index>=size) throw std::invalid_argument("Remove operation in empty array");
        if(size==1){
            delete[] elements;
            elements=nullptr;
            size--;
            return;
        } 
        size--;
        T* buf = new T[size];
        for(int i=0;i<index;i++){
            buf[i]=elements[i];
        }
        for(int i=index;i<size;i++){
            buf[i]=elements[i+1];
        }
        delete[] elements;
        elements=buf;
        return;
    }
    
    T& operator[](int index){
        if(size<=index)throw std::out_of_range("Invalid index");
        if(size<=0) throw std::out_of_range("Getter call in empty collection");
        return elements[index];
    }
    const T& operator[](int index) const{
        if(size<=index)throw std::out_of_range("Invalid index");
        if(size<=0) throw std::out_of_range("Getter call in empty collection");
        return elements[index];
    }
    //тестировать
    DynamicArray<T>* Concat (const DynamicArray<T>& array){
        DynamicArray<T>* buf = new DynamicArray<T>(array.GetLength()+size);
        if(buf->size==0) return buf;
        for(int i=0;i<this->size;i++){
            (*buf)[i]=this->elements[i];
        }
        for(int i=0;i<array.GetLength();i++){
            (*buf)[size+i]=array.elements[i];
        }
        return buf;
    }
    
    bool operator==(const DynamicArray<T>& array){
        if(array.size!=size) return false;
        for(int i =0 ; i<array.size;i++){
            if(array[i]!=(*this)[i]) return false;
        }
        return true;
    }
    DynamicArray<T>& operator=( DynamicArray<T> array){ ///COPY AND SWAP IDIOM
       swap(array);
       return *this;
    }
    DynamicArray<T>& operator+=(const DynamicArray<T>& array){
        T* buf = new T[size+array.size];
        for(int i=0;i<size;i++){
            buf[i]=elements[i];
        }
        for(int i=0;i<array->size;i++){
            buf[size+i]=array.elements[size+i];
        }
        delete[] elements;
        elements=buf;
        return *this;
    }
    DynamicArray<T> operator+(const DynamicArray<T>& array){ /// += FIRST
        DynamicArray<T> result = (*this);
        result+=array;
        return result;
    }
    
    //Destructor
    virtual ~DynamicArray(){
        delete[] elements;
    }
};