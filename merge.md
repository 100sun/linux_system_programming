# Ⅱ. file I/O

function(2)

## library

#### 0. <unistd.h>

filedes

#### 1. <sys/stat.h> 2. <sys/types.h>

&emsp; &emsp; off_t&emsp; &emsp; &emsp; &emsp; <b>st_size</b><br/>
&emsp; &emsp; mode_t&emsp; &emsp; &emsp; <b>st_mode</b><br/>

#### 2. <fcntl.h>

oflag, whence

<hr/>

## IO

### int open(const char* pathname, int oflag, mode_t mode); 

0, 1, 2

### int close(int filedes); 

0

### int creat(const char* pathname, mode_t mode); 

0, 1, 2

``` 
fd = open(filename, O_RDONLY);
close(fd);
``` 
``` 
fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
fd = creat(filename, 0666);
``` 

<hr/>

## OFFSET

### off_t lseek(int filedes, off_t offset, int whence);

0, 2

``` 
lseek(fd,(off_t)0, SEEK_SET); // move the offset of the file to the beginning of the file
lseek(fd, (off_t)150000, SEEK_CUR); // move the offset of the file 
```

``` 
fd = open(filename, O_RDWR | O_APPEND, S_IRWXU | S_IRUSR); // to write appending the file
lseek(fd, (off_t)0, SEEK_END); // to write appending the file
```

``` 
current_offset = lseek(fd, (off_t)0, SEEK_CUR);
file_size = lseek(fd, (off_t)0, SEEK_END);
```

<hr/>

## R/W

### ssize_t read(int filedes, void* buf, size_t bytes); 

0

### ssize_t write(int filedes, void* buf, size_t bytes); 

0

``` 
length = read(0, buf, BUFFER_SIZE); // 0 == stdin
write(1, buf, length); // 1 == stdout
```

``` 
while((length = read(fd1, (char*)&record, sizeof(record)) > 0)
    write(fd2, (char*)&record, sizeof(record));
```

<hr/>

## DUPLICATE 

### int dup(int filedes); 

0

### int dup2(int filedes, int filedes2); 

: this is like redirection of printing stream of the file 
0

``` 
fd2 = dup(fd1); // copy fd1
dup2(fd, 1); // return 1 
// 1(stdout) => fd
newfd = dup2(1, 4); // return 4 
// 4 => 1(stdout)
```

# Ⅲ-1. file attribute

function(2)

## key

### stat

&emsp; &emsp; mode_t&emsp; &emsp; &emsp; <b>st_mode</b><br/>

&emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; * S_I(RWX)(USR/GRP/OTH)

&emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; * S_IR(RWXU)<br/>
&emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; * S_IF(MT), S_IS(DIR)

##### |= (on) &=~ (off) ^= (mask)

&emsp; &emsp; off_t&emsp; &emsp; &emsp; &emsp; <b>st_size</b><br/>

&emsp; &emsp; time_t&emsp; &emsp; &emsp; &emsp; <b>st_mtime</b><br/>

### utimebuf

actime, modtime

## library

### 1.<sys/stat.h> 2.<sys/types.h>

### 3.<unistd.h>

<hr/>

## STAT

### int stat(const char *restrict pathname, struct stat *restrict buf); 

### int lstat(const char *restrict pathname, struct stat *restrict buf); 

(== stat) except that if pathname is a symbolic link, then it returns information about the link itself.

1, 2, 3

``` 
stat(argv[1], &statbuf);
size = statbuf.st_size;
intertime = statbuf.st_mtime;
```

``` 
lstat(argv[1], &statbuf);
(statbuf.st_mode & S_IFMT) == S_IFREG; // mode & S_IFMT == S_IF~
S_ISDIR(statbuf.st_mode); // S_IS~(mode)
// ~ : REG, DIR, BLK, CHR, FIFO, SOCK, LNK
```

### mode_t umask(mode_t cmask); 

1, 2

``` 
prev_cmask = umask(0066);  
// if the mode was 0666, then the mask would change to 0600, and also it would return 0666.
```

### int utime(const char* pathname, const struct utimbuf *times); 

2, <utime.h>

