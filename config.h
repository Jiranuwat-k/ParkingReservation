#ifndef CONFIG_H
#define CONFIG_H
    // Define ANSI Escape Color
    #define KNRM  "\x1B[0m"
    #define KRED  "\x1B[31m"
    #define KGRN  "\x1B[32m"
    #define KYEL  "\x1B[33m"
    #define KBLU  "\x1B[34m"
    #define KMAG  "\x1B[35m"
    #define KCYN  "\x1B[36m"
    #define KWHT  "\x1B[37m"
    #define KCLS  "\x1B[1J\x1B[H"
    // app
    int MaxSize_Parking_File = 35;  // use in function file read/write
    char* parking1_path = "appData/stage/parking1.txt";
    char* parking2_path = "appData/stage/parking2.txt";
    char* parking3_path = "appData/stage/parking3.txt";
    char* parking4_path = "appData/stage/parking4.txt";
    char* parking5_path = "appData/stage/parking5.txt";
    char* auth_user_path = "appData/auth/user.txt";
#endif
// Enable CMD ANSI Escape
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif