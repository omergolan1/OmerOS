#include "../Drivers/Typedefs.h"
#include "../Drivers/VGA_Text.h"
#include "../Drivers/Conversions.h"
#include "../Memory/mem.h"
#include "../Drivers/string.h"

extern const char* currentTask;

static const int numberOfCMDs = 6;

extern int CursorPos;

static const char *  const helpList[6] = {                  // find better (dynamic) way
    "  help: shows command list\n",
    "  echo [text]: prints text\n",
    "  usedmem: shows dynamic memory usage\n",
    "  clear: clears the screen\n",
    "  calc: p=+, m=*, s=- ,d=/ exmple: calc 2p2 = 4\n",
    "  dark: dark mode"
    
};

void calcCMD(const char* s){
    
   
}

void helpCMD(const char* s){
    if(strLen(s) == 0){
        currentTask = "help";
        kprint("List of commands:\n");
        for(int i = 0; i < numberOfCMDs; i++)
            kprint(helpList[i]);
    }
    else{
        kprint("Invalid option: \"");
        if(s[0] == ' ') kprint((const char*)((int)s + 1));
        else kprint(s);
        kprint("\"");
    }
   
}

void printUsedMem(const char* s){
    if(strLen(s) == 0){
        currentTask = "usedmem";
        kprint("Used dynamic memory: ");
        kprint(toString(getFreeMem() - 0x10000, 10));
        kprint(" bytes");
    }
    else{
        kprint("Invalid option: \"");
        if(s[0] == ' ') kprint((const char*)((int)s + 1));
        else kprint(s);
        kprint("\"");
    }
}

void clearCMD(const char* s){ 
    if(strLen(s) == 0){
        currentTask = "clear";
        ClearScreen(-1);
        CursorPos = 0;
    }
    else{
        kprint("Invalid option: \"");
        if(s[0] == ' ') kprint((const char*)((int)s + 1));
        else kprint(s);
        kprint("\"");
    }
    
}
void DarkMode(const char* s){ 
    if(strLen(s) == 0){
        currentTask = "clear";
        ClearScreen(2);
        CursorPos = 0;
    }
    else{
        kprint("Invalid option: \"");
        if(s[0] == ' ') kprint((const char*)((int)s + 1));
        else kprint(s);
        kprint("\"");
    }
    
}
