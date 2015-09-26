// N4402: stackless resumable function
generator<void> f1(){
    yield; // suspend f1
}
generator<void> f2(){
    yield; // suspend f2
}
int main(){
    f1(); // resume f1
    f2(); // resume f2
}
