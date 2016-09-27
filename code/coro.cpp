void read_msg(yield_context yield) {
    try {
        array< char, 64 > bf1;
        async_read(socket,buffer(b1),yield);
        header hdr(bf1);
        std::size_t n=hdr.payload_size();
        std::vector< char > b2(n,'\0');
        async_read(socket,buffer(bf2),yield);
        payload pld(bf2);
        // process message ...
    } catch (exception const&) {
        // ...
    }
}
