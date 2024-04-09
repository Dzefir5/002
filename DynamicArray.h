#pragma once
#include <cstring>
#include <algorithm> 


template <typename T>
class DynamicArray{
    
private:
    int size=0;
    T* elements=nullptr;
    void swap(DynamicArray<T>& toSwap){
        std::swap(size,toSwap.size);
        std::swap(elements,toSwap.elements);
    }
public:
    //Constructors
    DynamicArray():size(0),elements(nullptr){};
    DynamicArray(int size):size(size),elements(nullptr){
        if(size<0) throw std::invalid_argument("invalid input in constructor");
        if(size>0) elements=new T[size];
    }
    DynamicArray( T* items, int count):DynamicArray<T>(count){
        if(items==nullptr) throw std::invalid_argument("invalid input in constructor");
        for(int i=0;i<count;i++){
            elements[i]=items[i];
        }
    }
    DynamicArray( const T& fillElem, int count):DynamicArray<T>(count){
        //memset(&elements,fillElem,sizeof(T)*count);  возможно заменить на std:fill
        std::fill(elements,elements+size,fillElem);
    }
    DynamicArray(const DynamicArray<T>& array):DynamicArray<T>(array.elements,array.size){}

    //Functions
    T Get(int index) const {
        if(size<=index||index<0)throw std::out_of_range("Invalid index");
        return elements[index];
    }

    int GetSize() const { return this->size; }

    void Set(const T& value,int index) {
        if(size<=index||index<0)throw std::out_of_range("Invalid index");
        elements[index]=value;
    }
    void Resize(int newSize,int offset){
        if(newSize<=0||offset<=0||offset+size>newSize)throw std::invalid_argument("Invalid input in Resize fucntion");
        T* buf = new T[newSize];
        memcpy((void*)(buf+offset),(void*)elements,sizeof(T)*std::min(size,newSize));
        delete[] elements;
        elements=buf;
        size=newSize;
    }
    void InsertAt(const T& item, int index) {
        if(index<0||index>size) throw std::invalid_argument("");
        size++;
        T* buf = new T[size];
        memcpy((void*)(buf),(void*)elements,sizeof(T)*index);
        buf[index]=item;
        memcpy((void*)(buf+index+1),(void*)(elements+index),sizeof(T)*(size-index));
        delete[] elements;
        elements=buf;
    }
    void RemoveAt(int index) {
        if(index<0||index>=size) throw std::invalid_argument("");
        T* buf = new T[size-1];
        memcpy((void*)(buf),(void*)elements,sizeof(T)*index);
        memcpy((void*)(buf+index),(void*)(elements+index+1),sizeof(T)*(size-index-1));
        delete[] elements;
        elements=buf;
        size--;
    }
    
    T& operator[](int index){
        if(size<=index)throw std::out_of_range("Invalid index");
        if(size<=0) throw std::out_of_range("Getter call in empty collection");
        return elements[index];
    }
    
    DynamicArray<T>* Concat (const DynamicArray<T>* array){
        if(array==nullptr) throw std::invalid_argument("invalid nullptr argument in concat fucntion");
        DynamicArray<T>* buf = new DynamicArray<T>(array->GetSize()+size);
        if(buf->size==0) return buf;
        memcpy((void*)buf->elements,(void*)this->elements,sizeof(T)*size);
        memcpy((void*)(buf->elements+size),(void*)array->elements,sizeof(T)*array->size);
        return buf;
    }
    
    bool operator==(const DynamicArray<T>& array){
        if(array.size!=size) return false;
        for(int i =0 ; i<array.size;i++){
            if(array[i]!=(*this)[i]) return false;
        }
        return true;
    }
    DynamicArray<T>& operator=(const DynamicArray<T> array){ ///COPY AND SWAP IDIOM
       swap(array);
       return *this;
    }
    DynamicArray<T>& operator+=(const DynamicArray<T>& array){
        T* buf = new T[size+array.size];
        memcpy((void*)buf,(void*)(this->elements),size*sizeof(T));
        memcpy((void*)(buf+size),(void*)(array.elements),array.size*sizeof(T));
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