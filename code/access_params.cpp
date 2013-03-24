std::coroutine<void(int,int)> c(
    [&](std::coroutine<std::tuple<int,int>()> & c){
        // access tuple {7,11}; x==7 y==1
        int x,y;
        std::tie(x,y)=c.get();
    });

c(7,11);
