#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "config.h"
#include "packcar.h" // initialize file
// Global Variable Declarations
char parking [][3] = {"A0","A1","A2","A3","A4","A5","A6",
                      "B0","B1","B2","B3","B4","B5","B6",
                      "C0","C1","C2","C3","C4","C5","C6",
                      "D0","D1","D2","D3","D4","D5","D6",
                      "E0","E1","E2","E3","E4","E5","E6"
                    };
int empty_parking = 0;
int use_parking   = 0;
const int Max_Capacity = sizeof(parking)/sizeof(parking[0]);
bool park_stage[sizeof(parking)/sizeof(parking[0])] = {0};
int main(void){
    bool exit = 0;
    // park();
    printf(KCLS);
    while (!exit){
        printf(KNRM); // reset color 
        exit = cmd();
        park_count();
    }
    // getchar(); //not used
}

// Function Definitions
bool cmd(void){
    char cmd[255],buf[5][125] = {" "};
    printf("Parkingcar> ");
    // scanf("%s",&cmd);  //not used
    fgets(cmd, sizeof(cmd), stdin);
    int i,k = Split(buf,cmd," \n");
    // debug
    // for (i = 0; i < k+1; i++)
    // {
    //     printf("%d == |%s|\n",i,buf[i]);
    // }
    if(!strcmp(buf[0],"help")&&!strlen(buf[1])){
        help();
    }else if(!strcmp(buf[0],"--version")||!strcmp(buf[0],"--v")&&!strlen(buf[1])){
        printf(KYEL"1.0.1-alpha\n");
    }else if(!strcmp(buf[0],"parkcar")&&!strlen(buf[1])){
        park();
    }else if(!strcmp(buf[0],"time")&&!strlen(buf[1])){
        struct tm *loc_time;
        time_t curtime = time(NULL);
        loc_time = localtime (&curtime);
        printf("\n%s\n", asctime (loc_time));
    }else if(!strcmp(buf[0],"reserve")&&!strlen(buf[2])){
        if (!strlen(buf[1])){
            printf(KRED"No value was entered to select.\n");
            return 0;
        }
        if(!Reserve(buf[1])){
            printf(KGRN"Reserve Success\n");
            park();
        }
    }else if(!strcmp(buf[0],"cancel")&&!strlen(buf[2])){
        if (!strlen(buf[1])){
            printf(KRED"No value was entered to select.\n");
            return 0;
        }
        if(!Cancel(buf[1])){
            printf(KGRN"Cancel Success\n");
            park();
        }
    }else if(!strcmp(buf[0]," ")){
        return 0;
    }else if(!strcmp(buf[0],"cls")||!strcmp(buf[0],"clear")&&!strlen(buf[1])){
        printf(KCLS);
    }else if(!strcmp(buf[0],"exit")&&!strlen(buf[1])){
        return 1;
    }else{
        error(buf);
    }
    return 0;
}
bool Split(char buf[5][125], char str[],char* delim){
    char* string = str;
    // Extract the first token
    char * token = strtok(string,delim);
    int i = 0;
    while( token != NULL ) {
        //printf( " %s\n", token ); //Debug printing each token
        strcpy(buf[i],token);
        token = strtok(NULL,delim);
        i++;
   }
   return i;
}
void help(void){
    printf("\t\t\tHelp Program\n\n");
    printf("\thelp          \t\t: Get-Help name of a function or operable program.\n");
    printf("\t--v, --version\t\t: Get Program Version.\n");
    printf("\tparkcar       \t\t: Get List Packcar.\n");
    printf("\treserve       \t\t: Reserve Packcar.\n");
    printf("\t  Usage : reserve [options]\n");
    printf("\t  Options:\n");
    printf("\t  -a, all     \t\t: Reserve All ParkCar.\n");
    printf("\t  {ID}        \t\t: Reserve ID in ParkCar. (Ex. reserve A0)\n");
    printf("\tcancel        \t\t: Reserve Packcar.\n");
    printf("\t  Usage : cancel [options]\n");
    printf("\t  Options:\n");
    printf("\t  -a, all     \t\t: Cancel reserve All ParkCar.\n");
    printf("\t  {ID}        \t\t: Cancel reserve ID in ParkCar. (Ex. cancel A0)\n");
    printf("\texit          \t\t: Exit Program.\n");
    printf("\tcls, clear    \t\t: Clear Program Display.\n");
    printf("\ttime          \t\t: Get Now Date-Time.\n\n");
}
void error(char buf[5][125]){
    printf(KRED"%s : The term \'%s\' is not recognized as the name of a cmdlet, function, script file, or operable program.\n",buf[0],buf[0]);
    int i;
    printf("+ ");
    for (i = 0; i < 5; i++)
    {
        if(strlen(buf[i])){
            printf("%s ",buf[i]);
        }
    }
    printf("\n");
}
void park(void){
    int i,j;
    printf(KWHT"\n\x1B[48;5;202m\t\t             Parkcar Map            \x1B[0m\n\n\t\t");
    for(i = 0; i<Max_Capacity;i++){
        printf(KCYN"| ");
        printf((park_stage[i] == 0) ? KGRN : KRED);
        printf("%s ",parking[i]);
        if(!((i+1)%7)){
            printf(KCYN"|\n\n\t\t");
        }
    }
    printf("\n");
}
bool Reserve(char* s_index){
    if(!strcmp(s_index,"all")||!strcmp(s_index,"-a")){
        setall(1);
        return 0;
    }
    int index = findIndex(s_index);
    if(index != -1){
        if(park_stage[index]){
            printf(KRED"Reserve Fall\n");
            return 1;
        }
        park_stage[index] = 1;
        return 0;
    }
    printf(KRED"Reserve Out of Range\n");
    return 1;
}
bool Cancel(char* s_index){
    if(!strcmp(s_index,"all")||!strcmp(s_index,"-a")){
        setall(0);
        return 0;
    }
    int index = findIndex(s_index);
    if(index != -1){
        if(!park_stage[index]){
            printf(KRED"Cancel Fall\n");
            return 1;
        }
        park_stage[index] = 0;
        return 0;
    }
    printf(KRED"Cancel outofrange\n");
    return 1;
}
int findIndex(char* text){
    int i;
    for ( i = 0; i < Max_Capacity; i++)
    {
        if(!strcmp(parking[i],text)){
            return i;
        }
    }
    return -1;
}
void setall(bool stage){
    int i;
    for (i = 0; i < Max_Capacity; i++)
    {
        park_stage[i] = stage;
    }
}
void park_count(void){

}
// function convert string to Uppercase String ()
// void strtoupper(char string[]){
//     int i = 0;
//     char ch;
//     while (string[i])
//     {
//         ch = string[i];
//         // toupper
//         strcpy(string,towupper(string[i]));
//         i++;
//     }
    
// }