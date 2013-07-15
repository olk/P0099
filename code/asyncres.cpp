void echo(boost::asio::ip::tcp::socket& socket,boost::asio::yield_context yield){
    char data[128];
    // read asynchronous data from socket
    // execution context will be suspended until
    // some bytes are read from socket
    std::size_t n=socket.async_read_some(boost::asio::buffer(data),yield);
    // write some bytes asynchronously
    boost::asio::async_write(socket,boost::asio::buffer(data,n),yield);
}
