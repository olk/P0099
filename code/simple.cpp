int main() {
    std::execution_context<void> ctx1(
        [](std::execution_context<void>&& ctx2){ // (b)
            return std::move(ctx2); // (c)
        });
    ctx1(); // (a)
    return 0;
}
