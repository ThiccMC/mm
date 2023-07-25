#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define MAX_CLIENTS 10
#define SOCKET_PATH "./lo.sock"
#define STATIC_BUFFER_SIZE 1024

int main() {
    int sv, cl[MAX_CLIENTS];
    struct sockaddr_un addr;
    char buf[STATIC_BUFFER_SIZE];
    int num_clients = 0;
    // create sock
    sv = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sv == -1) {
        perror("socket");
        exit(1);
    }
    // set
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
    // bind
    if (bind(sv, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        exit(1);
    }
    // listen
    if (listen(sv, MAX_CLIENTS) == -1) {
        perror("listen");
        exit(1);
    }
    printf("bind %s\n", SOCKET_PATH);
    while (1) {
        fd_set read_fds;
        int max_fd = sv;

        // wtf
        FD_ZERO(&read_fds);
        FD_SET(sv, &read_fds);
        for (int i = 0; i < num_clients; i++) {
            FD_SET(cl[i], &read_fds);
            if (cl[i] > max_fd) {
                max_fd = cl[i];
            }
        }

        // patience
        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(1);
        }

        // more seeders
        if (FD_ISSET(sv, &read_fds)) {
            int client_fd = accept(sv, NULL, NULL);
            if (client_fd == -1) {
                perror("accept");
                continue;
            }
            printf("New connection\n");
            cl[num_clients++] = client_fd;
        }

        // consume
        for (int i = 0; i < num_clients; i++) {
            if (FD_ISSET(cl[i], &read_fds)) {
                ssize_t num_bytes = read(cl[i], buf, sizeof(buf));
                if (num_bytes <= 0) {
                    printf("Client disconnected\n");
                    close(cl[i]);
                    memmove(&cl[i], &cl[i + 1], num_clients - i - 1);
                    num_clients--;
                    i--;
                } else {
                    // throw
                    for (int j = 0; j < num_clients; j++) {
                        if (j != i) {
                            write(cl[j], buf, num_bytes);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

