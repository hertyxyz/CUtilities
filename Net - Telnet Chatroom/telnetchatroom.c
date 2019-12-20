#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define MAX_CLIENTS 10
#define BUFFER_SIZE 2048

static _Atomic unsigned int cli_count = 0;
static int uid = 10;

typedef struct {
    struct sockaddr_in addr;
    int connfd;
    int uid;
    char name[32];
    bool isOp;
} client_t;

client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
static char topic[BUFFER_SIZE / 2];
pthread_mutex_t topic_mutex = PTHREAD_MUTEX_INITIALIZER;

char *_strdup(const char *s)
{
    size_t size = strlen(s) + 1;
    char *p = malloc(size);
    if (p)
        memcpy(p, s, size);
    return p;
}

void addClient(client_t *c)
{
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (!clients[i])
        {
            clients[i] = c;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void delClient(int uid)
{
    pthread_mutex_lock(&clients_mutex);
    for (int  i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i])
        {
            if (clients[i]->uid == uid)
            {
                clients[i] = NULL;
                break;
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void sendMessage(char *s, int uid)
{
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i])
        {
            if (clients[i]->uid != uid)
            {
                if (write(clients[i]->connfd, s, strlen(s)) < 0)
                {
                    perror("Write to descriptor failed");
                    break;
                }
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void sendToAll(char *s)
{
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i])
        {
            if (write(clients[i]->connfd, s, strlen(s)) < 0)
            {
                perror("Write to descriptor failed");
                break;
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void sendToSelf(const char *s, int connfd)
{
    if (write(connfd, s, strlen(s)) < 0)
    {
        perror("Write to descriptor failed");
        exit(-1);
    }
}

void sendToClient(char *s, int uid)
{
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i])
        {
            if (clients[i]->uid == uid)
            {
                if (write(clients[i]->connfd, s, strlen(s))<0)
                {
                    perror("Write to descriptor failed");
                    break;
                }
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void sendClientList(int connfd)
{
    char s[64];
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        if (clients[i])
        {
            sprintf(s, "=> [%d] %s\r\n", clients[i]->uid, clients[i]->name);
            sendToSelf(s, connfd);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void stripNewline(char *s)
{
    while (*s != '\0')
    {
        if (*s == '\r' || *s == '\n')
        {
            *s = '\0';
        }
        s++;
    }
}

void printIPAddr(struct sockaddr_in addr)
{
    printf("%d.%d.%d.%d",
        addr.sin_addr.s_addr & 0xff,
        (addr.sin_addr.s_addr & 0xff00) >> 8,
        (addr.sin_addr.s_addr & 0xff0000) >> 16,
        (addr.sin_addr.s_addr & 0xff000000) >> 24);
}

void *handle_client(void *arg){
    char buff_out[BUFFER_SIZE];
    char buff_in[BUFFER_SIZE / 2];
    int rlen;
    cli_count++;
    client_t *cli = (client_t *)arg;
    printf("=> accept ");
    printIPAddr(cli->addr);
    printf(" referenced by %d\n", cli->uid);
    sprintf(buff_out, "=> %s has joined\r\n", cli->name);
    sendToAll(buff_out);

    pthread_mutex_lock(&topic_mutex);
    if (strlen(topic)) {
        buff_out[0] = '\0';
        sprintf(buff_out, "=> topic: %s\r\n", topic);
        sendToSelf(buff_out, cli->connfd);
    }
    pthread_mutex_unlock(&topic_mutex);

    sendToSelf("=> see /help for assistance\r\n", cli->connfd);

    /* Receive input from client */
    while ((rlen = read(cli->connfd, buff_in, sizeof(buff_in) - 1)) > 0) {
        buff_in[rlen] = '\0';
        buff_out[0] = '\0';
        stripNewline(buff_in);

        /* Ignore empty buffer */
        if (!strlen(buff_in)) {
            continue;
        }

        /* Special options */
        if (buff_in[0] == '/') {
            char *command, *param;
            command = strtok(buff_in," ");
            if (!strcmp(command, "/quit")) {
                break;
            } else if (!strcmp(command, "/ping")) {
                sendToSelf("=> pong\r\n", cli->connfd);
            } else if (!strcmp(command, "/topic")) {
                param = strtok(NULL, " ");
                if (param) {
                    pthread_mutex_lock(&topic_mutex);
                    topic[0] = '\0';
                    while (param != NULL) {
                        strcat(topic, param);
                        strcat(topic, " ");
                        param = strtok(NULL, " ");
                    }
                    pthread_mutex_unlock(&topic_mutex);
                    sprintf(buff_out, "=> topic changed to: %s \r\n", topic);
                    sendToAll(buff_out);
                } else {
                    sendToSelf("=> message cannot be null\r\n", cli->connfd);
                }
            } else if (!strcmp(command, "/nick")) {
                param = strtok(NULL, " ");
                if (param) {
                    char *old_name = _strdup(cli->name);
                    if (!old_name) {
                        perror("Cannot allocate memory");
                        continue;
                    }
                    strcpy(cli->name, param);
                    sprintf(buff_out, "=> %s is now known as %s\r\n", old_name, cli->name);
                    free(old_name);
                    sendToAll(buff_out);
                } else {
                    sendToSelf("=> name cannot be null\r\n", cli->connfd);
                }
            } else if (!strcmp(command, "/msg")) {
                param = strtok(NULL, " ");
                if (param) {
                    int uid = atoi(param);
                    param = strtok(NULL, " ");
                    if (param) {
                        sprintf(buff_out, "[PM][%s]", cli->name);
                        while (param != NULL) {
                            strcat(buff_out, " ");
                            strcat(buff_out, param);
                            param = strtok(NULL, " ");
                        }
                        strcat(buff_out, "\r\n");
                        sendToClient(buff_out, uid);
                    } else {
                        sendToSelf("=> message cannot be null\r\n", cli->connfd);
                    }
                } else {
                    sendToSelf("=> reference cannot be null\r\n", cli->connfd);
                }
            } else if(!strcmp(command, "/list")) {
                sprintf(buff_out, "=> clients %d\r\n", cli_count);
                sendToSelf(buff_out, cli->connfd);
                sendClientList(cli->connfd);
            } else if (!strcmp(command, "/help")) {
                strcat(buff_out, "=> /quit     Quit chatroom\r\n");
                strcat(buff_out, "=> /ping     Server test\r\n");
                strcat(buff_out, "=> /topic    <message> Set chat topic\r\n");
                strcat(buff_out, "=> /nick     <name> Change nickname\r\n");
                strcat(buff_out, "=> /msg      <reference> <message> Send private message\r\n");
                strcat(buff_out, "=> /list     Show active clients\r\n");
                strcat(buff_out, "=> /help     Show help\r\n");
                sendToSelf(buff_out, cli->connfd);
            } else {
                sendToSelf("=> unknown command\r\n", cli->connfd);
            }
        } else {
            /* Send message */
            fflush(stdout);
            if (cli->isOp)
            {
                snprintf(buff_out, sizeof(buff_out), "\x1B[34m<%s>\x1B[0m %s\r\n", cli->name, buff_in);
            } else {
                snprintf(buff_out, sizeof(buff_out), "[%s] %s\r\n", cli->name, buff_in);
            }
            printf(buff_out);
            sendMessage(buff_out, cli->uid);
        }
    }

    /* Close connection */
    sprintf(buff_out, "=> %s has left\r\n", cli->name);
    sendToAll(buff_out);
    close(cli->connfd);

    /* Delete client from queue and yield thread */
    delClient(cli->uid);
    printf("=> quit ");
    printIPAddr(cli->addr);
    printf(" referenced by %d\n", cli->uid);
    free(cli);
    cli_count--;
    pthread_detach(pthread_self());

    return NULL;
}

int main(int argc, char *argv[]){
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    pthread_t tid;

    /* Socket settings */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    /* Ignore pipe signals */
    signal(SIGPIPE, SIG_IGN);

    /* Bind */
    if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Socket binding failed");
        return EXIT_FAILURE;
    }

    /* Listen */
    if (listen(listenfd, 10) < 0) {
        perror("Socket listening failed");
        return EXIT_FAILURE;
    }

    printf("<[ SERVER STARTED ]>\n");

    /* Accept clients */
    while (1) {
        socklen_t clilen = sizeof(cli_addr);
        connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);

        /* Check if max clients is reached */
        if ((cli_count + 1) == MAX_CLIENTS) {
            printf("=> max clients reached\n");
            printf("=> reject ");
            printIPAddr(cli_addr);
            printf("\n");
            close(connfd);
            continue;
        }

        /* Client settings */
        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->addr = cli_addr;
        cli->connfd = connfd;
        cli->isOp = false;
        if (uid == 10)
            cli->isOp = true;
        cli->uid = uid++;
        sprintf(cli->name, "%d", cli->uid);

        /* Add client to the queue and fork thread */
        addClient(cli);
        pthread_create(&tid, NULL, &handle_client, (void*)cli);

        /* Reduce CPU usage */
        sleep(1);
    }

    return EXIT_SUCCESS;
}
