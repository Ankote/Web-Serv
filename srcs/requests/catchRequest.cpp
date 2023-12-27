#include "catchRequest.hpp"

size_t create_socket() 
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        cerr << "webserver (socket)" << errno << endl;
        exit(1);
    }
    cout << "socket created successfully" << endl;
    return sockfd;
}

size_t bind_socket(size_t sockfd, MAP &map)
{
    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) != 0)
    {
        cout << "webserver (bind)" <<endl;
        exit(1);
    }
    cout << ("socket successfully bound to address\n");
    
    listen_and_accept(sockfd, (struct sockaddr *)&host_addr,(socklen_t *)&host_addrlen, map);
    return (sockfd);
}

size_t listen_and_accept(size_t sockfd, struct sockaddr *host_addr,socklen_t * host_addrlen, MAP &map)
{
    if (listen(sockfd, SOMAXCONN) != 0)
    {
        cerr << ("webserver (listen)") << endl;
        return 1;
    }
    cout << ("server listening for connections\n");
    for (;;)
    {
        cout << "Waiting For incomming connections . . ." << endl;
        ssize_t client_sockfd = listen_to_cnx(sockfd, (struct sockaddr *)host_addr,
                                (socklen_t *)host_addrlen);
        if (client_sockfd > 0)
        {
            // cout << read_request (client_sockfd) << endl << endl << endl;
            parceRequest(read_request (client_sockfd), map);
            close(client_sockfd);
        }
    }
}

ssize_t listen_to_cnx(size_t sockfd, struct sockaddr *host_addr,socklen_t * host_addrlen)
{
    static int cpt;
    int newsockfd = accept(sockfd, (struct sockaddr *)host_addr,
                        (socklen_t *)host_addrlen);
    if (newsockfd < 0)
    {
        cerr << " \033[0;31mConnection inacceptable!\033[0m" << endl;
        return (-1);
    }
    cout << ("\033[0;32mconnection accepted ") << ++cpt << " times.\033[0m" << endl;
    return (newsockfd);
}

string read_request(size_t cl_sockfd)
{
    char buffer[BUFFER_SIZE];
    string request;
    int readbytes = read(cl_sockfd, buffer, BUFFER_SIZE);
    if (readbytes < 0)
    {
        cout << ("webserver (read)") << endl;
        return (NULL);
    }
    buffer[readbytes] = '\0';
    request = buffer;
    return request;
}