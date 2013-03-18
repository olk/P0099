#include <coroutine>

template<typename Signature>
class coroutine;

template<class R,class... Args>
class coroutine<R(Args...)>
{
public:
    //construction
    coroutine();

    coroutine(coroutine&& other);

    template<class Function>
    explicit coroutine(Function&& fn);

    template<class Function,class... Args>
    explicit coroutine(Function&& fn,Args&&... args);

    coroutine(const coroutine& other) = delete;

    //destruction
    ~coroutine();

    // assignment
    coroutine& operator=(coroutine&& other);

    coroutine& operator=(const coroutine& other) = delete;

    // test
    explicit operator bool() const;

    // swap
    void swap(coroutine& other);

    // jump function
    coroutine& operator()(Args&&... args);

    // access result
    R get() const;
};
