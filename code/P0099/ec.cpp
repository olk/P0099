class execution_context {
public:
    static execution_context current() noexcept;

    template<typename StackAlloc, typename Fn, typename ... Args>
    explicit execution_context(StackAlloc salloc, Fn&& fn, Args&& ... args);

    execution_context( execution_context const&)=default;
    execution_context( execution_context &&)=default;

    execution_context& operator=( execution_context const&)=default;
    execution_context& operator=( execution_context &)=default;

    void operator()() noexcept;
};
