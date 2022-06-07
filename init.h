#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//headers for auto-completion.
#include <readline/readline.h>
#include <readline/history.h>

typedef struct{
    char host[HOST_NAME_MAX];
    char uname[LOGIN_NAME_MAX];
}user;

/***Low level temrinal manipulation
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
char *get_dir();

void init()
{
    gethostname(cur_user.host, HOST_NAME_MAX);
    getlogin_r(cur_user.uname, LOGIN_NAME_MAX);

    char *home = getenv("HOME"); 
    chdir(home);

    rl_bind_key('\t', rl_complete);
}

char *get_dir()
{
    char *path = (char *)malloc(sizeof(char) * PATH_MAX);
    getcwd(path, PATH_MAX);
    return path;
}