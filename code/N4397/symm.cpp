// N4397: stackful execution context
int main(){
    auto mctx(std::execution_context::current());
    auto ctx1=[&mctx]()mutable resumable(fixedsize()){
            mctx(); // suspend ctx1, resume mctx
        };
    auto ctx2=[&ctx1]()mutable resumable(fixedsize()){
            ctx1(); // suspend ctx2, resume ctx1
        };
    ctx2(); // suspend main-context mctx, resume ctx2
}
