#pragma once


#include "ListSequence.h"
#include "ArraySequence.h"
#include "MapReduce.h"
#include <iostream>


void Delimiter(int length){
    std::cout<<std::endl;
    for(int i=0;i<length;i++){
        std::cout<<"=";
    }
    std::cout<<std::endl;
}

void demonstrateMutableArraySequence(){
    int fill1 = 2;
    int fill2 = 5;
    std::cout<<"MUTABLE ARRAY SEQUENCE"<<std::endl<<std::endl;
    std::cout<<"Первый заполняющий элемент : "<<fill1<<std::endl;
    std::cout<<"Второй заполняющий элемент : "<<fill2<<std::endl;
    MutableArraySequence<int> testlist1(fill1,5);
    MutableArraySequence<int> testlist2(fill2,7);
    std::cout<<"Первый Sequence размера 5 : ";
    testlist1.PrintSequence();
    std::cout<<std::endl;
    std::cout<<"Второй Sequence размера 7 : ";
    testlist2.PrintSequence();
    std::cout<<std::endl;

    std::cout<<std::endl;
    std::cout<<"SET FUNCTION "<<std::endl;
    testlist1.Set(10,3);
    testlist2[3]=-30;
    std::cout<<"Первый Sequence с 10 в четвёртом элементе : ";
    testlist1.PrintSequence();
    std::cout<<std::endl;
    std::cout<<"Второй Sequence с -30 в четвёртом элементе : ";
    testlist2.PrintSequence();
    std::cout<<std::endl;


    std::cout<<std::endl;
    //Copy constructor test
    std::cout<<"APPEND MUTABLE ARRAY SEQUENCE"<<std::endl;
    MutableArraySequence<int>* testlist4 =  new MutableArraySequence<int>(testlist1);
    std::cout<<"Sequence до Append :";
    testlist4->PrintSequence();
    std::cout<<std::endl;
    testlist4->Append(10);
    std::cout<<"Sequence после Append(10) :";
    testlist4->PrintSequence();
    std::cout<<std::endl;


    std::cout<<std::endl;
    std::cout<<"MUTABLE ARRAY SEQUENCE CONCAT"<<std::endl;
    MutableArraySequence<int>* testlist3 = testlist1.Concat(testlist2);
    std::cout<<"Первый Sequence : ";
    testlist1.PrintSequence();
    std::cout<<std::endl;
    std::cout<<"Второй Sequence : ";
    testlist2.PrintSequence();
    std::cout<<std::endl;
    std::cout<<"Результат конкатенации : ";
    testlist3->PrintSequence();
    std::cout<<std::endl;

    std::cout<<std::endl;
    std::cout<<"MUTABLE ARRAY SEQUENCE SUBSEQUENCE"<<std::endl;
    std::cout<<"Sequence из которой берётся подпоследовательность : ";
    testlist3->PrintSequence();
    std::cout<<std::endl;
    MutableArraySequence<int>* testlist5 =testlist3->GetSubsequence(2,8);
    std::cout<<"Результирующая подпоследовательность с третьего по девятый элемент  : ";
    testlist5->PrintSequence();
    std::cout<<std::endl;

    std::cout<<std::endl;
    std::cout<<"SPLIT MUTABLE ARRAY SEQUENCE"<<std::endl;
    int b[]={1,2,3,4,5,6};
    MutableArraySequence<int> testSplit1 (b,6);
    std::cout<<"Sequence до разделения : ";
    testSplit1.PrintSequence();
    std::cout<<std::endl;
    auto func { [](int i){ return i==3;  }};
    auto splitResult1 = testSplit1.Split(func);
    std::cout<<"Результат разделения по элементам кратным 3 : "<<std::endl;
    for(int i=0;i<splitResult1->GetLength();i++){
        splitResult1->Get(i)->PrintSequence();
        std::cout<<std::endl;
    }

    std::cout<<std::endl;
    std::cout<<"SLICE MUTABLE ARRAY SEQUENCE"<<std::endl;
    MutableArraySequence<int> testArraySlice(2,6);
    MutableArraySequence<int> testArraySliceAdd(6,2);
    std::cout<<"Sequence до slice : ";
    testArraySlice.PrintSequence();
    std::cout<<std::endl;
    std::cout<<"Sequence для slice : ";
    testArraySliceAdd.PrintSequence();
    std::cout<<std::endl;

    std::cout<<"Результат после slice начиная с индекса 2, длинною 3: ";
    auto testArraySliceResult1 = testArraySlice.Slice(2,3,testArraySliceAdd);
    testArraySliceResult1->PrintSequence();
    std::cout<<std::endl<<std::endl;


}

