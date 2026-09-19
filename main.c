#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(){
char c[1000];
char *args[100];
printf("< ");
fflush(stdout);
while(fgets(c,1000,stdin)!=NULL){
    c[strlen(c)-1] = '\0';
    if(strcmp(c, "exit")==0){
        break;
    }
    char *rec=strtok(c, " ");
    int i=0;
    while(rec!=NULL){
        args[i]=rec;
        i++;
        rec=strtok(NULL, " ");
    }
    args[i]=NULL;
    if (strcmp(args[0], "cd") == 0) {
        if(chdir(args[1])!=0){
            perror("cd");
        }
        continue;
    }
    int pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        printf("nema te komande\n");
        exit(1);
    } else {
        wait(NULL);
    }
    printf("< ");
    fflush(stdout);
}
}
