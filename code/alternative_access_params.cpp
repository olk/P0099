std::coroutine<void(std::tuple<int,int>)> c(
    [&](std::coroutine<std::tuple<int,int>()> & c){
        // access tuple {7,11}; x==7 y==1
        int x,y;
        std::tie(x,y)=c.get();
    },
    std::make_tuple(7,11)); // tuple passed as argument; coroutine-fn entered
