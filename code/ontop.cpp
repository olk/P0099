// f1() is the toplevel context function:
// it returns only std::execution_context<args...>
std::execution_context<int> f1(std::execution_context<int> ctx,int data) {
    std::cout << "f1: entered first time: " << data << std::endl; // (b)
    std::tie(ctx,data) = // (g)
        ctx(data+1); // (c)
    std::cout << "f1: entered second time: " << data << std::endl; // (h)
    std::tie(ctx,data) = // (o)
        ctx(data+1); // (i)
    std::cout << "f1: entered third time: " << data << std::endl; // (p)
    return std::move(ctx); // (q)
}

// f2() is an invoke_ontop_arg function:
// though its parameter list is very like that of a toplevel context function,
// it must return std::tuple<std::execution_context<args...>, args...>
std::tuple<std::execution_context<int>,int>
f2(std::execution_context<int> ctx,int data) {
    std::cout << "f2: entered: " << data << std::endl; // (m)
    return std::make_tuple(std::move(ctx),-1); // (n)
}

int data=0;
ctx::execution_context< int > ctx(f1);
std::tie(ctx,data) = // (d)
    ctx(data+1); // (a)
std::cout << "f1: returned first time: " << data << std::endl; // (e)
std::tie(ctx,data) = // (j)
    ctx(data+1); // (f)
std::cout << "f1: returned second time: " << data << std::endl; // (k)
std::tie(ctx,data) = // (r)
    ctx(std::invoke_ontop_arg,f2,data+1); // (l)

output:
    f1: entered first time: 1
    f1: returned first time: 2
    f1: entered second time: 3
    f1: returned second time: 4
    f2: entered: 5
    f1: entered third time: -1
