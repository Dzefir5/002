#pragma once
#include "ListSequence.h"
#include <cassert>


void Test_ListSequence_Constuctors(){
    int a[]={1,2,3,4,5,6};
    int fillElem = 8;

    MutableListSequence<int> testM1(6);
    assert(testM1.GetLength()==6);
    ImmutableListSequence<int> testIm1(6);
    assert(testIm1.GetLength()==6);

    MutableListSequence<int> testM2(a,6);
    assert(testM2.GetLength()==6);
    for(int i=0;i<testM2.GetLength();i++){
        assert(testM2.Get(i)==a[i]);
    }
    ImmutableListSequence<int> testIm2(a,6);
    assert(testIm2.GetLength()==6);
    for(int i=0;i<testIm2.GetLength();i++){
        assert(testIm2.Get(i)==a[i]);
    }

    MutableListSequence<int> testM4(testM2);
    assert(testM4.GetLength()==testM2.GetLength());
    ImmutableListSequence<int> testIm4(testIm2);
    assert(testIm4.GetLength()==testIm2.GetLength());
    for(int i=0;i<testM4.GetLength();i++){
        assert(testM2.Get(i)==testM4.Get(i));
    }
    for(int i=0;i<testIm4.GetLength();i++){
        assert(testIm2.Get(i)==testIm4.Get(i));
    }

    MutableListSequence<int> testM3(fillElem,7);
    assert(testM3.GetLength()==7);
    ImmutableListSequence<int> testIm3(fillElem,7);
    assert(testIm3.GetLength()==7);
    for(int i=0;i<testM3.GetLength();i++){
        assert(testM3.Get(i)==fillElem);
    }
    for(int i=0;i<testIm3.GetLength();i++){
        assert(testIm3.Get(i)==fillElem);
    }
    return;
}
void Test_ListSequence_Append(){
    int a[]={1,2,3,4,5,6};
    MutableListSequence<int> test(a,6);
    test.Append(10);
    assert(test.GetLength()==7);
    assert(test.GetLast()==10);
}
void Test_ListSequence_Prepend(){
    int a[]={1,2,3,4,5,6};
    MutableListSequence<int> test(a,6);
    test.Prepend(10);
    assert(test.GetLength()==7);
    assert(test.GetFirst()==10);
}
void Test_ListSequence_InsertAt(){
    int a[]={1,2,3,4,5,6};
    MutableListSequence<int> test(a,6);
    test.InsertAt(10,3);
    assert(test.GetLength()==7);
    assert(test.Get(3)==10);
}
void Test_ListSequence_RemoveAt(){
    int a[]={1,2,3,4,5,6};
    MutableListSequence<int> test(a,6);
    test.RemoveAt(3);
    assert(test.GetLength()==5);
    assert(test.Get(3)==5);
}
void Test_ListSequence_Set(){
    int a[]={1,2,3,4,5,6};
    MutableListSequence<int> test(a,6);
    test.Set(10,4);
    assert(test.Get(4)==10);
}
void Test_ListSequence_AccessOperator(){
    int a[]={1,2,3,4,5,6};
    MutableListSequence<int> test(a,6);
    test[4]=10;
    assert(test.Get(4)==10);
}
void Test_ListSequence_CompareOperator(){
    int a[]={1,2,3,4,5,6};
    MutableListSequence<int> test10(a,6);
    MutableListSequence<int> test11(a,6);
    assert(test10==test11 );
    test11[4]=1323;
    assert(! (test10==test11) );
}
void Test_ListSequence_Slice(){
    int b[]={1,2,3,4,5,6,7};
    int c[]={10,11};
    int d[]={1,2,10,11,6,7};
    MutableListSequence<int> testM2(b,7);
    MutableListSequence<int> testM3(c,2);
    auto testM4 = testM2.Slice(2,3,testM3);
    auto testM5 = testM2.Slice(-5,3,testM3);
    assert(testM4->GetLength()==6);
    assert(testM5->GetLength()==6);
    for(int i=0;i<testM4->GetLength();i++){
        assert(testM4->Get(i)==d[i]);
    }
    for(int i=0;i<testM5->GetLength();i++){
        assert(testM5->Get(i)==d[i]);
    }
}

void Test_ListSequence_Split(){
    int e[]={1,2,3,4,5,6,7,8,9,10};
    MutableListSequence<int> testSplit1 (e,10);
    auto func { [](int i){ return i==5;  }};
    auto splitResult1 = testSplit1.Split(func);
    int ex[2][5]= { {1,2,3,4,5},{6,7,8,9,10} };
    for(int i=0;i<splitResult1->GetLength();i++){
        for(int j=0;j<splitResult1->Get(i)->GetLength();j++){
            assert(ex[i][j]==splitResult1->Get(i)->Get(j));
        }
    }
}

void Test_ListSequence_Concat(){
    int f[]={1,2,3,4};
    int m[]={5,6,7};
    int n[]={1,2,3,4,5,6,7};
    MutableListSequence<int> testConcat1 (f,4);
    MutableListSequence<int> testConcat2 (m,3);
    MutableListSequence<int>* testConcat = testConcat1.Concat(testConcat2);
    for(int i=0;i<testConcat->GetLength();i++){
        assert(testConcat->Get(i)==n[i]);
    }
}
void Test_ListSequence_SubSequence(){
    int n[]={1,2,3,4,5,6,7};
    MutableListSequence<int> test (n,7);
    int subseq[]={3,4,5,6};
    MutableListSequence<int>* testSubSeq = test.GetSubsequence(2,5);
    for(int i=0;i<testSubSeq->GetLength();i++){
        assert(testSubSeq->Get(i)==subseq[i]);
    }
}

