std::push_coroutine<std::tuple<int,int>> c(
    [&](std::pull_coroutine<std::tuple<int,int>> & c){
        // access tuple {7,11}; x==7 y==1
        int x,y;
        std::tie(x,y)=c.get();
    });

c(std::make_tuple(7,11));
