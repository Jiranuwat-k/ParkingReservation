#include <stdio.h>
#include <string.h>
#include <time.h>
#include "packcar.h" // initialize file

int main(void){
    int exit = 0;
    while (!exit){
        exit = cmd();
    }
    // getchar(); //Don't use
}

// Function Definitions
int cmd(void){
    char cmd[255],buf[255][255] = {" "};
    printf("Parkingcar> ");
    // scanf("%s",&cmd);  //don't use
    fgets(cmd, sizeof(cmd), stdin);
    int i,k = Split(buf,cmd," \n");
    // debug
    // for (i = 0; i < k+1; i++)
    // {
    //     printf("%d == |%s|\n",i,buf[i]);
    // }
    if(!strcmp(buf[0],"help")&&!strlen(buf[1])){
        help();
    }else if(!strcmp(buf[0],"--version")||!strcmp(buf[0],"--v")){
        printf("1.0.1-alpha\n");
    }else if(!strcmp(buf[0],"exit")){
        return 1;
    }else if(!strcmp(buf[0],"parkcar")){
        park();
    }else if(!strcmp(buf[0],"time")){
        struct tm *loc_time;
        time_t curtime = time(NULL);
        loc_time = localtime (&curtime);
        printf("\n%s\n", asctime (loc_time));
    }else if(!strcmp(buf[0]," ")){
        return 0;
    }else{
        error(buf);
    }
    return 0;
}
int Split(char buf[255][255], char str[],char* delim){
    char* string = str;
    // Extract the first token
    char * token = strtok(string,delim);
    int i = 0;
    while( token != NULL ) {
        //printf( " %s\n", token ); //printing each token
        strcpy(buf[i],token);
        token = strtok(NULL,delim);
        i++;
   }
   return i;
}
void help(void){
    printf("\t\t\tHelp Program\n\n");
    printf("\t--version ,--v\t\t: Get Program Version.\n");
    printf("\texit          \t\t: Exit Program.\n");
    printf("\tparkcar       \t\t: Get List Packcar.\n");
    printf("\ttime          \t\t: Get Now Date-Time.\n\n");
}
void error(char buf[255][255]){
    printf(KRED"%s : The term \'%s\' is not recognized as the name of a cmdlet, function, script file, or operable program.\n",buf[0],buf[0]);
    int i;
    printf("+ ");
    for (i = 0; i < 5; i++)
    {
        if(strlen(buf[i])){
            printf("%s ",buf[i]);
        }
    }
    printf("\n"KNRM);
}
void park(void){
    char parking [100][3] = {"A0","A1","A2","A3","A4","A5","A6",
                             "B0","B1","B2","B3","B4","B5","B6",
                             "C0","C1","C2","C3","C4","C5","C6",
                             "D0","D1","D2","D3","D4","D5","D6"
                             };
    int i;
    printf("\n\n"KGRN);
    for(i = 0; i<sizeof(parking)/sizeof(parking[0]);i++){
        printf("%s ",parking[i]);
        if(!(strcmp(parking[i],"A6")&&strcmp(parking[i],"B6")&&strcmp(parking[i],"C6"))){
            printf("\n");
        }
    }
    printf(KNRM"\n\n");
}