template< typename T >
class pull_coroutine {
private:
    template< typename X >
    friend class push_coroutine;

    std::execution_context   caller_;
    std::execution_context   callee_;
    int                      state_;
    std::exception_ptr       except_;
    T                    **  t_;

    pull_coroutine( synthesized_t,
                    std::execution_context const& caller,
                    std::execution_context const& callee,
                    T ** t) :
        caller_( caller),
        callee_( callee),
        state_( 0),
        except_(),
        t_( t) {
    }

public:
    template< typename StackAllocator, typename Fn >
    pull_coroutine( StackAllocator salloc, Fn && fn_) :
        caller_( std::execution_context::current() ),
        callee_( salloc,
                 [=,&fn_](){
                    // create synthesized push_coroutine< void >
                    push_coroutine< T > push_coro( synthesized, callee_, caller_, & t_);
                    try {
                        // store coroutine-fn
                        Fn fn( std::forward< Fn >( fn_) );
                        // call coroutine-fn with synthesized pull_coroutine as argument
                        fn( push_coro);
                    } catch ( forced_unwind const&) {
                        // do nothing for unwinding exception
                    } catch (...) {
                        // store other exceptions in exception-pointer
                        except_ = std::current_exception();
                    }
                    // set termination flags
                    state_ |= static_cast< int >( state_t::complete);
                    // jump back to caller
                    caller_.jump_to();
                    assert( false);
                }),
        state_( static_cast< int >( state_t::unwind) ),
        except_(),
        t_( nullptr) {
        callee_.jump_to();
    }

    pull_coroutine( pull_coroutine const&) = delete;
    pull_coroutine & operator=( pull_coroutine const&) = delete;

    void operator()() {
        callee_.jump_to();
        if ( except_) {
            std::rethrow_exception( except_);
        }
    }

    explicit operator bool() const noexcept {
        return nullptr != t_ && 0 == ( state_ & static_cast< int >( state_t::complete) );
    }

    bool operator!() const noexcept {
        return nullptr == t_ || 0 != ( state_ & static_cast< int >( state_t::complete) );
    }

    T get() const noexcept {
        return ** t_;
    }
};

template< typename T >
struct coroutine {
    typedef pull_coroutine< T >     pull_type;
    typedef push_coroutine< T >     push_type;
};
