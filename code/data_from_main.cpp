std::asymmetric_coroutine<int>::push_type sink( // constructor does NOT enter coroutine-function
    [&](std::asymmetric_coroutine<int>::pull_type& source){
        for (int i:source){
            std::cout << i <<  " ";
        }
    });

std::vector<int> v{1,1,2,3,5,8,13,21,34,55};
for(int i:v){
    sink(i); // push {i} to coroutine-function
}
