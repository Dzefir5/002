#pragma once

template<typename T>
void  MySwap(T& a,T& b){
    T buf = a;
    a=b;
    b=buf;
}