// N4397: stackful execution context
std::execution_context l1=[]()resumable(fixedsize(1024)){
    ...
};
auto l2=[&l1]()resumable(segmented(1024)){
    ...
};
