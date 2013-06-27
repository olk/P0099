node::ptr_t create_tree1(){
    return branch::create(
        leaf::create("a"),
        branch::create(
            leaf::create("b"),
            leaf::create("c")));
}

node::ptr_t create_tree2(){
    return branch::create(
        branch::create(
            leaf::create("a"),
            leaf::create("b")),
        leaf::create("c"));
}

int main() {
    // create tree t1
    node::ptr_t t1=create_tree1();
    // create a coroutine, recursivly iterates trough t1
    // returning leaf nodes
    std::pull_coroutine<leaf&> c1(
        [&](std::push_coroutine<leaf&> & c){
            // create visitor, attached to coroutine
            coro_visitor v(c);
            // traverse t1 recursivly
            t1->accept(v);
        });

    // create tree t2
    node::ptr_t t2=create_tree2();
    // create a coroutine, recursivly iterates trough t2
    // returning leaf nodes
    std::pull_coroutine<leaf&> c2(
        [&](std::push_coroutine<leaf&> & c){
            // create visitor, attached to coroutine
            coro_visitor v(c);
            // traverse t2 recursivly
            t2->accept(v);
        });

    // compare leaf node ranges of t1 and t2
    bool result = std::equal(
            std::begin(c1),
            std::end(c1),
            std::begin(c2));

    std::cout << std::boolalpha << "same fringe == " << result;
    std::cout << "\nDone" << std::endl;

    return EXIT_SUCCESS;
}
