#pragma once

template <typename T>
T MyAbs(T input){
    if(input<0){
        return (-1)*input;
    }
    return input;
}