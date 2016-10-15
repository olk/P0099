std::execution_context<int> ctx1([](std::execution_context<int>&& ctx2,int j){
            std::cout << "inside ctx1,j==" << j << std::endl; // (b)
            std::tie(ctx2,j) = // (f)
                ctx2(j+1); // (c)
            return std::move(ctx2); // (g)
        });
int i=1;
std::tie(ctx1,i) = // (d)
    ctx1(i); // (a)
std::cout << "i==" << i << std::endl;

output:
    inside ctx1,j==1
    i==2
