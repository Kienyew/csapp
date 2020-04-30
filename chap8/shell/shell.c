#include <stdbool.h>
#include <stdio.h>              /* fgets(), feof(), printf() */
#include <stdlib.h>             /* exit() */
#include <string.h>             /* strcmp() */
#include <signal.h>
#include <setjmp.h>
#include <errno.h>
#include <sys/types.h>          /* pid_t */
#include <sys/wait.h>           /* waitpid() */
#include <unistd.h>
#include <assert.h>

#define MAXLINE 1024
#define MAXJOBS 128
#define MAXARGS 256
#define PS1 "[kienyew]> "

typedef int jid_t;

struct LineParseResult {
    char* name;
    int argc;
    bool background;
    char** argv;
};

struct JobContext {
    pid_t pid;
    jid_t jid; /* job id */
    bool stopped;
    bool free;
};

enum JPID { ERR = -1, JID, PID, };

void eval(const char* cmdline);
void parseline(const char* line, struct LineParseResult* res);
struct JobContext* startjob(const char* name, const char* argv[], bool background);
void endjob(struct JobContext* job_ctx);
void eval_builtin(char* name);
bool is_builtin(const char* name);
void builtin(const char* name, const char* argv[]);
int parse_jpid(const char* s, jid_t* jid, pid_t* pid);
int reap_done_backgrounds();
void parse_result_free(struct LineParseResult* parse_result);

const char* builtins[] = { "quit", "jobs", "fg", "bg", NULL };
struct JobContext jobs[MAXJOBS];
struct JobContext* jobfg = NULL;
jid_t jid_counter = 0;

void sigint_handler(int sig) {
    if (jobfg == NULL || jobfg->free) return;
    kill(-jobfg->pid, SIGINT);
}

void sigtstp_handler(int sig) {
    if (jobfg == NULL || jobfg->free) return;
    jobfg->stopped = true;
    printf("[%d] %d suspended", jobfg->jid, jobfg->pid);
    kill(-jobfg->pid, SIGSTOP);
}

void sigchld_handler(int sig) {
    printf("sigchld handler\n");
}

int main(int argc, char* argv[]) {
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);

    char linebuf[MAXLINE];
    for (int i = 0; i < MAXJOBS; ++i)
        jobs[i].free = true;

    while (true) {
        printf(PS1);
        fgets(linebuf, MAXLINE, stdin);
        if (feof(stdin))
            exit(0);

        reap_done_backgrounds();
        eval(linebuf);
    }

    return 0;
}

void parseline(const char* line, struct LineParseResult* res) {
    res->argc = 0;
    char buffer[256];
    res->argv = malloc(sizeof(char*) * MAXARGS);
    int i;
    while (*line != '\n' && *line != '\0') {
        while (*line == ' ')
            ++line;

        if (*line == '\n' || *line == '\0')
            break;

        for (i = 0; *line != ' ' && *line != '\n' && *line != '\0'; ++line, ++i)
            buffer[i] = *line;

        buffer[i] = '\0';
        assert(res->argc + 1 <= MAXARGS);
        res->argv[res->argc++] = strdup(buffer);
    }

    

    if (res->argc == 0) {
        free(res->argv);
        res->name = NULL;
        res->background = false;
        res->argv = NULL;
        return;
    }

    if (strcmp(res->argv[res->argc - 1], "&") == 0) {
        res->background = true;
        free(res->argv[--res->argc]);
    } else {
        res->background = false;
    }

    res->name = strdup(res->argv[0]);
    res->argv = realloc(res->argv, sizeof(char*) * (res->argc + 1));
    res->argv[res->argc] = NULL;
    return;
}

