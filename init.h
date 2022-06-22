#include <linux/limits.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
//headers for auto-completion.
#include <readline/readline.h>
#include <readline/history.h>

typedef struct{
    char host[HOST_NAME_MAX];
    char uname[LOGIN_NAME_MAX];
}user;

/***Low level temrinal manipulation not in use. 
struct termios term; 
***/
user cur_user;

void init(void);
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
void lsh_loop(void);
int lsh_cls(char **agrs);
char **lsh_split_line(char *line);
char *lsh_read_line(void);
int lsh_launch(char **args);
int lsh_exit(char **args);
int lsh_help(char **args);
int lsh_cd(char **args);
int lsh_num_builtins(void);
void *t_exec(void *p); 

void init()
{
    gethostname(cur_user.host, HOST_NAME_MAX);
    getlogin_r(cur_user.uname, LOGIN_NAME_MAX);

    char cdir[PATH_MAX];
    if(getcwd(cdir, PATH_MAX) == NULL)
    {
        fprintf(stderr, "lsh: error getting working dir.\n");
    }

    rl_bind_key('\t', rl_complete);
}