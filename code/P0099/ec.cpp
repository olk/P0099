class execution_context {
public:
    static execution_context current() noexcept;

    template<typename StackAlloc, typename Fn, typename ... Args>
    execution_context(std::allocator_arg_t, StackAlloc salloc,
                      Fn&& fn, Args&& ... args);

    template<typename Fn, typename ... Args>
    explicit execution_context(Fn&& fn, Args&& ... args);

    execution_context( execution_context const&)=default;
    execution_context( execution_context &&)=default;

    execution_context& operator=( execution_context const&)=default;
    execution_context& operator=( execution_context &)=default;

    void operator()() noexcept;
};
