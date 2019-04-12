#include <stdio.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8002
#define NUMBER_OF_STRING 4
#define MAX_STRING_SIZE 40

void print_array(const char arr[NUMBER_OF_STRING][MAX_STRING_SIZE])
{
    for (int i = 0; i < NUMBER_OF_STRING; i++)
    {
        printf("'%s' has length %d\n", arr[i], strlen(arr[i]));
    }
}
int main()
{
    struct sockaddr_in address;
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char *hello = "Hello from client";
        char buffer[2224] = {0};
        int buffer2[3] = {0};
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        memset(&serv_addr, '0', sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }
        send(sock , hello , strlen(hello) , 0 );
        printf("Hello message sent\n");
        valread = read( sock , buffer, 2224);
        printf("%s\n",buffer );
        print_array(buffer);
        return 0;
}
