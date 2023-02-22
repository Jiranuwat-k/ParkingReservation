#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "config.h"
#include "parking.h" // initialize file
#include "parkingadvice.h"
#include "auth.h"
bool auth_status = 0;
bool rights = 0;
int reserve_id;
char* reserve_spot;
int main(void){
    loadparkstatus(parking1_path,parking1_status);
    loadparkstatus(parking2_path,parking2_status);
    loadparkstatus(parking3_path,parking3_status);
    loadparkstatus(parking4_path,parking4_status);
    loadparkstatus(parking5_path,parking5_status);
    bool exit = 0;
    printf(KCLS);
    auth_status = !authentication();
    delay(1);
    printf(KCLS);
    while (!exit&&auth_status){
        printf(KNRM); // reset color 
        exit = cmd();
    }
    return 0;
}

// Function Definitions
bool cmd(void){
    char cmd[255] = " ",buf[5][125] = {" "};
    printf("%s > "KYEL,user.username);
    // gets(cmd);
    scanf(" %[^\n]s",cmd);
    printf(KNRM);
    // getline(cmd,sizeof(cmd),stdin);
    // scanf("%s",&cmd);  //not used
    // fgets(cmd, sizeof(cmd), stdin); // not used
    int i,k = Split(buf,cmd," \n");
    
    if(!strcmp(buf[0],"help")&&!strlen(buf[1])){
        help();
    }else if(!strcmp(buf[0],"--version")||!strcmp(buf[0],"--v")&&!strlen(buf[1])){
        printf(KYEL"1.0.1-alpha\n");
    }else if(!strcmp(buf[0],"parking")&&!strlen(buf[1])){
        dis_parkinglist();
        getparkingid();
    }else if(!strcmp(buf[0],"time")&&!strlen(buf[1])){
        dis_time();
    }else if(!strcmp(buf[0],"reserve")&&!strlen(buf[1])){
        if (rights){
            printf(KRED"You cannot make a reservation because you have already exercised your reservation rights.\n");
            return 0;
        }
        int id;
        char spot[3];
        dis_parkinglist();
        id = getparkingid();
        printf(KMAG"\t\tPlease select a parking spot : "KYEL);
        scanf("%s",spot);
        Setparkingbyid(id,spot,1);
    }else if(!strcmp(buf[0],"cancel")&&!strlen(buf[1])){
        // if(){

        // }
        // int id;
        // char spot[3];
        // dis_parkinglist();
        // id = getparkingid();
        // printf(KMAG"\t\tPlease select a parking spot to Cancel : "KYEL);
        // scanf("%s",spot);
        Setparkingbyid(reserve_id,reserve_spot,0);
    }else if(!strcmp(buf[0],"advice")&&!strlen(buf[1])){
        char select = ' ';
        CatetoryList();
        Advice();
        printf(KNRM"\tWould you like to reserve a parking spot? (Y/N) : "KYEL);
        scanf(" %c",&select);
        if('y' == tolower(select)){
            if (rights){
                printf(KRED"You cannot make a reservation because you have already exercised your reservation rights.\n");
                return 0;
            }
            int id;
            char spot[3];
            dis_parkinglist();
            id = getparkingid();
            printf(KMAG"\t\tPlease select a parking spot : "KYEL);
            scanf("%s",spot);
            Setparkingbyid(id,spot,1);
        }
    }else if(!strcmp(buf[0],"logout")&&!strlen(buf[1])){
        auth_status = 0;
        printf(KCLS);
        auth_status = !authentication();
        delay(1);
        printf(KCLS);
    }else if(!strcmp(buf[0],"catetory")&&!strlen(buf[1])){
        CatetoryList();
    }else if(!strcmp(buf[0],"catetoryfloor")&&!strlen(buf[1])){
        CatetoryListFloor();
    }else if(!strcmp(buf[0]," ")){
        return 0;
    }else if(!strcmp(buf[0],"cls")||!strcmp(buf[0],"clear")&&!strlen(buf[1])){
        printf(KCLS);
    }else if(!strcmp(buf[0],"exit")&&!strlen(buf[1])){
        printf(KNRM);
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
    printf("\tparking       \t\t: Get List Packing.\n");
    printf("\treserve       \t\t: Reserve packing.\n");
    printf("\tcancel        \t\t: Cancel reservation packing.\n");
    printf("\tadvice        \t\t: Recommended parking.\n");
    printf("\tcatetory        \t: Show all categories.\n");
    printf("\tcatetoryfloor        \t: Show categories on each floor.\n");
    printf("\tlogout        \t\t: Logout.\n");
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
void dis_parkinglayout(char parking[][3], bool status[],int row, int column){
    int i,j,parkinguse;
    int size = row*column;
    parkinguse = park_count(status,size);
    printf(KWHT"\n\x1B[48;5;202m\t\t             Parking Map            \x1B[0m\n\n\t\t");
    for(i = 0; i<size;i++){
        printf(KCYN"| ");
        printf((status[i] == 0) ? KGRN : KRED);
        printf("%s ",parking[i]);
        if(!((i+1)%column)){
            printf(KCYN"|\n\n\t\t");
        }
    }
    printf(KBLU"Parking use = %s%d%s   Parking Emtry = %s%d\n",KYEL,parkinguse,KBLU,KYEL,size-parkinguse);
}
bool Reserve(char parking[][3], bool p_status[], int size, char* s_index){
    if((!strcmp(s_index,"all")||!strcmp(s_index,"-a"))&&!strncmp(user.username,"Admin",50)){
        setall(p_status,size,1);
        return 0;
    }
    int index = findIndex(parking, size, s_index);
    if(index != -1){
        if(p_status[index]){
            printf(KRED"Reserve Fall\n");
            return 1;
        }
        p_status[index] = 1;
        return 0;
    }
    printf(KRED"Reserve Out of Range\n");
    return 1;
}
bool Cancel(char parking[][3], bool p_status[], int size, char* s_index){
    if((!strcmp(s_index,"all")||!strcmp(s_index,"-a"))&&!strncmp(user.username,"Admin",50)){
        setall(p_status,size,0);
        return 0;
    }
    int index = findIndex(parking, size, s_index);
    if(index != -1){
        if(!p_status[index]){
            printf(KRED"Cancel Fall\n");
            return 1;
        }
        p_status[index] = 0;
        return 0;
    }
    printf(KRED"Cancel outofrange\n");
    return 1;
}
int findIndex(char dataset[][3], int size, char* text){
    int i;
    for ( i = 0; i < size; i++)
    {
        if(!strcmp(dataset[i],text)){
            return i;
        }
    }
    return -1;
} 
int findIndex2(char dataset[][256], int size, char* text){
    int i;
    for ( i = 0; i < size; i++)
    {
        if(!strcmp(dataset[i],text)){
            return i;
        }
    }
    return -1;
} 
void setall(bool p_status[], int size, bool set){
    int i;
    for (i = 0; i < size; i++)
    {
        p_status[i] = set;
    }
}
int park_count(bool p_status[], int size){
    int i,count_use = 0;
    for (i = 0; i < size; i++)
    {
        if(p_status[i]){
            count_use += 1;
        }
    }
    return count_use;
}
void dis_time(void){
    struct tm *loc_time;
    time_t curtime = time(NULL);
    loc_time = localtime (&curtime);
    printf("\n%s\n", asctime (loc_time));
}
bool loadparkstatus(char *path, bool buf[]){
    int i, max = 0;
    FILE *stream;
    // use appropriate location if you are using MacOS or Linux
    stream = fopen(path,"r");
    if(stream == NULL)
    {
        writeparkstage(path,buf,-1); // set size -1 touse MaxSize_Parking_File 
        return 1;            
    }
    
    fscanf(stream,"Max_Capacity = %d",&max);
    for (i = 0; i < max; i++)
    {
        fscanf(stream,"%d ",&buf[i]);
    }
    fclose(stream);
    return 0;
}
bool writeparkstage(char *path, bool update[], int max){
    int i;
    if (max == -1){
        max = MaxSize_Parking_File;
    }
    FILE *stream;
    stream = fopen(path,"w");
    if(stream == NULL)
    {
        printf(KRED"File Write Error!\n");    
        return 1;            
    }
    fprintf(stream,"Max_Capacity = %d\n",max);
    for ( i = 0; i < max; i++)
    {
        fprintf(stream,"%d ",update[i]);
    }
    fclose(stream);
    return 0;
}

void CatetoryList(){
    int i;
    printf(KMAG"\n\t%-32s%s\n\n","Catetory","ID"KNRM);
    for (i = 0; i < 7; i++)
    {
        printf("\t%-32s%d\n",catetory[i],i+1);
    }
}
void CatetoryListFloor(){
    int i;
    printf(KMAG"\n\tFloor 1\n");
    for (i = 0; i < LEVEL1.maxcatetory; i++){
        printf(KNRM"\t\t%-32s\n",LEVEL1.catetory[i]);
    }
    printf(KMAG"\n\tFloor 2\n");
    for (i = 0; i < LEVEL2.maxcatetory; i++){
        printf(KNRM"\t\t%-32s\n",LEVEL2.catetory[i]);
    }
    printf(KMAG"\n\tFloor 3\n");
    for (i = 0; i < LEVEL3.maxcatetory; i++){
        printf(KNRM"\t\t%-32s\n",LEVEL3.catetory[i]);
    }
    printf(KMAG"\n\tFloor 4\n");
    for (i = 0; i < LEVEL4.maxcatetory; i++){
        printf(KNRM"\t\t%-32s\n",LEVEL4.catetory[i]);
    }
}
int Register(char* username, char* password, char gender){
        FILE* stream = fopen(auth_user_path,"a");
        if (stream == NULL){
            return -1;
        }
        // srand(time(NULL));
        if(UsernameIsuse(username)){
            srand(time(NULL));
            char uid[14];
            sprintf(uid,"%05d%05d",rand(),rand());
            fprintf(stream,USER_FORMAT_OUT,uid,username,password,gender);
        }else{
            printf(KRED"\t\tUsername is use.\n"KNRM);
            return 1; 
        }
        fclose(stream);
        return 0;
}
int Login(char* username, char* password){
    FILE* stream = fopen(auth_user_path,"r");
    if (stream == NULL)
    {
        return -1;
    }
    char buffer[200];
    fgets(buffer,200,stream);
    while (!feof(stream))
    {
        struct user data;
        sscanf(buffer,USER_FORMAT_IN,data.uid,data.username,data.password,&data.gender);
        if(!strncmp(data.username,username,50)&&!strncmp(data.password,password,50)){
            user = data;
            return 0;
        }
        fgets(buffer,200,stream);
    }
    fclose(stream);
    printf(KRED"\t\tThe username or password is incorrect or the user does not exist in the system.\n"KNRM);
    return 1;
}
bool UsernameIsuse(char* username){
    FILE* stream = fopen(auth_user_path,"r");
    if (stream == NULL)
    {
        return 1;
    }
    char buffer[200];
    fgets(buffer,200,stream);
    while (!feof(stream))
    {
        struct user data;
        sscanf(buffer,USER_FORMAT_IN,data.uid,data.username,data.password,&data.gender);
        if(!strncmp(data.username,username,50)){
            return 0;
        }
        fgets(buffer,200,stream);
    }
    fclose(stream);
    return 1;
}
bool authentication(){
    char selected = ' ',gender;
    char username[50],password[50];
    printf(KCYN"\n\n\t\tWelcome to the parking reservation and guide system.\n\n");
    while(1){
        printf(KMAG"\t\tYou want to login / register (L/R) : "KYEL);
        scanf(" %c",&selected);
        if ('l' == tolower(selected))
        {
            while (1){
                printf(KMAG"\t\tUsername : "KYEL);
                scanf("%s",&username);
                printf(KMAG"\t\tPassword : "KYEL);
                scanf("%s",&password);
                if(!Login(username, password)){
                    printf(KGRN"\t\tLogin Success.\n");
                    printf(KNRM"\t\tHello %s\n",user.username);
                    return 0;
                }
                break;
            }
        }else if('r' == tolower(selected)){
            while (1)
            {
                printf(KMAG"\t\tUsername : "KYEL);
                scanf("%s",&username);
                printf(KMAG"\t\tPassword : "KYEL);
                scanf("%s",&password);
                printf(KMAG"\t\tGender Male/Female (M/F) : "KYEL);
                scanf(" %c",&gender);
                if(!Register(username, password, gender)){
                    printf(KGRN"\t\tRegister Success.\n");
                    break;
                }
            }
            
        }
    }
}
void dis_parkinglist(){
        printf(KCYN"\n\t\tParking\t\t\tID\n\n");
        printf("\t\tMotorcycle park\t\t1\n");
        printf("\t\tCarpark 1\t\t2\n");
        printf("\t\tCarpark 2\t\t3\n");
        printf("\t\tCarpark 3\t\t4\n");
        printf("\t\tlady park\t\t5\n"KNRM);
}
int getparkingid(){
    int id,ex = 1;
    while (ex){
        printf(KMAG"\t\tPlease select parking by ID : "KYEL);
        scanf("%d",&id);
        if (id == 5 && tolower(user.gender) == 'm')
        {
            printf(KRED"\t\tYou can't make a reservation because it's a lady only parking.\n");
            continue;
        }
        switch (id){
            case 1:
                loadparkstatus(parking1_path,parking1_status);
                dis_parkinglayout(parking1,parking1_status,5,7);
                ex = 0;
                break;
            case 2:
                loadparkstatus(parking2_path,parking2_status);
                dis_parkinglayout(parking2,parking2_status,5,7);
                ex = 0;
                break;
            case 3:
                loadparkstatus(parking3_path,parking3_status);
                dis_parkinglayout(parking3,parking3_status,5,7);
                ex = 0;
                break;
            case 4:
                loadparkstatus(parking4_path,parking4_status);
                dis_parkinglayout(parking4,parking4_status,5,7);
                ex = 0;
                break;
            case 5:
                loadparkstatus(parking5_path,parking5_status);
                dis_parkinglayout(parking5,parking5_status,5,7);
                ex = 0;
                break;
            default:
                printf(KRED"\t\tCan't find your ID.\n");
                break;
        }    
    }
    return id;
}
void Setparkingbyid(int id, char* spot, int status){
    if (status){
        switch (id){
            case 1:
                if(!Reserve(parking1, parking1_status,parking1_Max_Capacity,spot)){
                    printf(KGRN"Reserve Success\n");
                    writeparkstage(parking1_path,parking1_status,parking1_Max_Capacity);
                    dis_parkinglayout(parking1,parking1_status,5,7);
                    rights = 1;
                    reserve_id = id;
                    reserve_spot = spot;
                }
                break;
            case 2:
                if(!Reserve(parking2, parking2_status,parking2_Max_Capacity,spot)){
                    printf(KGRN"Reserve Success\n");
                    writeparkstage(parking2_path,parking2_status,parking2_Max_Capacity);
                    dis_parkinglayout(parking2,parking2_status,5,7);
                    rights = 1;
                    reserve_id = id;
                    reserve_spot = spot;
                }
                break;
            case 3:
                if(!Reserve(parking3, parking3_status,parking3_Max_Capacity,spot)){
                    printf(KGRN"Reserve Success\n");
                    writeparkstage(parking3_path,parking3_status,parking3_Max_Capacity);
                    dis_parkinglayout(parking3,parking3_status,5,7);
                    rights = 1;
                    reserve_id = id;
                    reserve_spot = spot;
                }
                break;
            case 4:
                if(!Reserve(parking4, parking4_status,parking4_Max_Capacity,spot)){
                    printf(KGRN"Reserve Success\n");
                    writeparkstage(parking4_path,parking4_status,parking4_Max_Capacity);
                    dis_parkinglayout(parking4,parking4_status,5,7);
                    rights = 1;
                    reserve_id = id;
                    reserve_spot = spot;
                }
                break;
            case 5:
                if(!Reserve(parking5, parking5_status,parking5_Max_Capacity,spot)){
                    printf(KGRN"Reserve Success\n");
                    writeparkstage(parking5_path,parking5_status,parking5_Max_Capacity);
                    dis_parkinglayout(parking5,parking5_status,5,7);
                    rights = 1;
                    reserve_id = id;
                    reserve_spot = spot;
                }
                break;
        }
    }else{
        switch (id){
            case 1:
                if(!Cancel(parking1, parking1_status,parking1_Max_Capacity,spot)){
                    printf(KGRN"Cancel Success\n");
                    writeparkstage(parking1_path,parking1_status,parking1_Max_Capacity);
                    dis_parkinglayout(parking1,parking1_status,5,7);
                    rights = 0;
                }
                break;
            case 2:
                if(!Cancel(parking2, parking2_status,parking2_Max_Capacity,spot)){
                    printf(KGRN"Cancel Success\n");
                    writeparkstage(parking2_path,parking2_status,parking2_Max_Capacity);
                    dis_parkinglayout(parking2,parking2_status,5,7);
                    rights = 0;
                }
                break;
            case 3:
                if(!Cancel(parking3, parking3_status,parking3_Max_Capacity,spot)){
                    printf(KGRN"Cancel Success\n");
                    writeparkstage(parking3_path,parking3_status,parking3_Max_Capacity);
                    dis_parkinglayout(parking3,parking3_status,5,7);
                    rights = 0;
                }
                break;
            case 4:
                if(!Cancel(parking4, parking4_status,parking4_Max_Capacity,spot)){
                    printf(KGRN"Cancel Success\n");
                    writeparkstage(parking4_path,parking4_status,parking4_Max_Capacity);
                    dis_parkinglayout(parking4,parking4_status,5,7);
                    rights = 0;
                }
                break;
            case 5:
                if(!Cancel(parking5, parking5_status,parking5_Max_Capacity,spot)){
                    printf(KGRN"Cancel Success\n");
                    writeparkstage(parking5_path,parking5_status,parking5_Max_Capacity);
                    dis_parkinglayout(parking5,parking5_status,5,7);
                    rights = 0;
                }
                break;
        }
    }
}
void Advice(){
    int i,s_catetory,index;
    printf(KMAG"\tPlease select the desired store category : "KYEL);
    scanf("%d",&s_catetory);
    s_catetory -= 1;
    printf("\t** Nearest lady parking.\n");
    printf("\t** Farthest motorcycle parking.\n");
    printf("\n\t%-32s%-11s%-11s%-11s","Name","near","far","quite far");
    index = findIndex2(LEVEL1.catetory,LEVEL1.maxcatetory,catetory[s_catetory]);
    if(index != -1){
        printf(KCYN"\n\tFloor 1\n");
        printf("\t%-32s",LEVEL1.catetory[index]);
        for (i = 0; i < 3; i++)
        {
            printf("%s  ",parkingname[LEVEL1.parkingnear[index][i]-1]);
        }
        printf("\n");
    }
    index = findIndex2(LEVEL2.catetory,LEVEL2.maxcatetory,catetory[s_catetory]);
    if(index != -1){
        printf(KCYN"\n\tFloor 2\n");
        printf("\t%-32s",LEVEL2.catetory[index]);
        for (i = 0; i < 3; i++)
        {
            printf("%s  ",parkingname[LEVEL2.parkingnear[index][i]-1]);
        }
        printf("\n");
    }
    index = findIndex2(LEVEL3.catetory,LEVEL3.maxcatetory,catetory[s_catetory]);
    if(index != -1){
        printf(KCYN"\n\tFloor 3\n");
        printf("\t%-32s",LEVEL3.catetory[index]);
        for (i = 0; i < 3; i++)
        {
            printf("%s  ",parkingname[LEVEL3.parkingnear[index][i]-1]);
        }
        printf("\n");
    }
    index = findIndex2(LEVEL4.catetory,LEVEL4.maxcatetory,catetory[s_catetory]);
    if(index != -1){
        printf(KCYN"\n\tFloor 4\n");
        printf("\t%-32s",LEVEL4.catetory[index]);
        for (i = 0; i < 3; i++)
        {
            printf("%s  ",parkingname[LEVEL4.parkingnear[index][i]-1]);
        }
        printf("\n");
    }
}
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}
void autocheckout(){

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