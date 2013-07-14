#include <coroutine>

template<class Arg>
class coroutine::push_type
{
public:
    //construction
    push_type();

    push_type(push_type&& other);

    template<class Function>
    explicit push_type(Function&& fn);

    push_type(const push_type& other)=delete;

    //destruction
    ~push_type();

    // assignment
    push_type& operator=(push_type&& other);

    push_type& operator=(const push_type& other)=delete;

    // test
    explicit operator bool() const;

    // swap
    void swap(push_type& other);

    // jump function
    push_type& operator()(Arg&& arg);
};