void demonstrateMutableListSequence(){
    int fill1 = 2;
    int fill2 = 5;
    std::cout<<"MUTABLE LIST SEQUENCE"<<std::endl<<std::endl;
    std::cout<<"Первый заполняющий элемент : "<<fill1<<std::endl;
    std::cout<<"Второй заполняющий элемент : "<<fill2<<std::endl;
    MutableListSequence<int> testlist1(fill1,5);
    MutableListSequence<int> testlist2(fill2,7);
    std::cout<<"Первый Sequence размера 5 : ";
    testlist1.PrintSequence();
    std::cout<<std::endl;
    std::cout<<"Второй Sequence размера 7 : ";
    testlist2.PrintSequence();
    std::cout<<std::endl;

    std::cout<<std::endl;
    std::cout<<"SET FUNCTION "<<std::endl;
    testlist1.Set(10,3);
    testlist2[3]=-30;
    std::cout<<"Первый Sequence с 10 в четвёртом элементе : ";
    testlist1.PrintSequence();
    std::cout<<std::endl;
    std::cout<<"Второй Sequence с -30 в четвёртом элементе : ";
    testlist2.PrintSequence();
    std::cout<<std::endl;


    std::cout<<std::endl;
    //Copy constructor test
    std::cout<<"APPEND MUTABLE LIST SEQUENCE"<<std::endl;
    MutableListSequence<int>* testlist4 =  new MutableListSequence<int>(testlist1);
    std::cout<<"Sequence до Append :";
    testlist4->PrintSequence();
    std::cout<<std::endl;
    testlist4->Append(10);
    std::cout<<"Sequence после Append(10) :";
    testlist4->PrintSequence();
    std::cout<<std::endl;


    std::cout<<std::endl;
    std::cout<<"MUTABLE LIST SEQUENCE CONCAT"<<std::endl;
    MutableListSequence<int>* testlist3 = testlist1.Concat(testlist2);
    std::cout<<"Первый Sequence : ";
    testlist1.PrintSequence();
    std::cout<<std::endl;
    std::cout<<"Второй Sequence : ";
    testlist2.PrintSequence();
    std::cout<<std::endl;
    std::cout<<"Результат конкатенации : ";
    testlist3->PrintSequence();
    std::cout<<std::endl;

    std::cout<<std::endl;
    std::cout<<"MUTABLE LIST SEQUENCE SUBSEQUENCE"<<std::endl;
    std::cout<<"Sequence из которой берётся подпоследовательность : ";
    testlist3->PrintSequence();
    std::cout<<std::endl;
    MutableListSequence<int>* testlist5 =testlist3->GetSubsequence(2,8);
    std::cout<<"Результирующая подпоследовательность с третьего по девятый элемент  : ";
    testlist5->PrintSequence();
    std::cout<<std::endl;

    std::cout<<std::endl;
    std::cout<<"SPLIT MUTABLE LIST SEQUENCE"<<std::endl;
    int b[]={1,2,3,4,5,6};
    MutableListSequence<int> testSplit1 (b,6);
    std::cout<<"Sequence до разделения : ";
    testSplit1.PrintSequence();
    std::cout<<std::endl;
    auto func { [](int i){ return i==3;  }};
    auto splitResult1 = testSplit1.Split(func);
    std::cout<<"Результат разделения по элементам кратным 3 : "<<std::endl;
    for(int i=0;i<splitResult1->GetLength();i++){
        splitResult1->Get(i)->PrintSequence();
        std::cout<<std::endl;
    }

    std::cout<<std::endl;
    std::cout<<"SLICE MUTABLE LIST SEQUENCE"<<std::endl;
    MutableListSequence<int> testListSlice(2,6);
    MutableListSequence<int> testListSliceAdd(6,2);
    std::cout<<"Sequence до slice : ";
    testListSlice.PrintSequence();
    std::cout<<std::endl;
    std::cout<<"Sequence для slice : ";
    testListSliceAdd.PrintSequence();
    std::cout<<std::endl;

    std::cout<<"Результат после slice начиная с индекса 2, длинною 3: ";
    auto testListSliceResult = testListSlice.Slice(2,3,testListSliceAdd);
    testListSliceResult->PrintSequence();
    std::cout<<std::endl<<std::endl;
}
int testForMap(int i ) 
{ 
    return 2*i;  
}
bool testForWhere(int i){
    return i%2==0;
}
int testForReduce(int a,int b ) 
{ 
    return a+b;  
}
void demonstartionMapReduce(){
    //auto testForMap { [](int i){ return 2*i;  }};
    std::cout<<"MAP FUNCTION"<<std::endl;
    std::cout<<"Исходный Sequence  : ";
    MutableListSequence<int> testMap1(2,5);
    testMap1.PrintSequence();
    std::cout<<std::endl;

    MutableArraySequence<int> mapResult1 = map(testMap1,&testForMap);
    std::cout<<"Результат операции map(умножает исходное на 2) : ";
    mapResult1.PrintSequence();
    std::cout<<std::endl;

    std::cout<<std::endl;
    std::cout<<"WHERE FUNCTION"<<std::endl;
    int a[4]={1,2,3,4};
    MutableListSequence<int> testWhere(a,4);
    std::cout<<"Исходный Sequence  : ";
    testWhere.PrintSequence();
    std::cout<<std::endl;
    std::cout<<"Результат выборки where по чётным числам : ";
    MutableArraySequence<int> whereResult = where(testWhere,&testForWhere);
    whereResult.PrintSequence();
    std::cout<<std::endl;

    std::cout<<std::endl;
    std::cout<<"REDUCE FUNCTION"<<std::endl;
    int c[4]={1,2,3,4};
    MutableListSequence<int> testReduce(c,4);
    std::cout<<"Исходный Sequence  : ";
    int start =0;
    testReduce.PrintSequence();
    std::cout<<std::endl;
    std::cout<<"Результат reduce от функции суммирования : ";
    auto ReduceResult = reduce(testWhere,&testForReduce,start);
    std::cout<<ReduceResult<<std::endl;


    std::cout<<std::endl;        
    std::cout<<"ZIP TEST"<<std::endl;
    MutableArraySequence<int> test_1(1,2);
    test_1[0]=1;
    test_1[1]=2;
    std::cout<<"Первый Sequence  : ";
    test_1.PrintSequence();
    std::cout<<std::endl;
    MutableArraySequence<double> test_2(2.0,3);
    test_2[0]=3.1;
    test_2[1]=4.2;
    test_2[2]=5.2;
    std::cout<<"Второй Sequence  : ";
    test_2.PrintSequence();
    std::cout<<std::endl;
    MutableArraySequence<char> test_3('a',2);
    test_3[0]='a';
    test_3[1]='b';
    std::cout<<"Третий Sequence  : ";
    test_3.PrintSequence();
    std::cout<<std::endl;

    auto test_4 = zip<int,double,char>(test_1,test_2,test_3) ;
    std::cout<<"Результат функции ZIP : "<<std::endl;
    for(int i =0; i<test_4.GetLength();i++){
        std::cout<<"Элемент номер "<<i<<" : ";
        printTuple( test_4.Get(i) );
        std::cout<<std::endl;
    }

    std::cout<<std::endl;
    std::cout<<"UNZIP TEST"<<std::endl;
    std::cout<<"Входной  ZipSequence : "<<std::endl;
    for(int i =0; i<test_4.GetLength();i++){
        std::cout<<"Элемент номер "<<i<<" : ";
        printTuple( test_4.Get(i) );
        std::cout<<std::endl;
    }
    
    auto TEST =  unzip(test_4);
    std::cout<<"Результат функции UNZIP : "<<std::endl;

    std::cout<<"Первый Sequence : ";
    Get<0>(TEST)->PrintSequence();
    std::cout<<std::endl;

    std::cout<<"Второй Sequence : ";
    Get<1>(TEST)->PrintSequence();
    std::cout<<std::endl;

    std::cout<<"Третий Sequence : ";
    Get<2>(TEST)->PrintSequence();
    std::cout<<std::endl;
    
 
}