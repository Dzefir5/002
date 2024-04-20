#pragma once
#include "ListSequence.h"
#include "ArraySequence.h"
#include "MyTuple.h"
#include "MapReduce.h"
#include <iostream>
#include <cassert>

#include "DynamicArrayTest.h"
#include "LinkedListTest.h"
#include "ArraySequenceTest.h"
#include "ListSequenceTest.h"
#include "TestMyTuple.h"
#include "TestMapReduce.h"



void Test_DynamicArray(){
    Test_DynamicArray_CompareOperator();
    Test_DynamicArray_Set();
    Test_DynamicArray_Constructors();
}

void Test_LinkedList(){
    Test_LinkedList_Append();
    Test_LinkedList_CompareOperator();
    Test_LinkedList_Prepend();
    Test_LinkedList_Concat();
    Test_LinkedList_Constructors();
    Test_LinkedList_Insert();
    Test_LinkedList_Set();
    Test_LinkedList_SubList();
    Test_LinkedList_Remove();

}

void Test_ArraySequence(){
    Test_ArraySequence_Constuctors();
    Test_ArraySequence_Append();
    Test_ArraySequence_RemoveAt();
    Test_ArraySequence_Prepend();
    Test_ArraySequence_InsertAt();
    Test_ArraySequence_Split();
    Test_ArraySequence_Slice();
    Test_ArraySequence_CompareOperator();
    Test_ArraySequence_AccessOperator();
    Test_ArraySequence_Concat();
    Test_ArraySequence_SubSequence();
}
void Test_ListSequence(){
    Test_ListSequence_Constuctors();
    Test_ListSequence_Append();
    Test_ListSequence_RemoveAt();
    Test_ListSequence_Prepend();
    Test_ListSequence_InsertAt();
    Test_ListSequence_Split();
    Test_ListSequence_Slice();
    Test_ListSequence_CompareOperator();
    Test_ListSequence_AccessOperator();
    Test_ListSequence_Concat();
    Test_ListSequence_SubSequence();
}

void Test_MapReduce(){
    Test_Map();
    Test_Where();
    Test_Reduce();
    Test_ZipUnzip();
}