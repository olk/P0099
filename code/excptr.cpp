class my_context{
private:
    std::exception_ptr excptr_;
    std::execution_context ctx_;

public:
    my_context():
        excptr_(),
        ctx_(fixedsize_stack(),
             [&excptr_](){
                try {
                    ...
                } catch (...) {
                    excptr_ = std::current_exception();
                }
             })
    {}

    void run(){
        ctx_.resume();
        if(excptr_){
            std::rethrow_exception(excptr_);
        }
    }
};
