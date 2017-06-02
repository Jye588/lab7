/* $begin shellmain */
#include "csapp.h"
#define MAXARGS   128

int main(int argc, char** argv) 
{
    char fn[MAXLINE];
    char gzName[MAXLINE];
    char exe[MAXLINE];
    FILE* fp;
    pid_t pid;
    int status;

    printf("arg: %d\n", argc);
    if(argc < 2){
	fprintf(stdout, "Enter file name\n");
	exit(0);
    }

    fp=fopen(argv[1], "r");
    while(1){
	if(fgets(gzName, MAXLINE, fp)==NULL)
		break;
	sprintf(fn, "list/%s",gzName);
	fn[strlen(fn)-1] = '\0';
        printf("fn: %s\n", fn);
  	 
	if((pid=Fork() ==0)){	
		//sprintf(exe, "tar -xvzf %s -C temp/", fn);
		execlp("gzip", "gzip", "-d", fn, NULL);
		exit(0);
	}
    }

    while(wait(&status) >0);
    
    printf("All child processes are terminated\n");
    fclose(fp);
    return 0;
}
