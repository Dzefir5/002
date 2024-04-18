#pragma once
#include "MyTuple.h"
#include "MapReduce.h"
#include <cassert>

int testFuncMap(int i){
    return 5*i;
}
bool testFuncWhere(int i){
    return i%2==0;
}
int testFuncReduce(int a,int b ){
    return a+b;
}

void Test_Where(){
    int a[4]={1,2,3,4};
    int b[]={2,4};
    MutableListSequence<int> testWhere(a,4);
    MutableArraySequence<int> whereResult = where(testWhere,&testFuncWhere);
    for(int i=0;i<whereResult.GetLength();i++){
        assert ( whereResult.Get(i)==b[i]  );
    }
}
void Test_Map(){
    int a[]={1,2,3,4};
    int b[]={5,10,15,20};
    MutableListSequence<int> testMap(a,4);
    MutableArraySequence<int> mapResult = map(testMap,&testFuncMap);
    for(int i=0;i<mapResult.GetLength();i++){
        assert ( mapResult.Get(i)==b[i]  );
    }
}
void Test_Reduce(){
    int a[]={1,2,3,4};
    int res=10;
    MutableListSequence<int> testReduce(a,4);
    int start =0;
    int result = reduce(testReduce,&testFuncReduce,start);
    assert(result==res);
}

void Test_ZipUnzip(){
    int a[]={1,2,3,4};
    char b[]={'a','b','c','d','e'};
    double c[] = { 2.3, 5.6, 9.6};
    Tuple_<int,char,double> res[3] = {
        {1,'a',2.3},
        {2,'b',5.6},
        {3,'c',9.6}
    };

    MutableArraySequence<int> test_1(a,4);
    MutableArraySequence<char> test_2(b,5);
    MutableArraySequence<double> test_3(c,3);
    auto testZip =  zip<int,char,double>(test_1,test_2,test_3) ;
    for(int i =0; i<testZip.GetLength();i++){
        assert( Get<0>(res[i])==Get<0>(testZip[i]) ); 
        assert( Get<1>(res[i])==Get<1>(testZip[i]) ); 
        assert( Get<2>(res[i])==Get<2>(testZip[i]) ); 
    }
    auto testUnzip = unzip(testZip);
    for(int i=0;i<Get<0>(testUnzip)->GetLength();i++){
        assert( Get<0>(testUnzip)->Get(i)==a[i] ); 
    }
    for(int i=0;i<Get<1>(testUnzip)->GetLength();i++){
        assert( Get<1>(testUnzip)->Get(i)==b[i] ); 
    }
    for(int i=0;i<Get<2>(testUnzip)->GetLength();i++){
        assert( Get<2>(testUnzip)->Get(i)==c[i] ); 
    }
   

}