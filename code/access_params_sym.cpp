std::symmetric_coroutine<std::tuple<int,int>>::call_type call(
    [&](std::symmetric_coroutine<std::tuple<int,int>>::yield_type& yield){
        // access tuple {7,11}; x==7 y==1
        int x,y;
        std::tie(x,y)=yield.get();
    });

call(std::make_tuple(7,11));
