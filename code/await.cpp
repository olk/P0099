int bar(int i){
    // await is not limited by "one level" as in C#
    auto result=await async([i]{ return reschedule(),i*100; });
    return result+i*10;
}

int foo(int i){
    cout << i << ":\tbegin" << endl;
    cout << await async([i]{ return reschedule(),i*10; }) << ":\tbody" << endl;
    cout << bar(i) << ":\tend" << endl;
    return i*1000;
}

void async_user_handler(){
    vector<future<int>> fs;

    // instead of `async` at function signature, `asynchronous` should be
    // used at the call place:
    for(auto i=0;i!=5;++i)
        fs.push_back(asynchronous([i]{ return foo(i+1); }));

    for(auto&& f:fs)
        cout << await f << ":\tafter end" << endl;
}
