int main() {
    // P0099: stackful execution context
    std::execution_context<void> l2(
        // l1 represents suspended context
        [](std::execution_context<void> l1){
            std::printf("inside l2\n");
            // resume context l1
            return l1;
        });
    // suspend current context (->l1)
    // resume context of l2
    l2();
    return 0;
}
