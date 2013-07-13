#include <coroutine>

template<class R>
class coroutine::pull_type
{
public:
    //construction
    pull_type();

    pull_type(pull_type&& other);

    template<class Function>
    explicit pull_type(Function&& fn);

    template<class Function,class StackAllocator>
    explicit pull_type(Function&& fn,const StackAllocator& salloc);

    pull_type(const pull_type& other)=delete;

    //destruction
    ~pull_type();

    // assignment
    pull_type& operator=(pull_type&& other);

    pull_type& operator=(const pull_type& other)=delete;

    // test
    explicit operator bool() const;

    // swap
    void swap(pull_type& other);

    // jump function
    pull_type& operator()();

    // access result
    R get() const;
};
