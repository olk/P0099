std::pull_coroutine<int> c(
    [&](std::push_coroutine<int>& c){
        int i = 0;
        c.checkpoint(1,[&](){
            std::cout<<"ABC"<<std::endl;
            while(true){
                c(++i);
        });
});

for(int x=0;x<3;++x){
   std::cout<<c().get()<<std::endl;
}

c.rollback(1);
