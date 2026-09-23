#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(){
char c[1000];
char *args[100];
while(1){
    printf("< ");
    fflush(stdout);
    if(fgets(c,1000,stdin)==NULL) break;
    c[strlen(c)-1] = '\0';
    if (strcmp(c, "exit") == 0) break;
    char *rec=strtok(c, " ");
    int i=0;
    while(rec!=NULL){
        args[i]=rec;
        i++;
        rec=strtok(NULL, " ");
    }
    args[i]=NULL;
    if (args[0] == NULL) {
        continue;
}
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            chdir(getenv("HOME"));
        } else if (chdir(args[1]) != 0) {
            perror("cd");
        }
        continue;
    }
    int pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        fprintf(stderr, "%s: command not found\n", args[0]);
        exit(1);
    } else {
        wait(NULL);
    }
}
}
