std::coroutine<std::tuple<int,int>>::pull_type source(
    [&](std::coroutine<std::tuple<int,int>>::push_type& sink){
        sink(std::make_tuple(7,11)); // return tuple {7,11}
    });

int x,y;
std::tie(x,y)=source.get();
