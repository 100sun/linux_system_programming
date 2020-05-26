# file I/O

function(2)

## library

### <sys/types.h>

mode, whence ...

### <sys/stat.h>

stat : off_t, mode_t, time_t

### <fcntl.h>

oflag

### <unistd.h>

filedes

## function(2)

### int open(const char* pathname, int oflag, mode_t mode); 

### int close(int filedes); 

### int creat(const char* pathname, mode_t mode); 

``` 
fd = open(filename, O_RDONLY);
close(fd);
``` 
``` 
fd = open(filename, O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0666);
fd = creat(filename, 0666);
``` 

<hr/>

### off_t lseek(int filedes, off_t offset, int whence);

``` 
lseek(fd,(off_t)0, SEEK_SET); // move the offset of the file to the beginning of the file
lseek(fd, (off_t)150000, SEEK_CUR); // move the offset of the file 
```

``` 
fd = open(filename, O_RDWR | O_APPEND, S_IRWXU | S_IRUSR);
lseek(fd, (off_t)0, SEEK_END); // to write appending the file
```

``` 
current_offset = lseek(fd, (off_t)0, SEEK_CUR);
file_size = lseek(fd, (off_t)0, SEEK_END);
```

<hr/>

### ssize_t read(int filedes, void* buf, size_t bytes); 

### ssize_t write(int filedes, void* buf, size_t bytes); 

``` 
length = read(0, buf, BUFFER_SIZE); // 0 == stdin
write(1, buf, length); // 1 == stdout
```

``` 
while((length = read(fd1, (char*)&record, sizeof(record)) > 0)
    write(fd2, (char*)&record, sizeof(record));
```

<hr/>

### int dup(int filedes); 

### int dup2(int filedes, int filedes2); 

``` 
fd2 = dup(fd1); // copy fd1
dup2(fd, 1); // = 1 
// 1(stdout) <==> fd
newfd = dup2(1, 4); // = 4 
// 4 <==> 1(stdout)
```

# Ⅲ. file attribute

function(2)

## library

### <sys/stat.h> <sys/types.h>

#### stat

off_t <b>st_size</b><br/>
mode_t <b>st_mode</b><br/>

* S_IR(RWXU)
* S_IF(MT), S_IF(DIR)

time_t <b>st_mtime</b><br/>

### <fcntl.h>

oflag

### <unistd.h>

filedes

## function(2)

### int stat(const char *restrict pathname, struct stat *restrict buf); 

``` 
(statbuf.st_mode & S_IFMT) == S_IFREG; // mode & S_IFMT == S_IF~
S_ISDIR(statbuf.st_mode); // S_IS~(mode)
// ~ : REG, DIR, BLK, CHR, FIFO, SOCK, LNK
```

### int access(const char* pathname, int mode); 

``` 
access(fname, F_OK); // file existence
access(fname, 1 | 2 | 4); // X W R
``` 

### int utime(const char* pathname, const struct utimbuf *times);

```

utime(fname, &time_buf); // st_atime -> actime, st_mtime -> modtime
utime(fname, NULL); // st_atime -> current time, st_mtime -> current time

``` 

<hr/>

### mode_t umask(mode_t cmask); 

``` 
prev_cmask = umask(0066); // = 0 
// if the mode was 0666, then it would change to 0600
```

### int chmod(const char* pathname, mode_t mode); 

``` 
statbuf.st_mode &= ~ (S_IXGRP | S_IXOTH);
chmod(fname, statbuf.st_mode); // rwxrwxrwx => rwxrw-rw-
```

### int chown(const char* pathname, uid_t owner, gid_t group); 

``` 
chown(fname, 501, 300); // change st_uid, st_gid
```

<hr/>

### int link(const char* existingpath, const char* newpath); 

### int symlink(const char* actualpath, const char* sympath); 

``` 
link(fname, hardlink_fname); // make a new hardlink pointing inode of "fname"
symlink(fname, symlink_fname); // make a new symlink pointing FileTable of "fname"
```

### int unlink(const char* pathname); 

### int remove(const char* pathname); 

### int rename(const char* oldname, const char *newname); 

``` 
unlink(fname); // link count --;
// fname1 removed but the memory of fname1 still exists while hardlink_fname pointing
remove(dir); // link count --;
rename(hardlink_fname, fname);

```

# Ⅲ. directory I/O

function(2)

## library

### <dirent.h>

DIR

## function(2)

### int mkdir(const char* pathname, mode_t mode); 

### int rmdir(const char* pathname); 

<hr/>

### DIR *opendir(const char* name); 

### struct dirent *readdir(DIR *dp); 

### int closedir(DIR *dp); 

``` 
DIR* dp = opendir(dname);
struct dirent *dentry = readdir(dp);
// dentry->d_name == dname
closedir(dp);
```

<hr/>

### int chdir(const char* pathname); 

### char* getcwd(char* buf, size_t size); 

``` 
chdir("/etc"); // change directory
getcwd(cwd, PATH_MAX); // cwd == "/etc"
```

# Ⅳ standard file I/O

function(3)

* success -> return 0
* fail -> return EOF => [ERROR](#ERROR)

(except from [OPEN](#OPEN) and [setbuf](#BUFFER))

## library

### <stdio.h>

FILE

## function(3)

### BUFFER

#### void setbuf(FILE *fp, char* buf); 

set buffer of fp

#### int fflush(FILE *fp); 

flush a buffer of fp and print it immediately to fp

``` 
setbuf(stdout, buf); // buffer of stdout = buf -> by line (_IOLBF)
setbuf(stdout, NULL); // release buf (_IONBF)
```

### OPEN

#### FILE* fopen(const char* pathname, mode_t mode); 

#### FILE* freopen(const char* pathname, mode_t mode, FILE* fp); 

#### FILE* fdopen(int fd, mode_t mode); 

#### FILE* fclose(FILE* fp); 

``` 
fp = fopen(fname, "w+"); // O_RDWR | O_CREAT | O_TRUNC
freopen(fname, "a+", fp); // O_RDWR | O_CREAT | O_APPEND
fclose(fp);
```

<hr/>

### ERROR

#### int ferror(FILE* fp); 

#### int feof(FILE* fp); 

<hr/>

### char I/O 

#### int getc(int c, FILE *fp); 

(= fgetc) get c from fp

#### int getchar(int c); 

get c from stdin

#### int ungetc(int c, FILE *fp); 

push c back to stream

<hr/><hr/>

#### int putc(int c, FILE *fp); 

(= fputc) print c to fp

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

get char* from fp until '\n'<br/>
(include \n)

#### int gets(char* buf); 

get char* from stdin until '\n'<br/>
(exclude \n)

<hr/><hr/>

#### int fputs(int c, FILE *fp); 

print char* to fp until '\n'<br/>
(exclude \n)

#### int puts(int c); 

print char* to stdout until '\n'<br/>
(include \n)

``` 
while(!fgets(buf, BUF_SIZE, stdin) != NULL) // get \n
    if(fputs(buf, stdout) == EOF) // \n would be print 
        exit(1);
```

<hr/>

### file attribute

``` 
fseek(fp, 0, SEEK_END);
fsize = ftell(fp);
```
