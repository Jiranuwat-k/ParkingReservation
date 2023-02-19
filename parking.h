#ifndef PARKING_H
#define PARKING_H
    // Global Variable Declarations
    char parking1 [][3] = {"A0","A1","A2","A3","A4","A5","A6",
                          "B0","B1","B2","B3","B4","B5","B6",
                          "C0","C1","C2","C3","C4","C5","C6",
                          "D0","D1","D2","D3","D4","D5","D6",
                          "E0","E1","E2","E3","E4","E5","E6"
                         }; //motorcycle park
    char parking2 [][3] = {"A0","A1","A2","A3","A4","A5","A6",
                          "B0","B1","B2","B3","B4","B5","B6",
                          "C0","C1","C2","C3","C4","C5","C6",
                          "D0","D1","D2","D3","D4","D5","D6",
                          "E0","E1","E2","E3","E4","E5","E6"
                         }; //car park
    char parking3 [][3] = {"A0","A1","A2","A3","A4","A5","A6",
                          "B0","B1","B2","B3","B4","B5","B6",
                          "C0","C1","C2","C3","C4","C5","C6",
                          "D0","D1","D2","D3","D4","D5","D6",
                          "E0","E1","E2","E3","E4","E5","E6"
                         }; //car park
    char parking4 [][3] = {"A0","A1","A2","A3","A4","A5","A6",
                          "B0","B1","B2","B3","B4","B5","B6",
                          "C0","C1","C2","C3","C4","C5","C6",
                          "D0","D1","D2","D3","D4","D5","D6",
                          "E0","E1","E2","E3","E4","E5","E6"
                         }; //car park
    char parking5 [][3] = {"A0","A1","A2","A3","A4","A5","A6",
                          "B0","B1","B2","B3","B4","B5","B6",
                          "C0","C1","C2","C3","C4","C5","C6",
                          "D0","D1","D2","D3","D4","D5","D6",
                          "E0","E1","E2","E3","E4","E5","E6"
                         }; //lady park
    const int parking1_Max_Capacity = sizeof(parking1)/sizeof(parking1[0]);
    bool parking1_status[sizeof(parking1)/sizeof(parking1[0])] = {0};
    const int parking2_Max_Capacity = sizeof(parking2)/sizeof(parking2[0]);
    bool parking2_status[sizeof(parking2)/sizeof(parking2[0])] = {0};
    const int parking3_Max_Capacity = sizeof(parking3)/sizeof(parking3[0]);
    bool parking3_status[sizeof(parking3)/sizeof(parking3[0])] = {0};
    const int parking4_Max_Capacity = sizeof(parking4)/sizeof(parking4[0]);
    bool parking4_status[sizeof(parking4)/sizeof(parking4[0])] = {0};
    const int parking5_Max_Capacity = sizeof(parking5)/sizeof(parking5[0]);
    bool parking5_status[sizeof(parking5)/sizeof(parking5[0])] = {0};
    // Function Phototype Declarations
    bool cmd(void);
    bool Split  (char[5][125], char[], char*);
    void help   (void);
    void error  (char[5][125]);
    void dis_parkinglayout (char[][3], bool[], int, int);
    bool Reserve(char[][3], bool[], int, char*);
    bool Cancel (char[][3], bool[], int, char*);
    int  findIndex (char[][3], int, char*);
    void setall (bool[], int, bool);
    int  park_count (bool[], int);
    bool loadparkstatus (char*, bool[]);
    bool writeparkstage(char*, bool[], int);
    void dis_time(void);
    void CatetoryList();
    void CatetoryListFloor();
    int Login(char*, char*);
    int Register(char*, char*, char);
    bool UsernameIsuse(char*);
    bool authentication();
#endif