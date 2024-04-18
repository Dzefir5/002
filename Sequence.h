#pragma once



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
    virtual Sequence<T>* Concat( const Sequence<T> &seq ) const = 0; 
    virtual Sequence<T>* Slice(int index, int offset , const Sequence<T> &seq )  = 0; 

    virtual T& operator[](int index) = 0 ;

    void PrintSequence() const {
        std::cout<<std::endl;
        for(int i =0;i<this->GetLength();i++){
            std::cout<<this->Get(i)<<" ";
        }
        std::cout<<std::endl;
    }

    bool operator==(const Sequence<T> &seq){
        if(seq.GetLength()!=this->GetLength()){ 
            return false; 
        }
        for(int i = 0;i<seq.GetLength();i++){
            if(this->Get(i)!=seq.Get(i)){
                return false;
            }
        }
        return true;
    }
};

