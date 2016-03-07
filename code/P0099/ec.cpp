template<typename ... Args>
class execution_context {
public:
    execution_context() noexcept;

    template<typename Fn,
             typename ... Params,
             typename=detail::disable_overload<execution_context, Fn>
    >
    execution_context(Fn&& fn, Params&& ... params);

    template<typename StackAlloc,
             typename Fn,
             typename ... Params
    >
    execution_context(std::allocator_arg_t, StackAlloc salloc,
                      Fn&& fn, Params&& ... params);

    ~execution_context();

    execution_context(execution_context&& other) noexcept;

    execution_context&
    operator=(execution_context&& other) noexcept;

    execution_context(const execution_context& other) noexcept = delete;

    execution_context&
    operator=(const execution_context& other) noexcept = delete;

    std::tuple<execution_context, Args ...>
    operator()(Args ... args);

    template<typename Fn>
    std::tuple<execution_context, Args ...>
    operator()(exec_ontop_arg_t, Fn&& fn, Args ... args);

    explicit operator bool() const noexcept;

    bool operator!() const noexcept;

    bool operator==(const execution_context& other) const noexcept;

    bool operator!=(const execution_context& other) const noexcept;

    bool operator<(const execution_context& other) const noexcept;

    bool operator>(const execution_context& other) const noexcept;

    bool operator<=(const execution_context& other) const noexcept;

    bool operator>=(const execution_context& other) const noexcept;

    void swap(execution_context& other) noexcept;
};
