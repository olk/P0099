std::execution_context<int,int> ctx1(
        [](std::execution_context<int,int>&& ctx2,int i,int j){
            std::cout << "inside ctx1,i==" << i << " j==" << j << std::endl;
            std::tie(ctx2,i,j)=ctx2(i+j,i-j);
            return std::move(ctx2);
        });
int i=3,j=2;
std::tie(ctx1,i,j)=ctx1(i,j);
std::cout << "i==" << i << " j==" << j << std::endl;

output:
    inside ctx1,i==3 j==2
    i==5 j==1
