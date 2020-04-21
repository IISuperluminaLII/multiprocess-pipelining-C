#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <unistd.h>
#include  <sys/types.h>
#include  <iostream>
#include  <signal.h>

int main (){

    int num_pipes = 2;
    int fd[2], nbytes,fd_t[2];
    pid_t child_pid_t;
    pid_t parent_pid_t;
    char *readBuffer = (char *)malloc(sizeof(char));
    unsigned long *readintBuffer = (unsigned long *)malloc(sizeof(unsigned long));
    char inputRead;
    int i = 1;
    int total_value = 0;
    int test_size = sizeof(unsigned long);
    int test_size_two = sizeof(int);
    parent_pid_t = getpid();
    pipe(fd);
    pipe(fd_t);

    //child_pid_t = fork();
    if((child_pid_t = fork()) == -1){
        perror("fork");
        exit(-1);
    }
    //Child Process
    if(child_pid_t == 0){
        //Ask Input
        while(inputRead != -1) {
            printf("Please enter something: ");
            std::cin >> inputRead;
            close(fd[0]);
            close(fd_t[1]);
            if(inputRead-46 == -1){
                printf("%d\n",*readintBuffer);
                exit(SIGTERM);
            }
            write(fd[1], &inputRead, sizeof(inputRead));
            read(fd_t[0], readintBuffer, sizeof(readintBuffer));
        }
        exit(SIGTERM);
    }else{
        //read the number from pipe
        close(fd[1]);
        close(fd_t[0]);
        if(i == 1)
            nbytes++;
        while(nbytes > 0){
            nbytes = read(fd[0],readBuffer,sizeof(readBuffer));
            total_value += *readBuffer;
            write(fd_t[1],&(total_value),sizeof(total_value));
            i++;
        }
    }
    return 0;
}