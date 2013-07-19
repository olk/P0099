std::coroutine<int>::pull_type c( // constructor enters coroutine-function
    [&](std::coroutine<int>::push_type& c){
        c(1); // push {1} back to main-context
        c(1); // push {1} back to main-context
        c(2); // push {2} back to main-context
        c(3); // push {3} back to main-context
        c(5); // push {5} back to main-context
        c(8); // push {8} back to main-context
    });

while(c){            // test if pull-coroutine is valid
    int ret=c.get(); // access data value
    c();             // context-switch to coroutine-function
}
