// N3985 stackful coroutine (boost:coroutine2)
// implemented with execution_context
typedef coroutine<int> coro_t;
int main(){
    int n=35;
    coro_t::pull_type fib([n](coro_t::push_type & yield){
            int a=0;
            int b=1;
            while(n-->0){
                yield(a);
                auto next=a+b;
                a=b;
                b=next;
            }
        });
    for(auto v:fib) {
        std::cout<<v<<std::endl;
        if(v>10)break;
    }
}
