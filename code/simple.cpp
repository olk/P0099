// stackful execution_context
// access current execution context l1
auto l1=std::execution_context::current();
// create stackful execution context l2
auto l2=[&l1]()resumable(segmented()){
    std::printf("inside l2\n");
    // suspend l2 and resume l1
    l1();
}
// resume l2
l2();
