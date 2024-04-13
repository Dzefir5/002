
#include "ListSequence.h"
#include "ArraySequence.h"
#include "MapReduce.h"
#include <iostream>
//clang++ main.cpp -Wall -Wextra -o main.exe -v
int main(){
    int fill1 = 5;
    int fill3 = 10;
    int fill2 = 13;

   /* MutableArraySequence<int> testlist1(fill1,5);
    MutableArraySequence<int> testlist2(fill2,7);
    testlist1.PrintSequence();
    testlist2.PrintSequence();
    testlist1.Set(10,3);
    testlist2.Set(-30,3);
    testlist1.PrintSequence();
    testlist2.PrintSequence();
    testlist2.Append(-30);
    testlist2.PrintSequence();
    MutableArraySequence<int>* testlist4 =  new MutableArraySequence<int>(testlist1);
    testlist4->PrintSequence();
    testlist4->Append(10);
    testlist4->PrintSequence();
    std::cout<<"_____________"<<std::endl;
    MutableArraySequence<int>* testlist3 = testlist1.Concat(testlist2);
    std::cout<<testlist3->GetLength()<<std::endl;
    testlist3->PrintSequence();
    std::cout<<"_____________"<<std::endl;

    ImmutableArraySequence<int> testlist11(4,10);
    ImmutableArraySequence<int> testlist12(23,5);
    testlist11.PrintSequence();
    testlist12.PrintSequence();
    testlist12.Set(20,3);
    testlist11.Append(29);
    testlist12.Append(29);
    MutableArraySequence<int>* testlist13 = static_cast<MutableArraySequence<int>*>(testlist11.Set(20,3)) ;
    testlist11.PrintSequence();
    testlist13->PrintSequence();
     std::cout<<"MutableArrayConcat_____1"<<std::endl;
    MutableArraySequence<int> testlist14(4,4);
    MutableArraySequence<int> testlist15(23,5);
    MutableArraySequence<int>* testlist16 =testlist14.Concat(testlist15);
    testlist14.PrintSequence();
    testlist15.PrintSequence();
    testlist16->PrintSequence();
    std::cout<<"___________2"<<std::endl;
    MutableArraySequence<int>* testlist17 =testlist16->GetSubsequence(3,6);
    testlist17->PrintSequence();
    std::cout<<"ImmutableArrayConcat____3"<<std::endl;

    ImmutableArraySequence<int> testlist141(4,4);
    ImmutableArraySequence<int> testlist151(23,5);
    ImmutableArraySequence<int>* testlist161 =testlist141.Concat(testlist151);
    std::cout<<"________4"<<std::endl;
    testlist141.PrintSequence();
    testlist151.PrintSequence();
    testlist161->PrintSequence();
    std::cout<<"ImmutableArrayGetSubSeq_____5"<<std::endl;
    ImmutableArraySequence<int>* testlist171 =testlist161->GetSubsequence(2,6);
    testlist171->PrintSequence();
    std::cout<<"_____________6"<<std::endl;
    */

    MutableListSequence<int> testlist1(fill1,5);
    testlist1.PrintSequence();
    std::cout<<testlist1.GetLength()<<std::endl;
    MutableListSequence<int> testlist2(fill2,7);
    testlist2.PrintSequence();
    std::cout<<testlist2.GetLength()<<std::endl;
    testlist1.Set(10,3);
    testlist1.PrintSequence();
    testlist2.Set(-30,3);
    testlist2.PrintSequence();
    testlist2.Prepend(-30);
    std::cout<<testlist2.GetLength()<<std::endl;
    testlist2.PrintSequence();
    MutableListSequence<int>* testlist4 =  new MutableListSequence<int>(testlist1);
    testlist4->PrintSequence();
    testlist4->Append(10);
    testlist4->PrintSequence();
    std::cout<<"_____________"<<std::endl;
    MutableListSequence<int>* testlist3 = testlist1.Concat(testlist2);
    std::cout<<testlist3->GetLength()<<std::endl;
    testlist3->PrintSequence();
    std::cout<<"_____________"<<std::endl;

    ImmutableListSequence<int> testlist11(4,10);
    ImmutableListSequence<int> testlist12(23,5);
    testlist11.PrintSequence();
    testlist12.PrintSequence();
    testlist12.Set(20,3);
    testlist11.Append(29);
    testlist12.Append(29);
    MutableListSequence<int>* testlist13 = static_cast<MutableListSequence<int>*>(testlist11.Set(20,3)) ;
    testlist11.PrintSequence();
    testlist13->PrintSequence();
     std::cout<<"MutableArrayConcat_____1"<<std::endl;
    MutableListSequence<int> testlist14(4,4);
    MutableListSequence<int> testlist15(23,5);
    MutableListSequence<int>* testlist16 =testlist14.Concat(testlist15);
    testlist14.PrintSequence();
    testlist15.PrintSequence();
    testlist16->PrintSequence();
    std::cout<<"___________2"<<std::endl;
    MutableListSequence<int>* testlist17 =testlist16->GetSubsequence(3,6);
    testlist17->PrintSequence();
    std::cout<<"ImmutableArrayConcat____3"<<std::endl;

    ImmutableListSequence<int> testlist141(4,4);
    ImmutableListSequence<int> testlist151(23,5);
    ImmutableListSequence<int>* testlist161 =testlist141.Concat(testlist151);
    std::cout<<"________4"<<std::endl;
    testlist141.PrintSequence();
    testlist151.PrintSequence();
    testlist161->PrintSequence();
    std::cout<<"ImmutableArrayGetSubSeq_____5"<<std::endl;
    ImmutableListSequence<int>* testlist171 =testlist161->GetSubsequence(2,6);
    testlist171->PrintSequence();
    std::cout<<"_____________6"<<std::endl;


    std::cout<<"DIFFERENT SEQUENCE TEST"<<std::endl;
    MutableListSequence<int> testL1(2,4);
    MutableArraySequence<int> testA1(4,4);
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
    testA1[2]=5;
    testA1.PrintSequence();
    //testlist12.PrintSequence();
    /*ImmutableArraySequence<int>* testlist13 = testlist11.Concat(testlist12);
    testlist13->PrintSequence();
    testlist13->Set(80,3);
    testlist13->PrintSequence();*/

    
    /*testlist3->RemoveAt(3);
    testlist3->RemoveAt(7);
    testlist3->PrintSequence();
    MutableArraySequence<int>* testlist4 =testlist3->GetSubsequence(3,5);
    testlist4->PrintSequence();
    (*testlist4)[2]= 231;
    testlist4->PrintSequence();
    testlist5.PrintSequence();
    testlist5.Set(-30,3);
    testlist5.PrintSequence();*/
    return 0;
}