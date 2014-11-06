/*
 * grammar:
 *   P ---> E '\0'
 *   E ---> T {('+'|'-') T}
 *   T ---> S {('*'|'/') S}
 *   S ---> digit | '(' E ')'
 */
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
      level(0), next(), is(is_), cb(cb_)
    {}

   void run() {
      scan();
      E();
      if (next!='\0'){
          exit(1);
      }
   }

private:
   void E(){
      T();
      while (next=='+'||next=='-'){
         cb(next); 
         scan();
         T();
      }
   }

   void T(){
      S();
      while (next=='*'||next=='/'){
         cb(next); 
         scan();
         S();
      }
   }

   void S(){
      if (isdigit(next)){
         cb(next);
         scan();
      }
      else if(next=='('){
         cb(next); 
         scan();
         E();
         if (next==')'){
             cb(next); 
             scan();
         }else{
             exit(2);
         }
      }
      else{
         exit(3);
      }
   }
};

void parse(istream& is) {
	Parser p(is,[](char ch){ yield ch; });
        p.run();
}

void main() {
    istringstream is("1+1");
    // invert control flow
    auto seq = await stackfull[segmented(64*1024)] parse(is);
    // user-code pulls parsed data from parser
    for(char c: seq){
        printf("Parsed: %c\n",c);
    }
}
