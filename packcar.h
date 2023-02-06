#ifndef PACKCAR_H
#define PACKCAR_H
    // Define ANSI Escape Color
    #define KNRM  "\x1B[0m"
    #define KRED  "\x1B[31m"
    #define KGRN  "\x1B[32m"
    #define KYEL  "\x1B[33m"
    #define KBLU  "\x1B[34m"
    #define KMAG  "\x1B[35m"
    #define KCYN  "\x1B[36m"
    #define KWHT  "\x1B[37m"
    // Enable CMD ANSI Escape
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
    #endif
    // Function Phototype Declarations
    int  cmd(void);
    int  Split(char[255][255], char[], char*);
    void help(void);
    void error(char[255][255]);
    void park(void);
#endif