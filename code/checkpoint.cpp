std::checkpoint cp;
std::coroutine<int>::pull_type c(
    [&](std::coroutine<int>::push_type& c){
        int i = 0;
        c.set_checkpoint(cp,[&](){
            std::cout<<"ABC: ";
            while(true){
                c(++i);
        });
});

for(int x=0;x<3;++x){
   std::cout<<c().get()<<" ";
}
std::cout<<std::endl;

std::cout<<"rollback\n";
c.rollback(cp);

for(int x=0;x<3;++x){
   std::cout<<c().get()<<" ";
}
std::cout<<std::endl;

output:
ABC: 1 2 3
rollback
ABC: 1 2 3
