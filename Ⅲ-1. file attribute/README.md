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
