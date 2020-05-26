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

``` 
while(!fgets(buf, BUF_SIZE, stdin) != NULL) // get \n
    if(fputs(buf, stdout) == EOF) // \n would be print 
        exit(1);
```
