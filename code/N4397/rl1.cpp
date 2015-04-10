// N4397: stackful execution context
std::execution_context l1=std::execution_context::current();
auto l2=[&l1]()resumable(fixedsize(1024)){
    ...
};
auto l3=[&l2]()resumable(segmented(1024)){
    ...
};
