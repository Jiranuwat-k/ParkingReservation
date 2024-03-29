## Feature
- [x] Receive orders from users
- [x] Reserve parking
- [x] Cancellation of parking
- [x] Storage
- [x] Login/Register
- [x] Advice Parking
## Reference
- ANSI Escape
  - [Document ](https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797)
  - [Open ANSI settings in CMD, Powershell, etc. ](https://stackoverflow.com/questions/62784691/coloring-text-in-cmd-c)
``` c
    // Enable CMD ANSI Escape
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
    #endif
```
- C Library 
  - [String.h and Standard Library Document ](https://www.tutorialspoint.com/c_standard_library/string_h.htm) 
## Issue
- Color rendering doesn't work properly on the command prompt.

    ![command prompt.](assets/Issue_Color_CommandPrompt.jpg)
## Tools
- Use MinGW ("Minimalist GNU for Windows")
- Compiler
  - mingw32-gcc-g++-bin  version 2.9.0-2
## License
None
#### [IEE@KMUTNB](https://iee.eng.kmutnb.ac.th/iee/)
##### [Instrumentation and Electronics Engineering](https://iee.eng.kmutnb.ac.th/iee)
