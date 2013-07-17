std::coroutine<int>::pull_type c(
    [&](std::coroutine<int>::push_type& c){
        int first=1,second=1;
        c(first);
        c(second);
        for(int i=0;i<8;++i){
            int third=first+second;
            first=second;
            second=third;
            c(third);
        }
    });

for(auto i:c)
    std::cout << i <<  " ";

std::cout << "\nDone" << std::endl;

output:
1 1 2 3 5 8 13 21 34 55
Done
