#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"

#include <iostream>
//clang++ main.cpp -Wall -Wextra main.exe -v
int main(){
    int fill1 = 5;
    int fill3 = 10;
    int fill2 = 13;
    MutableArraySequence<int> testlist1(fill1,5);
    MutableArraySequence<int> testlist2(fill2,7);
    ImmutableArraySequence<int> testlist5(fill3,10);
    testlist1.PrintSequence();
    testlist2.PrintSequence();
    testlist5.PrintSequence();
    testlist1.Set(10,3);
    testlist2.Set(-30,3);
    testlist1.PrintSequence();
    testlist2.PrintSequence();
    MutableArraySequence<int>* testlist3 = testlist1.Concat(testlist2);
    testlist3->PrintSequence();
    testlist3->RemoveAt(3);
    testlist3->RemoveAt(7);
    testlist3->PrintSequence();
    MutableArraySequence<int>* testlist4 =testlist3->GetSubsequence(3,5);
    testlist4->PrintSequence();
    (*testlist4)[2]= 231;
    testlist4->PrintSequence();
    testlist5.PrintSequence();
    testlist5.Set(-30,3);
    testlist5.PrintSequence();
    return 0;
}