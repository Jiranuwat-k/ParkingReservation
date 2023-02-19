#ifndef AUTH_H
#define AUTH_H
    const char* USER_FORMAT_IN  = "(%[^,], %[^,], %[^,], %c)";
    const char* USER_FORMAT_OUT = "(%s, %s, %s, %c)\n";
    struct user{
        char  uid[14];
        char username[50];
        char password[50];
        char gender;
    };
    struct user user;
#endif