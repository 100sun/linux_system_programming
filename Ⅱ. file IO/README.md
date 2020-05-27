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
fd = open(filename, O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0666);
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

0

``` 
fd2 = dup(fd1); // copy fd1
dup2(fd, 1); // return 1 
// 1(stdout) => fd
newfd = dup2(1, 4); // return 4 
// 4 => 1(stdout)
```
