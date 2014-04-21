// constructor does NOT enter coroutine-function
std::symmetric_coroutine<int>::call_type coro(
    [&](std::symmetric_coroutine<int>::yield_type& yield){
        for (;;) {
            std::cout << yield.get() <<  " ";
            yield(); // jump back to starting context
         }
    });

coro(1); // transfer {1} to coroutine-function
coro(2); // transfer {2} to coroutine-function
coro(3); // transfer {3} to coroutine-function
coro(4); // transfer {4} to coroutine-function
coro(5); // transfer {5} to coroutine-function
