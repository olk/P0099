std::execution_context<int> fn(std::execution_context<int> ctx, int data) {
    std::tie(ctx,data)=ctx(data+2);
    return ctx;
}

std::execution_context<int> ctx(fn);
int data=1;
std::tie(ctx,data)=ctx(data+2);
std::tie(ctx,data)=ctx(data+2);
