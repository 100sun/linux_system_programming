# Ⅱ. file I/O

function(2)

## library

#### 0. <unistd.h>

filedes

#### 1. <sys/stat.h> 2. <sys/types.h>

&emsp; &emsp; off_t&emsp; &emsp; &emsp; &emsp; <b>st_size</b><br/>
&emsp; &emsp; mode_t&emsp; &emsp; &emsp; <b>st_mode</b><br/>

#### 2. <fcntl.h>

oflag

#### 3. <unistd.h>

filedes

<hr/>

## IO

### int open(const char* pathname, int oflag, mode_t mode); 

1, 2, 3

### int close(int filedes); 

3

### int creat(const char* pathname, mode_t mode); 

1, 2, 3

``` 
fd = open(filename, O_RDONLY);
close(fd);
``` 
``` 
fd = open(filename, O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0666);
fd = creat(filename, 0666);
``` 

<hr/>

## OFFSET

### off_t lseek(int filedes, off_t offset, int whence);

0, 2, 4

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

0

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

### 1.<sys/stat.h> 2.<sys/types.h>

&emsp; &emsp; mode_t&emsp; &emsp; &emsp; <b>st_mode</b><br/>

&emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; * S_IR(RWXU)<br/>
&emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; &emsp; * S_IF(MT), S_IS(DIR)

&emsp; &emsp; off_t&emsp; &emsp; &emsp; &emsp; <b>st_size</b><br/>

&emsp; &emsp; time_t&emsp; &emsp; &emsp; &emsp; <b>st_mtime</b><br/>

### 3.<unistd.h>

filedes

<hr/>

## STAT

### int stat(const char *restrict pathname, struct stat *restrict buf); 

1, 2, 3

``` 
(statbuf.st_mode & S_IFMT) == S_IFREG; // mode & S_IFMT == S_IF~
S_ISDIR(statbuf.st_mode); // S_IS~(mode)
// ~ : REG, DIR, BLK, CHR, FIFO, SOCK, LNK
```

### mode_t umask(mode_t cmask); 

1, 2

``` 
prev_cmask = umask(0066); // = 0 
// if the mode was 0666, then it would change to 0600
```

### int utime(const char* pathname, const struct utimbuf *times); 

2, <utime.h>

``` 
utime(fname, &time_buf); // st_atime -> actime, st_mtime -> modtime
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

remove(3) ⊂ <stdio.h>

### int rename(const char* oldname, const char *newname); 

rename(2) ⊂ <stdio.h>

``` 
unlink(fname); // link count --;
// fname1 removed but the memory of fname1 still exists while hardlink_fname pointing
remove(dir); // link count --;
rename(hardlink_fname, fname);

```

# Ⅲ. directory I/O

## function(3) : <dirent.h>

##### <sys/types.h>

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

function(3)

* success -> return 0
* fail -> return EOF => [ERROR](#ERROR)

(except from [OPEN](#OPEN) and [setbuf](#BUFFER))

## function(3) : <stdio.h>

### BUFFER

#### void setbuf(FILE *fp, char* buf); 

set buffer of fp

#### int fflush(FILE *fp); 

flush a buffer of fp and print it immediately to fp

``` 
setbuf(stdout, buf); // buffer of stdout = buf -> by line (_IOLBF)
setbuf(stdout, NULL); // release buf (_IONBF)
```

<hr/>

### OFFSET

``` 
fseek(fp, 0, SEEK_END);
fsize = ftell(fp);
```

<hr/>

### I/O

#### FILE* fopen(const char* pathname, mode_t mode); 

##### FILE* fdopen(int fd, mode_t mode); 

#### FILE* freopen(const char* pathname, mode_t mode, FILE* fp); 

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

<hr/><hr/>

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

<hr/><hr/>

``` 
while(!fgets(buf, BUF_SIZE, stdin) != NULL) // get \n
    if(fputs(buf, stdout) == EOF) // \n would be print 
        exit(1);
```