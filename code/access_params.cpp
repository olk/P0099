std::coroutine<std::tuple<int,int>>::push_type sink(
    [&](std::coroutine<std::tuple<int,int>>::pull_type& source){
        // access tuple {7,11}; x==7 y==1
        int x,y;
        std::tie(x,y)=source.get();
    });

sink(std::make_tuple(7,11));
