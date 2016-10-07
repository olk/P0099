std::execution_context<int> f1(std::execution_context<int> && ctx,int data) {
    std::cout << "f1: entered first time: " << data << std::endl;
    std::tie(ctx,data)=ctx(data+1);
    std::cout << "f1: entered second time: " << data << std::endl;
    std::tie(ctx,data)=ctx(data+1);
    std::cout << "f1: entered third time: " << data << std::endl;
    return std::move(ctx);
}

std::tuple<std::execution_context<int>,int> f2(std::execution_context<int> && ctx,int data) {
    std::cout << "f2: entered: " << data << std::endl;
    return std::make_tuple(std::move(ctx),-1);
}

int data=0;
ctx::execution_context< int > ctx(f1);
std::tie(ctx,data)=ctx(data+1);
std::cout << "f1: returned first time: " << data << std::endl;
std::tie(ctx,data)=ctx(data+1);
std::cout << "f1: returned second time: " << data << std::endl;
std::tie(ctx,data)=ctx(std::invoke_ontop_arg,f2,data+1);

output:
    f1: entered first time: 1
    f1: returned first time: 2
    f1: entered second time: 3
    f1: returned second time: 4
    f2: entered: 5
    f1: entered third time: -1
