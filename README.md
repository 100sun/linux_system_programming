# LINUX SYSTEM PROGRAMMING

each folder has its own README.md

<hr>

### memorizing tip

sth similar open() : require "mode" <br/>
sth similar get() : require "buf"

## Ⅱ. file IO

### subtitles

IO, offset, RW, duplicate

### key

fildes

### function

open, close, creat | lseek | read, write | dup, dup2
<hr>

## Ⅲ-1. file attribute

### subtitles

stat, unistd, link

### key

stat, utimebuf

### function

stat, umask, utime, chmod | chown, access | link, unlink, symlink, remove, rename
<hr>

## Ⅲ-2. directory IO

### subtitles

function(2), function(3)

### key

DIR, dirent

### library

<dirent.h>

### function

opendir, readdir, closedir | mkdir, rmdir, chdir, getcwd
<hr>

## Ⅳ. STD file IO

### library

<stdio.h>

### key

FILE 

### subtitles

buffer, offset, error, file/char/char*/bin IO  

### function

setbuf, setvbuf, fseek, ftell | fopen, fdopen, freopen, fclose | ferror, feof | fgetc, getchar, ungetc, fputc, putchar | fgets, gets, fputs, puts | fread, fwrite
<hr>

## Ⅴ. process

### subtitles

exit, goto, pid, create child process

### key

jump_buf

### function

exit, _exit | setjmp, longjmp | fork
