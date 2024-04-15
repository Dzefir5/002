class A{
public:
    double value;
};
class B:public A{
public:
    int value;
    void f(){
        (*this).A::value;
    }
};

template <size_t index,typename Type>
struct TuplePart{
    Type value;
    TuplePart(){};
    TuplePart(Type input):value(input){};
};

template <size_t index,typename... Others> //  специализация
struct Tuple{};

//template <size_t index>
//struct Tuple<index>{};

template <size_t index,typename First,typename... Others>
struct Tuple<index,First,Others...>:public TuplePart<index,First> , public Tuple<index+1,Others...> {
    Tuple(First first,Others... others):TuplePart<index,First>(first),Tuple<index+1,Others...>( others...){};
    Tuple():TuplePart<index,First>(),Tuple<index+1,Others...>( ){};
};

template <size_t index,typename First>
struct Tuple<index,First>:public TuplePart<index,First> {
    Tuple(First first):TuplePart<index,First>(first){};
    Tuple():TuplePart<index,First>(){};
};


template<size_t index, typename First, typename... Others>
First& Get(Tuple< index, First,  Others...>& tuple) {
    return tuple.TuplePart<index, First>::value; // можно сделать cast к нужной TuplePart
}

template<typename... Items>
using Tuple_ = Tuple<0, Items...>;
