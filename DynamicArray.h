#pragma once
#include "MySwap.h"



template <typename T>
class DynamicArray{

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
        if(size<0) 
            throw std::invalid_argument("invalid argument in constructor");
        if(size>0) 
            elements=new T[size];
    }
    DynamicArray( T* items, int count):DynamicArray<T>(count){
        if(items==nullptr) 
            throw std::invalid_argument("invalid argument in constructor");
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
        if(size<=index||index<0)
            throw std::out_of_range("Invalid index");
        return elements[index];
    }

    int GetLength() const { return this->size; }

    void Set(const T& value,int index) {
        if(size<=index||index<0) 
            throw std::out_of_range("Invalid index");//!!!!!! перенос
        elements[index]=value;
    }
    void Resize(int newSize,int offset){ 
        if(newSize<0||offset<0||offset+size>newSize)
            throw std::invalid_argument("Invalid argument in Resize fucntion");
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
        if(newSize<0||size>newSize)
            throw std::invalid_argument("Invalid argument in Resize fucntion");
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

    T& operator[](int index){
        if(size<=index)
            throw std::out_of_range("Invalid index");
        if(size<=0) 
            throw std::out_of_range("Getter call in empty collection");
        return elements[index];
    }
    const T& operator[](int index) const{
        if(size<=index)
            throw std::out_of_range("Invalid index");
        if(size<=0) 
            throw std::out_of_range("Getter call in empty collection");
        return elements[index];
    }
    bool operator==(const DynamicArray<T>& array){
        if(array.size!=size) 
            return false;
        for(int i =0 ; i<array.size;i++){
            if(array[i]!=(*this)[i]) return false;
        }
        return true;
    }
    DynamicArray<T>& operator=( DynamicArray<T> array){ ///COPY AND SWAP IDIOM
       swap(array);
       return *this;
    }
    
    //Destructor
    virtual ~DynamicArray(){
        delete[] elements;
    }
};