void eval(const char* cmdline) {
    struct LineParseResult parse_result;
    parseline(cmdline, &parse_result);
    if (parse_result.argc == 0)
        return;

    if (is_builtin(parse_result.name)) {
        builtin(parse_result.name, (const char**)parse_result.argv);
        return;
    }

    startjob(parse_result.name, (const char**)parse_result.argv, parse_result.background);
    parse_result_free(&parse_result);
    return;
}
void builtin(const char* name, const char* argv[]) {
    if (strcmp("quit", name) == 0) {
        exit(0);
    }
    else if (strcmp("jobs", name) == 0) {
        for (int i = 0; i < MAXJOBS; ++i)
            if (!jobs[i].free)
                printf("[%d]\t%d\t%s\n", jobs[i].jid, jobs[i].pid, (jobs[i].stopped ? "suspended" : "running"));
    }
    else if (strcmp("fg", name) == 0) {
        jid_t jid;
        pid_t pid;
        enum JPID ret = parse_jpid(argv[1], &jid, &pid);
        if (ret == ERR) {
            fprintf(stderr, "fg: should specify either job id or process id\n");
            return;
        }
        
        for (int i = 0; i < MAXJOBS; ++i) {
            if (jobs[i].free)
                continue;

            if ((ret == JID) ? (jobs[i].jid == jid) : (jobs[i].pid == pid)) {
                pid_t rpid;
                int status;
                kill(-jobs[i].pid, SIGCONT);
                jobs[i].stopped = false;
                jobfg = &jobs[i];
                rpid = waitpid(jobs[i].pid, &status, 0);
                printf("rpid: %d\n", rpid);
                assert(rpid == jobs[i].pid);
                if (WIFEXITED(status))
                    endjob(&jobs[i]);

                return;
            }
        }

        fprintf(stderr, "fg: [%s%d] job id or process id not found\n", (ret == JID) ? "%" : "", (ret == JID) ? jid : pid);
    }
    else if (strcmp("bg", name) == 0) {
        jid_t jid;
        pid_t pid;
        enum JPID ret = parse_jpid(argv[1], &jid, &pid);
        if (ret == ERR) {
            fprintf(stderr, "bg: should specify either job id or process id\n");
            return;
        }
        
        for (int i = 0; i < MAXJOBS; ++i) {
            if (jobs[i].free) 
                continue;

            if ((ret == JID) ? (jobs[i].jid == jid) : (jobs[i].pid == pid)) {
                kill(-jobs[i].pid, SIGCONT);
                jobs[i].stopped = false;
                return;
            }
        }

        fprintf(stderr, "bg: [%s%d] job id or process id not found\n", (ret == JID) ? "%" : "", (ret == JID) ? jid : pid);
        return;
    }
}

struct JobContext* startjob(const char* name, const char* argv[], bool background) {
    struct JobContext* job_ctx = NULL;

    /* find a empty job slot and apply to it */
    for (int i = 0; i < MAXJOBS; ++i)
        if (jobs[i].free) {
            job_ctx = &jobs[i];
            job_ctx->jid = i;
            break;
        }

    assert(job_ctx != NULL);

    job_ctx->free = false;
    job_ctx->stopped = false;
    if ((job_ctx->pid = fork()) == 0) {
        setpgid(0, 0);
        int ret = execv(name, (char* const*)argv);
        if (ret < 0)
            fprintf(stderr, "command '%s' error\n", name);
        exit(1);
    }

    if (background) {
        printf("[%d] %d\n", (int)job_ctx->jid, (int)job_ctx->pid);
        return job_ctx;
    }

    int status;
    jobfg = job_ctx;
    pid_t rpid = waitpid(job_ctx->pid, &status, WUNTRACED);
    assert(rpid == job_ctx->pid);
    if (WIFEXITED(status))
        endjob(jobfg);
    else if (WIFSIGNALED(status)) {
        char buffer[256];
        sprintf(buffer, "process %d terminated by signal", job_ctx->pid);
        psignal(WTERMSIG(status), buffer);
    }

    return job_ctx;
}

void endjob(struct JobContext* job_ctx) {
   job_ctx->free = true; 
   job_ctx->stopped = false;
   if (job_ctx == jobfg)
       jobfg = NULL;
}

bool is_builtin(const char* name) {
    for (int i = 0; builtins[i] != NULL; ++i)
        if (strcmp(name, builtins[i]) == 0)
            return true;

    return false;
}


enum JPID parse_jpid(const char* s, jid_t* jid, pid_t* pid) {
    char* nptr;
    if (s == NULL)
        return ERR;

    if (*s == '%') {
        *jid = strtol(s + 1, &nptr, 10);
        return (nptr == s) ? ERR : JID;
    } else {
        *pid = strtol(s, &nptr, 10);
        return (nptr == s) ? ERR : PID;
    }

}

int reap_done_backgrounds() {
    pid_t pid;
    int status;
    int count = 0;
    while ((pid = waitpid(-1, &status, WNOHANG)) != 0) {
        if (pid == -1) {
            if (errno != ECHILD)
                perror("waitpid error in read_done_backgrounds");
            break;
        } else if (pid > 0) {
            /* normal done */
            for (int i = 0; i < MAXJOBS; ++i) {
                if (jobs[i].free)
                    continue;

                if (jobs[i].pid == pid) {
                    if (WIFEXITED(status)) {
                        printf("[%d]\t%d\tdone with exit status %d\n", jobs[i].jid, jobs[i].pid, WEXITSTATUS(status));
                    } else if (WIFSIGNALED(status)) {
                        char buffer[256];
                        sprintf(buffer, "[%d]\t%d terminated by signal %d", jobs[i].jid, jobs[i].pid, WTERMSIG(status));
                        psignal(WTERMSIG(status), buffer);
                    }

                    endjob(&jobs[i]);
                    break;
                }
            }
        }
        count ++;
    }
    return count;
}

void parse_result_free(struct LineParseResult* parse_result) {
    free(parse_result->name);
    for (int i = 0; i < parse_result->argc; ++i)
        free(parse_result->argv[i]);

    free(parse_result->argv);
}
