#pragma once
#include "LinkedList.h"
#include <cassert>

void Test_LinkedList_Constructors(){
    int a[]={1,2,3,4,5,6};
    int fillElem = 8;

    LinkedList<int> test1(6);
    assert(test1.GetLength()==6);

    LinkedList<int> test2(a,6);
    assert(test2.GetLength()==6);
    for(int i=0;i<test2.GetLength();i++){
        assert(test2.Get(i)==a[i]);
    }
    LinkedList<int> test3(fillElem,7);
    assert(test3.GetLength()==7);
    for(int i=0;i<test3.GetLength();i++){
        assert(test3.Get(i)==fillElem);
    }
    LinkedList<int> test4(test2);
    assert(test4.GetLength()==test2.GetLength());
    for(int i=0;i<test4.GetLength();i++){
        assert(test2.Get(i)==test4.Get(i));
    }
}
void Test_LinkedList_Set(){
    int a[]={1,2,3,4,5,6};
    LinkedList<int> test5(a,6);
    assert(test5.GetLength()==6);
    assert(test5.Get(3)==a[3]);
    test5.Set(9,3);
    assert(test5.Get(3)==9);
    test5[3]=10;
    assert(test5[3]==10);
}

void Test_LinkedList_Insert(){
    int a[]={1,2,3,4,5,6};
    LinkedList<int> test5(a,6);
    test5.InsertAt(12,3);
    assert(test5[3]==12);
}
void Test_LinkedList_Remove(){
    int a[]={1,2,3,4,5,6};
    LinkedList<int> test5(a,6);
    test5.RemoveAt(1);
    assert(test5.Get(1)==a[2]);
}
void Test_LinkedList_Concat(){
    int b[]={1,2,3};
    int c[]={4,5,6};
    int bc[]={1,2,3,4,5,6};
    LinkedList<int> test6(b,3);
    LinkedList<int> test7(c,3);
    LinkedList<int>* test8 = test6.Concat(test7);
    assert(test8->GetLength()==test6.GetLength()+test7.GetLength());
    for(int i=0;i<test8->GetLength();i++){
        assert(test8->Get(i)==bc[i]);
    }
}
void Test_LinkedList_Append(){
    int a[]={1,2,3,4,5,6};
    LinkedList<int> test10(a,6);
    test10.Append(10);
    assert(test10.GetLast()==10 );
}

void Test_LinkedList_SubList(){
    int a[]={1,2,3,4,5,6};
    int b[]={3,4,5};
    LinkedList<int> test10(a,6);
    LinkedList<int>* test11 = test10.GetSubList(2,4);
    for(int i=0;i<test11->GetLength();i++){
        assert(test11->Get(i)==b[i]);
    }
}
void Test_LinkedList_Prepend(){
    int a[]={1,2,3,4,5,6};
    LinkedList<int> test10(a,6);
    test10.Prepend(10);
    assert(test10.GetFirst()==10 );

}

void Test_LinkedList_CompareOperator(){
    int a[]={1,2,3,4,5,6};
    LinkedList<int> test10(a,6);
    LinkedList<int> test11(a,6);
    assert(test10==test11 );
    test11[4]=1323;
    assert(! (test10==test11) );

}