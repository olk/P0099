// N4134: stackless resumable function
generator<int> fib(int n){
    int a=0;
    int b=1;
    while(n-->0){
        yield a;
        auto next=a+b;
        a=b;
        b=next;
    }
}

int main(){
    for(auto v:fib(35)){
        std::cout<<v<<std::endl;
        if(v>10)break;
    }
}