``` 
utime(fname, &time_buf); // st_atime(when open, or access) -> actime, st_mtime(modified) -> modtime
utime(fname, NULL); // st_atime -> current time, st_mtime -> current time
``` 

### int chmod(const char* pathname, mode_t mode); 

1

``` 
statbuf.st_mode &= ~ (S_IXGRP | S_IXOTH);
chmod(fname, statbuf.st_mode); // rwxrwxrwx => rwxrw-rw-
```

<hr/>

## UNIXSTD

### int chown(const char* pathname, uid_t owner, gid_t group); 

``` 
chown(fname, 501, 300); // change st_uid, st_gid
```

### int access(const char* pathname, int mode); 

``` 
access(fname, F_OK); // file existence
access(fname, 1 | 2 | 4); // X W R
``` 

<hr/>

## LINK

### int link(const char* existingpath, const char* newpath); 

### int symlink(const char* actualpath, const char* sympath); 

``` 
link(fname, hardlink_fname); // make a new hardlink pointing inode of "fname"
symlink(fname, symlink_fname); // make a new symlink pointing FileTable of "fname"
```

### int unlink(const char* pathname); 

### int remove(const char* pathname); 

: can access directory not only in root user unlink "unlink(2)"<br/>
remove(3) ⊂ <stdio.h>

### int rename(const char* oldname, const char *newname); 

rename(2) ⊂ <stdio.h>

``` 
unlink(fname); // link count --;
// fname1 removed but the memory of fname1 still exists while hardlink_fname pointing
remove(dir); // link count --;
rename(hardlink_fname, fname);

```

# Ⅲ-2. directory I/O

## key

### DIR

### dirent

d_name, d_ino

## function(3)

##### <sys/types.h>

### DIR* opendir(const char* name); 

### struct dirent* readdir(DIR *dp); 

### int closedir(DIR *dp); 

``` 
DIR* dirp = opendir(dname);
struct dirent *dentry = readdir(dp);
// dentry->d_name == dname
closedir(dp);
```

``` 
while((dentry = readdir(dirp)) != NULL){
	if(dentry->d_ino == 0)
		continue;
	memcpy(filename, dentry->d_name, DIRECTORY_SIZE);
```

<hr/>

## function(2)

##### <sys/stat.h>

##### <sys/types.h>

### int mkdir(const char* pathname, mode_t mode); 

<hr/>

##### <unistd.h>

### int rmdir(const char* pathname); 

### int chdir(const char* pathname); 

### char* getcwd(char* buf, size_t size); 

``` 
chdir("/etc"); // change directory
getcwd(cwd, PATH_MAX); // cwd == "/etc"
```

# Ⅳ standard file I/O

## library

<stdio.h>

## key

FILE 

## function(3)

