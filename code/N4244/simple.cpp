// N4244: stackless resumable lambda
int i=7;
// create stackless resumable lambda l
auto l=[j=i]()resumable{
    std::printf("inside l: %d\n", j);
    // suspend l and jump back to resumption point
    yield;
}
// resume l
l();
