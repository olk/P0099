#include <coroutine>

template<class R>
class pull_coroutine
{
public:
    //construction
    pull_coroutine();

    pull_coroutine(pull_coroutine&& other);

    template<class Function>
    explicit pull_coroutine(Function&& fn,std::size_t ssize=min_ssize);

    template<class Function,class StackAllocator>
    explicit pull_coroutine(Function&& fn,const StackAllocator& salloc,
                            std::size_t ssize=min_ssize);

    pull_coroutine(const pull_coroutine& other)=delete;

    //destruction
    ~pull_coroutine();

    // assignment
    pull_coroutine& operator=(pull_coroutine&& other);

    pull_coroutine& operator=(const pull_coroutine& other)=delete;

    // test
    explicit operator bool() const;

    // swap
    void swap(pull_coroutine& other);

    // jump function
    pull_coroutine& operator()();

    // access result
    R get() const;
};
