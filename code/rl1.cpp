// execution_context constructed out of resumable lambda
std::execution_context l1=[]()resumable(fixedsize(1024)){
    ...
};
// using auto
auto l2=[&l1]()resumable(segmented(1024)){
    ...
    l1(); // resume l1
    ...
};
