#pragma once
#include "MyTuple.h"
#include <cassert>

void Test_MyTuple(){
    Tuple_<> emptyTuple;
    Tuple_<int,char,double> testTuple(1,'a',5.5);
    assert(Get<0>(testTuple)==1);
    assert(Get<1>(testTuple)=='a');
    assert(Get<2>(testTuple)==5.5);
}