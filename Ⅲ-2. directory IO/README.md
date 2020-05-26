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
