std::coroutine<int>::pull_type c(
    [&](std::coroutine<int>::push_type& c){
        c(5); // return {5}
        c(7); // return {7}
        c(11); // return {11}
    });

for (;c;c())
    int ret=c.get();
