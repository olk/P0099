class session
{
public:
    session(boost::asio::io_service& io_service) :
          socket_(io_service) // construct a TCP-socket from io_service
    {}

    tcp::socket& socket(){
        return socket_;
    }

    void start(){
        // initiate asynchronous read; handle_read() is callback-function
        socket_.async_read_some(boost::asio::buffer(data_,max_length),
            boost::bind(&session::handle_read,this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

private:
    void handle_read(const boost::system::error_code& error,
                     size_t bytes_transferred){
        if (!error)
            // initiate asynchronous write; handle_write() is callback-function
            boost::asio::async_write(socket_,
                boost::asio::buffer(data_,bytes_transferred),
                boost::bind(&session::handle_write,this,
                    boost::asio::placeholders::error));
        else
            delete this;
    }

    void handle_write(const boost::system::error_code& error){
        if (!error)
            // initiate asynchronous read; handle_read() is callback-function
            socket_.async_read_some(boost::asio::buffer(data_,max_length),
                boost::bind(&session::handle_read,this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        else
            delete this;
    }

    boost::asio::ip::tcp::socket socket_;
    enum { max_length=1024 };
    char data_[max_length];
};
