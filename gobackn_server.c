#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define PORT 3033
#define WINDOW_SIZE 4
#define MAX_SEQ_NUM 10

void itoa(int number, char numberString[]) {
numberString[0] = (char)(number + 48);
numberString[1] = '\0';
}

int main() {
int sockfd, newSockFd, windowStart = 1, windowCurrent = 1, windowEnd;
char buffer[100];
socklen_t len;
struct sockaddr_in server, client;

sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
perror("Error opening socket");
exit(1);
}

server.sin_family = AF_INET;
server.sin_port = htons(PORT);
server.sin_addr.s_addr = INADDR_ANY;

if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
perror("Error in binding");
exit(1);
}

printf("Server started on port %d\n", PORT);
listen(sockfd, 1);
len = sizeof(client);

newSockFd = accept(sockfd, (struct sockaddr *)&client, &len);
if (newSockFd < 0) {
perror("Error in accepting connection");
exit(1);
}

printf("Received a request from client. Sending packets one by one...\n");
fcntl(newSockFd, F_SETFL, O_NONBLOCK);

windowEnd = windowStart + WINDOW_SIZE - 1;

do {
if (windowCurrent != windowEnd) {
itoa(windowCurrent, buffer);
send(newSockFd, buffer, 100, 0);
printf("\nPacket Sent: %d\n", windowCurrent);
windowCurrent++;
}

recv(newSockFd, buffer, 100, 0);

if (buffer[0] == 'R') {
printf("\nReceived a RETRANSMIT packet. Resending packet no. %c...", buffer[1]);
itoa(atoi(&buffer[1]), buffer);
send(newSockFd, buffer, 100, 0);
windowCurrent = atoi(&buffer[0]);
windowCurrent++;
} 
else if (buffer[0] == 'A') {
int oldWindowStart = windowStart;
windowStart = atoi(&buffer[1]) + 1;
windowEnd += (windowStart - oldWindowStart);
printf("\nReceived ACK %c. Moving window boundary.", buffer[1]);
}
} while (windowCurrent != 10);

close(sockfd);
close(newSockFd);
printf("\nSending Complete. Sockets closed. Exiting...\n");
return 0;
}
