// P0099: stackful execution context
int main(){
    auto mctx(std::execution_context::current());
    std::execution_context ctx1([&mctx]()mutable{
            mctx(); // suspend ctx1, resume mctx
        });
    std::execution_context ctx2([&ctx1]()mutable{
            ctx1(); // suspend ctx2, resume ctx1
        });
    ctx2(); // suspend main-context mctx, resume ctx2
}
