char resp_200[] = "HTTP/1.0 200 OK\r\n"
              "Server: webserver-c\r\n"
              "Content-type: text/html\r\n\r\n";
char resp_401[] = "HTTP/1.0 401 Unauthorized\r\n"
              "Server: webserver-c\r\n"
              "Content-type: text/html\r\n\r\n"
              "<html>ERROR 401</html>: Unauthorized\r\n";
char resp_404[] = "HTTP/1.0 404 Unauthorized\r\n"
              "Server: webserver-c\r\n"
              "Content-type: text/html\r\n\r\n"
              "<html>ERROR 404</html>: Resource Not Found\r\n";
char resp_405[] = "HTTP/1.0 405 Unsupported Method For Resource\r\n"
              "Server: webserver-c\r\n"
              "Content-type: text/html\r\n\r\n"
              "<html>ERROR 405</html>: Unsupported Method For Resource\r\n";