class X{
private:
    int* inp_;
    std::string outp_;
    std::exception_ptr excptr_;
    std::execution_context caller_;
    std::execution_context callee_;

public:
    X():
        inp_(nullptr),outp_(),excptr_(),
        caller_(std::execution_context::current()),
        callee_([=]()resumable(segmented(1024)){
                   try{
                       outp_=lexical_cast<std::string>(*inp_);
                       caller_(); // context switch to main()
                   }catch (...){
                       excptr_=std::current_exception();
                   }
                })
    {}

    std::string operator()(int i){
        inp_=&i;
        callee_(); // context switch for conversion
        if(excptr_){
            std::rethrow_exception(excptr_);
        }
        return outp_;
    }
};

int main(){
    X x;
    std::cout<<x(7)<<std::endl;
}
