# Ⅴ. process

function(2): <unistd.h><br/>
function(3): <setjmp.h>

## EXIT

#### <stdlib.h>

### void exit(int status); 

#### <unistd.h>

### void _exit(int status); 

``` 
exit(0); // print the buffer and termination (std IO buffer flushed) 
// 0 
_exit(0); // print nothing and forcibly termination (std IO buffer not flushed) 
```

<hr/>

## GOTO

#### <setjmp.h>

env should be a global var ⊃ register var, local var

### int setjmp(jump_buf env); 

called by itself : return 0
called by longjmp : return !0

### void longjmp(jump_buf env, int val); 

``` 
if(setjmp(env) != 0){
    // register var, local var would be same but volatile var would be changed.
    // when called by longjmp, return value would be 1.
}
longjmp(env, 1);
```

<hr/>

## RETURN PID

#### <unistd.h>

#### <sys/types.h>

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

#### <unistd.h>

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
