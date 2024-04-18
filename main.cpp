
#include "ListSequence.h"
#include "ArraySequence.h"
#include "MapReduce.h"
#include "Testing.h"
#include <iostream>
//clang++ main.cpp -Wall -Wextra -o main.exe -v
int testForMap(int i){
    return 5*i;
}
bool testForWhere(int i){
    return i%2==0;
}

int main(){
    Test_DynamicArray();
    Test_LinkedList();
    Test_ArraySequence();
    Test_ListSequence();
    Test_MyTuple();
    Test_MapReduce();
    std::cout<<"Tested successfully"<<std::endl;
    /*
    int fill1 = 5;
    int fill2 = 13;

    MutableArraySequence<int> testlist1(fill1,5);
    MutableArraySequence<int> testlist2(fill2,7);
    testlist1.PrintSequence();
    testlist2.PrintSequence();
    testlist1.Set(10,3);
    testlist2[3]=-30;
    testlist1.PrintSequence();
    testlist2.PrintSequence();
    testlist2.Append(-30);
    testlist2.PrintSequence();



    
    //Copy constructor test
    MutableArraySequence<int>* testlist4 =  new MutableArraySequence<int>(testlist1);
    testlist4->PrintSequence();
    testlist4->Append(10);
    testlist4->PrintSequence();
    std::cout<<"MUTABLE ARRAY CONCAT"<<std::endl;
    MutableArraySequence<int>* testlist3 = testlist1.Concat(testlist2);
    testlist3->PrintSequence();
    std::cout<<"MUTABLE ARRAY SUBSEQUENCE"<<std::endl;
    MutableArraySequence<int>* testlist5 =testlist3->GetSubsequence(2,8);
    testlist5->PrintSequence();
    std::cout<<"IMMUTABLE ARRAY SEQUENCE"<<std::endl;

    ImmutableArraySequence<int> testlist11(4,10);
    ImmutableArraySequence<int> testlist12(23,5);
    testlist11.PrintSequence();
    testlist12.PrintSequence();
    testlist12.Set(20,3);
    testlist11.Append(29);
    testlist12.Append(29);
    std::cout<<"IMMUTABLE ARRAY - CANT CHANGE"<<std::endl;
    testlist11.PrintSequence();
    testlist12.PrintSequence();
    std::cout<<"IMMUTABLE ARRAY CHANGE"<<std::endl;
    ImmutableArraySequence<int>* testlist13 = static_cast<ImmutableArraySequence<int>*>(testlist11.Set(20,3)) ;
    testlist11.PrintSequence();
    testlist13->PrintSequence();

    ImmutableArraySequence<int> testlist141(4,4);
    ImmutableArraySequence<int> testlist151(23,5);
    ImmutableArraySequence<int>* testlist161 =testlist141.Concat(testlist151);
    std::cout<<"IMMUTABLE CONCAT"<<std::endl;
    testlist141.PrintSequence();
    testlist151.PrintSequence();
    testlist161->PrintSequence();
    std::cout<<"IMMUTABLE SUBSEQUENCE"<<std::endl;
    ImmutableArraySequence<int>* testlist171 =testlist161->GetSubsequence(2,6);
    testlist171->PrintSequence();

    
    std::cout<<"MUTABLE LIST SEQUENCE "<<std::endl;
    MutableListSequence<int> testlist100(fill1,5);
    testlist100.PrintSequence();
    MutableListSequence<int> testlist200(fill2,7);
    testlist200.PrintSequence();
    testlist100.Set(10,3);
    testlist100.PrintSequence();
    testlist200.Set(-30,3);
    testlist200.PrintSequence();
    testlist200.Prepend(-30);
    testlist200.PrintSequence();
    std::cout<<"MUTABLE LIST COPY "<<std::endl;
    MutableListSequence<int>* testlist400 =  new MutableListSequence<int>(testlist100);
    testlist400->PrintSequence();
    testlist400->Append(10);
    testlist400->PrintSequence();
    std::cout<<"MUTABLE LIST CONCAT "<<std::endl;
    MutableListSequence<int>* testlist300 = testlist100.Concat(testlist200);
    testlist300->PrintSequence();
    std::cout<<"MUTABLE LIST SUBSEQUENCE "<<std::endl;
    MutableListSequence<int>* testlist500 =testlist300->GetSubsequence(3,6);
    testlist500->PrintSequence();
    
    std::cout<<"IMMUTABLE LIST SEQUENCE"<<std::endl;
    ImmutableListSequence<int> testlist110(4,10);
    ImmutableListSequence<int> testlist120(23,5);
    testlist110.PrintSequence();
    testlist120.PrintSequence();
    testlist120.Set(20,3);
    testlist110.Append(29);
    testlist120.Append(29);
    std::cout<<"IMMUTABLE LIST CANT CHANGE "<<std::endl;
    testlist110.PrintSequence();
    testlist120.PrintSequence();
    MutableListSequence<int>* testlist130 = static_cast<MutableListSequence<int>*>(testlist110.Set(20,3)) ;
    std::cout<<"CHANGE IMMUTABLE LIST RETURN "<<std::endl;
    testlist110.PrintSequence();
    testlist130->PrintSequence();
    
    std::cout<<"IMMUTABLE LIST CONCAT "<<std::endl;

    ImmutableListSequence<int> testlist1410(4,4);
    ImmutableListSequence<int> testlist1510(23,5);
    ImmutableListSequence<int>* testlist1610 =testlist1410.Concat(testlist1510);
    testlist1410.PrintSequence();
    testlist1510.PrintSequence();
    testlist1610->PrintSequence();
    std::cout<<"IMMUTABLE LIST SUBSEQ "<<std::endl;
    ImmutableListSequence<int>* testlist1710 =testlist1610->GetSubsequence(2,6);
    testlist1710->PrintSequence();

    std::cout<<"DIFFERENT SEQUENCE TEST"<<std::endl;
    MutableListSequence<int> testL1(2,5);
    MutableArraySequence<int> testA1(4,5);
    MutableArraySequence<int>* testArrayICONCAT =testA1.Concat(testL1);
    MutableListSequence<int>* testlistICONCAT =testL1.Concat(testA1);
    MutableArraySequence<int>* testA2 = new MutableArraySequence<int>(testL1);
    MutableListSequence<int>* testL2 =new MutableListSequence<int>(testA1);
    
    testA1.PrintSequence();
    testL1.PrintSequence();

    testA2->PrintSequence();
    testL2->PrintSequence();

    testlistICONCAT->PrintSequence();
    testArrayICONCAT->PrintSequence();

    testA1.PrintSequence();
    testA1[0]=1;
    testA1[1]=2;
    testA1[2]=3;
    testA1[3]=4;
    testA1[4]=5;
    testA1.PrintSequence();
    std::cout<<"ArraySlice TEST"<<std::endl;
    MutableArraySequence<int> testArraySlice(2,6);
    MutableArraySequence<int> testArraySliceAdd(6,2);
    testArraySlice.PrintSequence();
    testArraySlice.Slice(2,3,testArraySliceAdd);
    testArraySlice.PrintSequence();
    std::cout<<"ArraySlice - TEST"<<std::endl;
    MutableArraySequence<int> testArraySlice2(2,6);
    testArraySlice2.PrintSequence();
    testArraySlice2.Slice(-4,3,testArraySliceAdd);
    testArraySlice2.PrintSequence();

    std::cout<<"ListSlice TEST"<<std::endl;
    MutableListSequence<int> testListSlice(2,6);
    MutableListSequence<int> testListSliceAdd(6,2);
    testListSlice.PrintSequence();
    testListSlice.Slice(2,3,testListSliceAdd);
    testListSlice.PrintSequence();

    std::cout<<"Split TEST"<<std::endl;
    int b[]={1,2,3,4,5,6};
    MutableArraySequence<int> testSplit1 (b,6);
    MutableListSequence<int> testSplit2 (b,6);
    ImmutableArraySequence<int> testSplit3 (b,6);
    ImmutableListSequence<int> testSplit4 (b,6);
    testSplit1 .PrintSequence();
    auto func { [](int i){ return i==3;  }};
    auto splitResult1 = testSplit1.Split(func);
    auto splitResult2 = testSplit2.Split(func);
    auto splitResult3 = testSplit3.Split(func);
    auto splitResult4 = testSplit4.Split(func);
    std::cout<<"SplitArrayM"<<splitResult1->GetLength()<<std::endl;
    for(int i=0;i<splitResult1->GetLength();i++){
        splitResult1->Get(i)->PrintSequence();
    }
    std::cout<<"SplitArrayIm"<<splitResult2->GetLength()<<std::endl;
    for(int i=0;i<splitResult2->GetLength();i++){
        splitResult2->Get(i)->PrintSequence();
    }
    std::cout<<"SplitListM"<<splitResult3->GetLength()<<testSplit3.GetLength()<<std::endl;
    for(int i=0;i<splitResult3->GetLength();i++){
        splitResult3->Get(i)->PrintSequence();
    }
    std::cout<<"SplitListIm"<<splitResult4->GetLength()<<testSplit4.GetLength()<<std::endl;
    for(int i=0;i<splitResult4->GetLength();i++){
        splitResult4->Get(i)->PrintSequence();
    }
    

    std::cout<<"Map TEST"<<std::endl;
    MutableListSequence<int> testMap(2,5);
    testMap.PrintSequence();
    MutableArraySequence<int> mapResult = map(testMap,&testForMap);\
    mapResult.PrintSequence();

    std::cout<<"Where TEST"<<std::endl;
    int a[4]={1,2,3,4};
    MutableListSequence<int> testWhere(a,4);
    testWhere.PrintSequence();
    MutableArraySequence<int> whereResult = where(testWhere,&testForWhere);\
    whereResult.PrintSequence();


                        //MyTuple
    std::cout<<"MyTuple TEST"<<std::endl;
    Tuple_<int,double,char> tup (1,2.4,'u');
    Tuple_<int,int,double,char>* tups = new Tuple_<int,int,double,char>(3,713,9.0,'f');
    printTuple( *tups);
    printTuple( tup);
    std::cout<<Get<0>(tup)<<std::endl;
                        //ZIP
    std::cout<<"ZIP TEST"<<std::endl;
    MutableArraySequence<int> test_1(1,2);
    test_1[0]=1;
    test_1[1]=2;
    MutableArraySequence<double> test_2(2.0,3);
    test_2[0]=3.1;
    test_2[1]=4.2;
    test_2[2]=5.2;
    MutableArraySequence<int> test_3(3,2);
    test_3[0]=5;
    test_3[1]=6;

    test_1.PrintSequence();
    test_2.PrintSequence();
    test_3.PrintSequence();
    auto test_4 = zip<int,double>(test_1,test_2) ;
        

    for(int i =0; i<test_4.GetLength();i++){
        printTuple( test_4.Get(i) );
        std::cout<<std::endl;
    }

                        //Unzip
    //Tuple_< MutableArraySequence<int>*,MutableArraySequence<double>* > * TEST =
    auto TEST =  unzip<int,double>(test_4);
    std::cout<<"__"<<std::endl;
    std::cout<<(Get<0>(TEST))->GetLength()<<std::endl;
    std::cout<<"__"<<std::endl;
    Get<0>(TEST)->PrintSequence();
    Get<1>(TEST)->PrintSequence();
    
    
    
 


    */
    return 0;
}