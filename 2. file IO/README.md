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
