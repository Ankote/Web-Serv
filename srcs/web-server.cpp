#include "web-server.hpp"
#define BUFFER_SIZE 1024

char* webPage(const std::string &file) {
    std::string buffer;
    std::string content;
    std::ifstream fileObj(file.c_str());
    
    if (fileObj.is_open()) {
        while (getline(fileObj, buffer)) {
            content += buffer;
            content += "\n";
        }
    } else {
        std::cerr << "ERROR! can't open file : " << file << std::endl;
        _exit(1);
    }

    char* s = new char[content.size() + 1];
    std::strcpy(s, content.c_str());
    return s;
}

int main() {
    // Create a socket
    char buffer[BUFFER_SIZE];
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    string str = webPage("moon.jpg");
    string resp = "HTTP/1.0 200 OK\r\n"
    "Server: webserver-c\r\n"
    "Content-type: image/jpeg\r\n\r\n"
    + str;
    if (sockfd == -1) {
        cerr << "webserver (socket)" << endl;
        return 1;
    }
    cout << "socket created successfully" << endl;

    // Create the address to bind the socket to
    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the address
    if (bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) != 0) {
        cerr << ("webserver (bind)") << endl;
        return 1;
    }
    cout << ("socket successfully bound to address") << endl;

    // Listen for incoming connections
    if (listen(sockfd, SOMAXCONN) != 0) {
        cerr << ("webserver (listen)") << endl;
        return 1;
    }
    cout << ("server listening for connections\n");
    size_t cpt = 0;
    for (;;) {
        // Accept incoming connections
        int newsockfd = accept(sockfd, (struct sockaddr *)&host_addr,
                               (socklen_t *)&host_addrlen);
        if (newsockfd < 0) {
            cerr << ("webserver (accept)") << endl;
            continue;
        }
        cout << ("\033[0;32mconnection accepted ") << ++cpt << " times.\033[0m" << endl;
        // Read from the socket
        int valread = read(newsockfd, buffer, BUFFER_SIZE);
        if (valread < 0) {
            cerr << ("webserver (read)") << endl;
            continue;
        }
        int valwrite = write(newsockfd, resp.c_str(), strlen(resp.c_str()));
        if (valwrite < 0) {
            perror("webserver (write)");
            continue;
        }

        cout << buffer << endl;
        if (cpt == 10)
            _exit(0);
        close(newsockfd);
    }

    return 0;
}