* success -> return 0
* error or EOF -> return EOF(c) or NULL(s) => [ERROR](#ERROR) to check if it is error or EOR <br/>

(except from [OPEN](#OPEN) and [setbuf](#BUFFER))

### BUFFER

#### void setbuf(FILE *fp, char* buf); 

##### int setvbuf(FILE *fp, char* buf, int mode, size_t size); 

set buffer of fppowe

#### int fflush(FILE *fp); 

flush a buffer of fp and print it immediately to fp

``` 
setbuf(fp, buf); // default : _IOFBF
setbuf(stdout, NULL); // release buf (_IONBF)
```

``` 
if(isatty(fd)) 
		mode = _IOLBF;
setvbuf(fp, buf, mode, size);
```

<hr/>

### OFFSET

``` 
fseek(fp, 0, SEEK_END);
fsize = ftell(fp);
rewind(fp); // == fseek(fp, 0, SEEK_SET);
```

<hr/>

### I/O

#### FILE* fopen(const char* pathname, mode_t mode); 

##### FILE* fdopen(int fd, mode_t mode); 

#### FILE* freopen(const char* pathname, mode_t mode, FILE* fp); 

#### FILE* fclose(FILE* fp); 

``` 
newfp = fopen(fname, "w+"); // O_RDWR | O_CREAT | O_TRUNC
updatingfp = fopen(fname, "a+"); // O_RDWR | O_CREAT | O_APPEND
originalfp = freopen(fname, "w", stdout); // write in stdout -> fname
fclose(fp);
```

<hr/>

### ERROR

#### int ferror(FILE* fp); 

#### int feof(FILE* fp); 

<hr/><hr/>

### char I/O 

#### int fgetc(FILE *fp); 

(= getc) get character from fp

#### int getchar(); 

get character from stdin

#### int ungetc(int c, FILE *fp); 

push c back to stream

<hr/><hr/>

#### int fputc(int c, FILE *fp); 

(= putc) print c to fp

#### int putchar(int c); 

print c to stdout

``` 
while(!feof(fp)){

    fputc(c, stdout);

    if(ferror(fp)){
        clearerr(fp);
    }

    c = fgetc(fp);
}
```

<hr/>

### char* IO 

#### int fgets(char* buf, int n, FILE *fp); 

get at most n-1 char* from fp and stores them into buf until '\n'<br/>
(include \n)

#### int gets(char* buf); 

get char* from stdin and stores them into buf until '\n'<br/>
(exclude \n)

<hr/><hr/>

#### int fputs(const char* str, FILE *fp); 

print char* to fp until '\n'<br/>
(exclude \n)

#### int puts(const char* str); 

print char* to stdout until '\n'<br/>
(include \n)

``` 
while(!fgets(buf, BUF_SIZE, stdin) != NULL) // get \n
    if(fputs(buf, stdout) == EOF) // \n would be print 
        exit(1);
```

``` 
while((character = fgetc(fp)) != EOF && isdigit(character)) // => number
    number = 10 * number + character - 48; // abstract the number 0 (48 in ASCII code)
``` 

<hr/>

### binaray I/O

#### size_t fread(&emsp; &emsp; void* ptr, size_t, size_t nmemb, FILE* fp); 

#### size_t fwrite(const void* ptr, size_t, size_t nmemb, FILE* fp); 

``` 
fwrite(&mystruct, sizeof(struct mystruct), 1, fp); 
fread(&twostructs, sizeof(struct mystruct), 2, fp); // get 2*sizeof(mystruct) bytes and store the two items at ptr 
``` 

### format I/O

```

scanf("%[^\n]", tmp); 
printf("%0X "/%02hhX"/ \n", *p, *p); 
// %[필드너비][길이 수정자][변환형식]

``` 
# Ⅴ. process

function(2): <unistd.h><br/>
function(3): <setjmp.h>

## EXIT

##### <stdlib.h>

### void exit(int status); 

##### <unistd.h>

### void _exit(int status); 

``` 
exit(0); // print the buffer and termination (std IO buffer flushed) 
// 0 
_exit(0); // print nothing and forcibly termination (std IO buffer not flushed) 
```

<hr/>

## GOTO

##### <setjmp.h>

env should be a global var ⊃ register var, local var

### int setjmp(jump_buf env); 

called by itself : return 0
called by longjmp : return !0

### void longjmp(jump_buf env, int val); 

``` 
if(setjmp(env) != 0){
    // : when called by longjmp (return value == 1(the value of "val" param from longjmp))
    // register var, local var would be same but volatile var would be changed.
}
longjmp(env, 1);
```

<hr/>

## RETURN PID

##### <unistd.h>

##### <sys/types.h>

``` 
process_id = getpid();
parent_process_id = getppid();
```

``` 
real_user_id = getuid();
effective_user_id = geteuid(); 
```

``` 
real_group_id = getgid();
effective_group_id = getegid(); 
```

<hr/>

## CREATE CHILD PROCESS

##### <unistd.h>

### pid_t fork(void); 

return

* 0: child process
* >0(pid of its child) : parent process
* -1: error

``` 
write(STDOUT_FILENO, ~, ~); // 1
// no buffering
printf("~");                // 2
// can be buffered unless stdout

if((pid = fork()) < 0){ // 3
    // error            
}
else if(pid == 0){      
    // child process    // 4
}
else {
    // parent process   // 5
}
printf("~");            // 6
exit(0);                // 7

// stdout&setbuf : 1->2->3->4->6->7-> 3->5->6->7
// others : 1->2->3->4->6->7-> 3->5->6&2->7
```

<hr/>
