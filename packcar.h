#ifndef PACKCAR_H
#define PACKCAR_H
    // Function Phototype Declarations
    bool cmd(void);
    bool Split  (char[5][125], char[], char*);
    void help   (void);
    void error  (char[5][125]);
    void park   (void);
    bool Reserve(char*);
    bool Cancel (char*);
    int  findIndex (char*);
    void setall (bool);
    void park_count (void);
#endif