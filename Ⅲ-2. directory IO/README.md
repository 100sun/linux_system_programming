# Ⅲ. directory I/O

<dirent.h> : DIR

## function(3)

##### <sys/types.h>

### DIR* opendir(const char* name); 

### struct dirent* readdir(DIR *dp); 

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
