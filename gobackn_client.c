#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 3033

int main() {
int sockfd, size, firstTime = 1, currentPacket, wait = 3;
char data[100], digit[2];
struct sockaddr_in client;

sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
perror("Error creating socket");
exit(1);
}

client.sin_family = AF_INET;
client.sin_port = htons(PORT);
client.sin_addr.s_addr = INADDR_ANY;

printf("\nStarting up...");
size = sizeof(client);
printf("\nEstablishing Connection to Server...");

if (connect(sockfd, (struct sockaddr *)&client, size) < 0) {
perror("Connection failed");
exit(1);
}

sprintf(data, "REQUEST");
send(sockfd, data, strlen(data), 0);

do {
recv(sockfd, data, 100, 0);
currentPacket = atoi(data);
printf("\nGot packet: %d", currentPacket);

if (currentPacket == 3 && firstTime) {
printf("\n*** Simulation: Packet data corrupted/incomplete. ***");
printf("\nSending RETRANSMIT for packet 1");
memset(data, 0, sizeof(data));
sprintf(data, "R1");
send(sockfd, data, strlen(data), 0);
firstTime = 0;
} else {
memset(data, 0, sizeof(data));
sprintf(data, "A%d", currentPacket);
send(sockfd, data, strlen(data), 0);
printf("\nACK Sent for packet: %d", currentPacket);
}
} while (currentPacket != 10);

close(sockfd);
printf("\nReceiving Complete. Socket closed. Exiting...\n");
return 0;
}
