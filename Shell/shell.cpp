#include "../Drivers/Typedefs.h"
#include "../Drivers/VGA_Text.h"
#include "../Drivers/colors.h"
#include "../Drivers/string.h"
#include "shellFunctions.h"
#include "../Memory/mem.h"
#include "../Drivers/Conversions.h"


int CommandCursor;
extern int CursorPos;
extern int curMode;

extern int curColor;

const char* currentTask;

void load_shell(){
    curColor = DEFAULT_COLOR;
    currentTask = "init";
	ClearScreen(DEFAULT_COLOR);
	curMode = 10;
	ColLine(0, BAR_COLOR);
	ColLine(24, BAR_COLOR);
	ClrLine(24);
	SetCursorPos(0,0);
	kprint("Omer shell - [");
    kprint("task: ");
    kprint(currentTask);
    kprint(" | ");
    kprint("dir: -");
    kprint("]\n");
    kprint("Work in progress, ");
	CommandCursor = CursorPos;
	SetCursorPosRaw(1920);
	return;
    
}

void refreshShell(){
	SetCursorPos(0,0);
	kprint("Omer shell - [");
    kprint("task: ");
    kprint(currentTask);
    kprint(" | ");
    kprint("dir: -");
    kprint("]\n");
	SetCursorPosRaw(1920);
	return;
}

void calc(char s[])
{   bool beforeS=true;
    bool afterSpace = false;
    int multi=1;
    int num1=0;
    int num2=0;
    int sing;
    for (int i =0;i<strLen(s);i++)
    {  

        
         if (afterSpace){
            if (s[i]==0x70 || s[i]==0x6d ||s[i]==0x73||s[i]==0x64){
            beforeS=false;
            sing = s[i];
            multi=1;
            }
            else if (beforeS)
            {
                num1=num1+((s[i]-0x30)*multi);
                multi=multi*10;
            }
            else if (!beforeS)
            {
                num2=num2+((s[i]-0x30)*multi);
                multi=multi*10;
            }
        }
        if(s[i]==0x20)
        {
            afterSpace=true;
        }
    }
    const char* resultp= "worng input";
    if(sing==0x70){
        resultp=toString(num1+num2,10);}
    else if(sing==0x6d){
        resultp=toString(num1*num2,10);}
    else if(sing==0x73){
        resultp=toString(num1-num2,10);}
    else if(sing==0x64){
        resultp=toString(num1/num2,10);}
       
   
    kprint(resultp);
    



}

char CommandBuffer[128];
void findCommand(){
    SetCursorPosRaw(CommandCursor);
    char* c = (char*)(0xB8000 + 2 * 1920);
	int i;
	for(i = 0; i < 2000 - CursorPos; i += 1)
		CommandBuffer[i] = *(c + 2 * i);
	CommandBuffer[i] = 0;
}


bool CheckCMD(void(*f)(const char*), const char* command){
    bool res = false;
    memrec();
    if(StringStartsWith(CommandBuffer, command)) {
        f(strDecapitate(CommandBuffer, strLen(command)));
        res = true;
    }
    memunrec();
    return res;
}

void parseCommand(){
    findCommand();
         if(CheckCMD(helpCMD, "help")){;}
    else if (CheckCMD(kprint, "echo ")){currentTask = "echo";}
    else if (CheckCMD(printUsedMem, "usedmem")){;}
    else if (CheckCMD(clearCMD, "clear")){;}
    else if (CheckCMD(DarkMode, "dark")){;}
    else if (CheckCMD(calcCMD, "calc")){calc(CommandBuffer);}
    else {kprint("\""); kprint(CommandBuffer); kprint("\" is not a command");}
    kprint("\n");
    CommandCursor = CursorPos;
    ClrLine(24);
    //SetCursorPosRaw(1920);
    refreshShell();
}


