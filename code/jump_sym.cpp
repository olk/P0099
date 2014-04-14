boost::coroutines::symmetric_coroutine<int>::call_type coro_a(
    [&](boost::coroutines::symmetric_coroutine<int>::yield_type& yield){
            std::cout << yield.get() <<  "\n";
            yield(); // jump back to starting context
            std::cout << yield.get() <<  "\n";
            std::cout << "coro_a finished" << std::endl;
    });

coro_a(3); // start coro_a with parameter 3

boost::coroutines::symmetric_coroutine<std::string>::call_type coro_b(
    [&](boost::coroutines::symmetric_coroutine<std::string>::yield_type& yield){
            std::cout << yield.get() <<  "\n";
            yield( coro_a, 7); // resume coro_a with parameter 7
            std::cout << "coro_b finished" << std::endl;
    });

coro_b("abc"); // start coro_b with parameter "abc"
std::cout << "Done" << std::endl;

output:
3
abc
7
coro_a finished
coro_b finished
Done
