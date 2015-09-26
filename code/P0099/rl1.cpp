// P0099: stackful execution context
std::execution_context l1=std::execution_context::current();
std::execution_context l2(
    std::allocator_arg,
    fixedsize(4048),
    [&l1](){
        ...
    });
std::execution_context l3(
    std::allocator_arg,
    protected_fixedsize(4048),
    [&l2](){
        ...
    });
