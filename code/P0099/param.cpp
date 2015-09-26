// P0099: stackful execution context
class X{
private:
    int* inp_;
    std::string outp_;
    std::execution_context caller_;
    std::execution_context callee_;

public:
    X():
        inp_(nullptr),outp_(),
        caller_(std::execution_context::current()),
        callee_(fixedsize(),
                [=](){
                       outp_=lexical_cast<std::string>(*inp_);
                       caller_(); // context switch to main()
                })
    {}

    std::string operator()(int i){
        inp_=&i;
        callee_(); // context switch to coroutine (lambda)
        return outp_;
    }
};

int main(){
    X x;
    try{
        std::cout<<x(7)<<std::endl;
    }catch(const std::exception& e){
        std::cout<<"exception: "<<e.what()<<std::endl;
    }
}
