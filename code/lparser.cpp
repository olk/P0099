// class Parser omitted
int main() {
    std::istringstream is("1+1");
    bool done=false;
    char c;
    // create resumable lambda from current execution context
    auto ml=std::current_context();
    // create resumable lambda using an stack
    // which grows on demand and with an initial size of 1KB
    auto pl=[&is,&ml,&done,&c]()resumable(segmented(1024)){
            Parser p(is,
                     // create/pass callback, invoked by the parser
                     [&ml,&c](char ch){
                        c=ch;
                        // resume main-context
                        ml();
                     });
            p.run();
            done=true;
        });
    // inversion of control: user-code pulls parsed data from parser
    while(!done){
        // resume parser-context
        pl();
        printf("Parsed: %c\n",c);
    }
}
