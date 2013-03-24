class coro_visitor : public visitor
{
private:
    // coroutine used to pass leaf node back to caller
    std::coroutine<void(leaf&)> & c_;

public:
    coro_visitor(std::coroutine<void(leaf&)> & c) :
        c_(c)
    {}

    void visit(branch & b){
        // traverse tree
        if (b.left) b.left->accept(*this);
        if (b.right) b.right->accept(*this);
    }

    void visit(leaf & l){
        // return leaf node to caller
        c_(l);
    }
};
