// N4398: stackless execution context
int main(){
    std::execution_context* other=nullptr;
    auto ctx1=[other]()resumable{
        (* other)(); // suspend ctx1, resume other
    };
    auto ctx2=[&ctx1]()resumable{
        ctx1(); // suspend ctx2; resume ctx1
    };
    auto ctx3=[&ctx1,&ctx2]()resumable{
        ctx2(); // suspend ctx3, resume ctx2
        ctx1(); // suspend ctx3, resume ctx1
    };
    other=&ctx3;
    ctx3(); // suspend main context, resume ctx3
}
