#include <coroutine>

template<class Arg>
class push_coroutine
{
public:
    //construction
    push_coroutine();

    push_coroutine(push_coroutine&& other);

    template<class Function>
    explicit push_coroutine(Function&& fn,std::size_t ssize=min_ssize);

    template<class Function,class StackAllocator>
    explicit push_coroutine(Function&& fn,const StackAllocator& salloc,
                            std::size_t ssize=min_ssize);

    push_coroutine(const push_coroutine& other)=delete;

    //destruction
    ~push_coroutine();

    // assignment
    push_coroutine& operator=(push_coroutine&& other);

    push_coroutine& operator=(const push_coroutine& other)=delete;

    // test
    explicit operator bool() const;

    // swap
    void swap(push_coroutine& other);

    // jump function
    push_coroutine& operator()(Arg&& arg);
};
