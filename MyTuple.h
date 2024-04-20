#pragma once


template <bool TypeBool,typename T = void>
struct Enable_If{};

template <typename T>
struct Enable_If<true,T>{
    using Type=T;
};

template <bool TypeBool,typename T = void>
using Enable_If_T= typename Enable_If<TypeBool,T>::Type;



template <size_t index,typename Type>
struct TuplePart{
    using type = Type;
    Type value;
    TuplePart(){};
    TuplePart(Type input):value(input){};
};

template <size_t index,typename... Others> //  специализация
struct Tuple{};

template <size_t index,typename First>
struct Tuple<index,First>:public TuplePart<index,First> {
    Tuple(First first):TuplePart<index,First>(first){};
    Tuple():TuplePart<index,First>(){};
};


template <size_t index,typename First,typename... Others>
struct Tuple<index,First,Others...>:public TuplePart<index,First> , public Tuple<index+1,Others...> {
    Tuple(First first,Others... others):TuplePart<index,First>(first),Tuple<index+1,Others...>( others...){};
    Tuple():TuplePart<index,First>(),Tuple<index+1,Others...>( ){};
};


template<size_t index, typename First, typename... Others>
First& Get(Tuple< index, First,  Others...>& tuple) {
    return tuple.TuplePart<index, First>::value; // можно сделать cast к нужной TuplePart
}

template <typename ... TypeForTuple> 
using Tuple_=Tuple<0,TypeForTuple...>;

template <size_t I = 0, typename... Tail> 
int MyTupleSize(Tuple_<Tail...> tup)//enable if создаёт тип при условии 
{
    return sizeof...(Tail);
}
// опора на SFINAE (Substitution failure is not an error)
template <size_t I = 0, typename... Tail> 
Enable_If_T<( I >= sizeof...(Tail) )> printTuple(Tuple_<Tail...> tup)//enable if создаёт тип при условии 
{
    return;
}

template <size_t I = 0, typename... Tail> 
Enable_If_T<( I < sizeof...(Tail) )>  printTuple(Tuple_<Tail...> tup)
{
    std::cout << Get<I>(tup) << " ";
    printTuple<I + 1>(tup);
}

