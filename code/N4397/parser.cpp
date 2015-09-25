// P0099: stackful execution context
// grammar:
//   P ---> E '\0'
//   E ---> T {('+'|'-') T}
//   T ---> S {('*'|'/') S}
//   S ---> digit | '(' E ')'
class Parser{
   int level;
   char next;
   istream& is;
   function<void(char)> cb;

   char pull(){
        return char_traits<char>::to_char_type(is.get());
   }

   void scan(){
       do{
           next=pull();
       }
       while(isspace(next));
   }

public:
   Parser(istream& is_,function<void(char)> cb_) :
      level(0),next(),is(is_),cb(cb_)
    {}

   void run() {
      scan();
      E();
   }

private:
   void E(){
      T();
      while (next=='+'||next=='-'){
         cb(next); // callback; signal new symbol
         scan();
         T();
      }
   }

   void T(){
      S();
      while (next=='*'||next=='/'){
         cb(next); // callback; signal new symbol
         scan();
         S();
      }
   }

   void S(){
      if (isdigit(next)){
         cb(next); // callback; signal new symbol
         scan();
      }
      else if(next=='('){
         cb(next); // callback; signal new symbol
         scan();
         E();
         if (next==')'){
             cb(next); // callback; signal new symbol
             scan();
         }else{
             throw std::runtime_error("parsing failed");
         }
      }
      else{
          throw std::runtime_error("parsing failed");
      }
   }
};

int main(){
    std::istringstream is("1+1");
    char c;
    // access current execution context
    auto m=std::execution_context::current();
    std::execution_context l(
        [&is,&m,&c](){
            Parser p(is,
                     // callback, used to signal new symbol
                     [&m,&c](char ch){
                        c=ch;
                        m(); // resume main-context
                     });
            p.run(); // start parsing
        });
    try{
        // inversion of control: user-code pulls parsed symbols from parser
        while(l()){
            std::cout<<"Parsed: "<<c<<std::endl;
        }
    }catch(const std::exception& e){
        std::cerr<<"exception: "<<e.what()<<std::endl;
    }
}
