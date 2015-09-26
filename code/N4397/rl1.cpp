// P0099: stackful execution context
std::execution_context l1=std::execution_context::current();
std::execution_context l2([&l1](){
    ...
});
std::execution_context l3([&l2](){
    ...
});
