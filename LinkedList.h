#pragma once
#include <cstring>

template <typename T>
class Node{
public:
    Node* next=nullptr;
    T data;
    Node(T indata):data(indata),next(NULL){};
    Node(T indata,T* ptr):data(indata),next(ptr){};
};


template <typename T>
class LinkedList{
private:
    Node<T>* head=nullptr;
    Node<T>* tail=nullptr;
    int size = 0;

    void swap(LinkedList<T>& toSwap){
        std::swap(size,toSwap.size);
        std::swap(head,toSwap.head);
        std::swap(tail,toSwap.tail);
    }
public:
    LinkedList ():head(NULL),tail(NULL),size(0){};
    LinkedList (T* items, int count):size(count){
        if(count<0) throw std::invalid_argument("invalid argument in constuctor");
        for(int i=0;i<count,i++){
            Append(items[i]);
        }
    }
    LinkedList (const LinkedList<T>& list ):LinkedList(){
        Node<T>* currentToCopy =list.head;
        while(currentToCopy!=NULL){
            Append(currentToCopy->data);
            currentToCopy=currentToCopy->next;
        }
        this->size=list.size;
    }

    T GetFirst() const {
        if(head==nullptr){
            throw std::out_of_range("Getter call in empty collection");
        }
        return head->data;
    }
    T GetLast() const{
        if(tail==nullptr){
            throw std::out_of_range("Getter call in empty collection");
        }
        return tail->data;
    }
    T Get(int index) const {
        if(index<0||index>=size) throw std::std::out_of_range("Getter call with wrong index ");
        Node<T>* current = head;
        for(int i=0;i<index-1;i++){
            current=current->next;
        }
        return current->data;
    }
    void Set(const T& value ,int index)  {
        if(index<0||index>=size) throw std::std::out_of_range("Setter call with wrong index ");
        Node<T>* current = head;
        for(int i=0;i<index-1;i++){
            current=current->next;
        }
        current->data=value;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex){
        if(endIndex>=size) throw std::out_of_range("Invalid index in SubList function");
        if(startIndex<0||endIndex<0||endIndex<startIndex) throw std::invalid_argument("Invalid input in SubList function");
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
    }

    int GetLength() const{ return size; }

    void Append(const T& item){
        if(head==nullptr){
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
        if(index>size||index<0) throw std::out_of_range("Invalid index in insert function");
        if(head==nullptr){
            Append(item);
            size++;
            return 0;
        }
        Node<T> current(head->data,head);
        for(int i=0;i<index;i++){
            current=current->next;
        }
        if(current->next==head){
            Prepend(item);
            size++; 
            return 0;
        } 
        if(current->next==tail){
            Append(item);
            size++;
            return 0;
        }
        Node<T>* insert = new Node(item);
        insert->next=current->next;
        current->next = insert;
        size++;
        return 0;
    }

   void RemoveAt(int index){
        if(index>=size||index<0) throw std::out_of_range("Invalid index in insert function");
        Node<T> current(head->data,head);
        for(int i=0;i<index;i++){
            current=current->next;
        }
        if(current->next==head){
            Node<T>* buf = head;
            head = head->next
            delete buf;
            size--;
            return 0;
        } 
        if(current->next==tail){
            Node<T>* buf = tail;
            tail = current;
            current->next=nullptr;
            delete buf;
            size--;
            return 0;
        }
        Node<T>* buf = current->next;
        current->next=buf->next;
        delete buf;
        size--;
        return 0;
    }

    LinkedList<T>* Concat(const LinkedList<T>* list){
        if(list == nullptr) throw std::invalid_argument("Invalid argument in Concat function");
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
        if(index<0) throw std::invalid_argument("Invalid input in get operator");
        if(index>=size) throw std::out_of_range("Invalid index in get operator");
        Node<T>* current = head;
        for(int i=0;i<index-1;i++){
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
        if(list.size!=size) return false;
        Node<T>* current1= list->head;
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
            Node* current = head;
            Node* buf;
            while(current->next!=nullptr){
                buf = current->next;
                delete current;
                current = buf;
            }
            delete current;  
        }
    }
};