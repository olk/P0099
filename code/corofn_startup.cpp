std::pull_coroutine<int> c(
    [&](std::push_coroutine<int> & c){
        c(5); // return {5}
        c(7); // return {7}
        c(11); // return {11}
    });

for (;c;c())
    int ret=c.get();
