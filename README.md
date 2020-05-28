# LINUX SYSTEM PROGRAMMING

each folder has its own README.md

<hr>

### memorizing tip

sth similar open() : require "mode" <br/>
sth similar get() : require "buf"

## Ⅱ. [file IO](https://github.com/100sun/linux_system_programming/tree/master/%E2%85%A1.%20file%20IO)

### subtitles

IO, offset, RW, duplicate

### key

fildes

### function

open, close, creat | lseek | read, write | dup, dup2
<hr>

## [Ⅲ-1. file attribute](https://github.com/100sun/linux_system_programming/tree/master/%E2%85%A2-1.%20file%20attribute)

### subtitles

stat, unistd, link

### key

stat, utimebuf

### function

stat, umask, utime, chmod | chown, access | link, unlink, symlink, remove, rename
<hr>

## [Ⅲ-2. directory IO](https://github.com/100sun/linux_system_programming/tree/master/%E2%85%A2-2.%20directory%20IO)

### subtitles

function(2), function(3)

### key

DIR, dirent

### library

<dirent.h>

### function

opendir, readdir, closedir | mkdir, rmdir, chdir, getcwd
<hr>

## [Ⅳ. STD file IO](https://github.com/100sun/linux_system_programming/tree/master/%E2%85%A3.%20STD%20file%20IO)

### library

<stdio.h>

### key

FILE 

### subtitles

buffer, offset, error, file/char/char*/bin IO  

### function

setbuf, setvbuf, fseek, ftell | fopen, fdopen, freopen, fclose | ferror, feof | fgetc, getchar, ungetc, fputc, putchar | fgets, gets, fputs, puts | fread, fwrite
<hr>

## [Ⅴ. process](https://github.com/100sun/linux_system_programming/tree/master/%E2%85%A4.%20process)

### subtitles

exit, goto, pid, create child process

### key

jump_buf

### function

exit, _exit | setjmp, longjmp | fork
