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
