void read_msg() {
    try {
        array< char, 64 > bf1;
        async_read(socket,buffer(b1),boost::fibers::asio::yield);
        header hdr(bf1);
        std::size_t n=hdr.payload_size();
        std::vector< char > b2(n,'\0');
        async_read(socket,buffer(bf2),boost::fibers::asio::yield);
        payload pld(bf2);
        // process message ...
    } catch (exception const&) {
        // ...
    }
}
