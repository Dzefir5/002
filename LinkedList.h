#pragma once
#include "MySwap.h"
template <typename T>
class Node{
public:
    Node<T>* next=nullptr;
    T data;
    Node() = default;
    Node(T indata):next(nullptr),data(indata){};
    Node(T indata,Node<T>* ptr):data(indata),next(ptr){};
};


template <typename T>
class LinkedList{
private:
    Node<T>* head=nullptr;
    Node<T>* tail=nullptr;
    int size = 0;

    void swap(LinkedList<T>& toSwap){
        MySwap(size,toSwap.size);
        MySwap(head,toSwap.head);
        MySwap(tail,toSwap.tail);
    }
public:
    LinkedList (){};
    LinkedList ( int count){
        if(count<0) 
            throw std::invalid_argument("invalid argument in constuctor");
        this->size=count;
        for(int i=0;i<count-1;i++){
            if(i==0){
                Node<T>* buf = new Node<T>();
                head = buf;
                tail = buf;
                continue;
            }
            Node<T>* buf = new Node<T>();
            tail->next = buf;
            tail = buf;
        }
    }
    LinkedList (T* items, int count){
        if(count<0) 
            throw std::invalid_argument("invalid argument in constuctor");
        for(int i=0;i<count;i++){
            Append(items[i]);
        }
    }
    LinkedList (const T& elemFill, int count){
        if(count<0) 
            throw std::invalid_argument("invalid argument in constuctor");
        for(int i=0;i<count;i++){
            Append(elemFill);
        }
    }
    LinkedList (const LinkedList<T>& list ):LinkedList(){
        Node<T>* currentToCopy =list.head;
        while(currentToCopy!=nullptr){
            Append(currentToCopy->data);
            currentToCopy=currentToCopy->next;
        }
        this->size=list.size;
    }

    T GetFirst() const {
        if(head==nullptr)
            throw std::out_of_range("Getter call in empty collection");
        return head->data;
    }
    T GetLast() const{
        if(tail==nullptr)
            throw std::out_of_range("Getter call in empty collection");
        return tail->data;
    }
    T Get(int index) const {
        if(index<0||index>=size) 
            throw std::out_of_range("Getter call with wrong index ");
        Node<T>* current = head;
        for(int i=0;i<index;i++){
            current=current->next;
        }
        return current->data;
    }
    void Set(const T& value ,int index)  {
        if(index<0||index>=size) 
            throw std::out_of_range("Setter call with wrong index ");
        Node<T>* current = head;
        for(int i=0;i<index;i++){
            current=current->next;
        }
        current->data=value;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex){
        if(endIndex>=size)  
            throw std::out_of_range("Invalid index in SubList function");
        if(startIndex<0||endIndex<0||endIndex<startIndex) 
            throw std::invalid_argument("Invalid input in SubList function");
        LinkedList<T>* buf = new LinkedList();
        Node<T>* current = head;
        int i = 0 ;
        for( ;i<startIndex;i++){
            current=current->next;
        }
        for(;i<endIndex+1;i++){
            buf->Append(current->data);
            current=current->next;
        }
        return buf;
    }

    int GetLength() const{ return size; }

    void Append(const T& item){     //вернуть this
        if(tail==nullptr){
            Node<T>* buf = new Node<T>(item);
            head=buf;
            tail=buf;
        }else{
            Node<T>* buf = new Node<T>(item);
            tail->next=buf;
            tail = buf;
        }
        size++;
    }

    void Prepend(const T& item){
        if(head==nullptr){
            Node<T>* buf = new Node<T>(item);
            head=buf;
            tail=buf;
        }else{
            Node<T>* buf = new Node<T>(item);
            buf->next=head;
            head = buf;
        }
        size++;
    }

    void InsertAt(const T& item, int index){
        if(index>size||index<0) 
            throw std::out_of_range("Invalid index in insert function");
        Node<T>* current=head;
        for(int i=0;i<index-1;i++){
            current=current->next;
        }
        if(index==0){
            Prepend(item);
            size++; 
            return ;
        } 
        if(index==size){
            Append(item);
            size++;
            return ;
        }
        Node<T>* insert = new Node<T>(item);
        insert->next=current->next;
        current->next = insert;
        size++;
        return ;
    }

   void RemoveAt(int index){
        if(index>=size||index<0) 
            throw std::out_of_range("Invalid index in insert function");
        Node<T>* current=head;
        if(size==0){
            delete head;
            head=nullptr;
            tail=nullptr;
            size--;
            return ;
        } 
        if(index==0){
            Node<T>* buf = head;
            head = head->next;
            delete buf;
            size--;
            return ;
        } 
        if(index==size-1){
            Node<T>* buf = tail;
            tail = current;
            current->next=nullptr;
            delete buf;
            size--;
            return ;
        }
        for(int i=0;i<index-1;i++){
            current=current->next;
        }
        
        Node<T>* buf = current->next;
        current->next=buf->next;
        delete buf;
        size--;
        return ;
    }

    LinkedList<T>* Concat(const LinkedList<T>& list){
        LinkedList<T>* buf = new LinkedList<T>(*this);
        Node<T>* current=list.head;
        while(current!= nullptr){
            buf->Append(current->data);
            current=current->next;
        }
        buf->size=this->size+list.size;
        return buf;
    }

    T& operator[](int index){
        if(index<0) 
            throw std::invalid_argument("Invalid input in get operator");
        if(index>=size) 
            throw std::out_of_range("Invalid index in get operator");
        Node<T>* current = head;
        for(int i=0;i<index;i++){
            current=current->next;
        }
        return current->data;
    }
    LinkedList<T>& operator=(const LinkedList<T> list){ // COPY AND SWAP IDIOM
        swap(list);
        return *this;
    }   
    LinkedList<T>& operator+=(const LinkedList<T>& list2){ /// += FIRST
        Node<T>* current = list2.head;
        while(current!=nullptr){
            Append(current->data);
        }
        size+=list2.size;
    } 
     
    LinkedList<T> operator+(const LinkedList<T>& list){  /// += FIRST
        LinkedList<T> result = (*this);
        result+=list;
        return result;
    }

    bool operator==(const LinkedList<T>& list){
        if(list.size!=size) 
            return false;
        Node<T>* current1= list.head;
        Node<T>* current2 = head;
        while(current1!=nullptr){
            if(current1->data!=current2->data){
                return false;
            }
            current1=current1->next;
            current2=current2->next;
        }
        return true;
    }
    
    virtual ~LinkedList(){
        if(head!=nullptr){
            Node<T>* current = head;
            Node<T>* buf;
            while(current->next!=nullptr){
                buf = current->next;
                delete current;
                current = buf;
            }
            delete current;  
        }
    }
};