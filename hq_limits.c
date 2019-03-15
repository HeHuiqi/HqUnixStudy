#include "apue.h"
#include <limits.h>
#include <sys/param.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif
#define OPEN_MAX_GUESS 256

long open_max(void){
    if(openmax == 0){
        errno = 0;
    }
    return openmax;
}

static long posix_version = 0;
static long xsi_version = 0;
#define PATH_MAX_GUESS 1024

char * path_alloc(size_t *sizep){
    char *ptr;
    size_t size;

    if (posix_version == 0) {
        posix_version = sysconf(_SC_VERSION);
    }
    if (xsi_version == 0) {
        xsi_version = sysconf(_SC_XOPEN_VERSION);
    }
    if (pathmax == 0 ) {
        errno = 0;
        pathmax = pathconf("/", _PC_PATH_MAX);
         if ( pathmax < 0){
            if (errno == 0) {
                pathmax = PATH_MAX_GUESS;
            }else{
                hq_err_sys("pathconf error for _PC_PATH_MAX");
            }
        }else{
            pathmax++;
        }
    }
    if (posix_version < 200112L && (xsi_version <4)) {
        size = pathmax + 1;
    }else{
        size = pathmax;
    }

    ptr = malloc(size);
    if (ptr == NULL)
    {
        hq_err_sys("malloc error for pathname");
    }

    if (sizep != NULL) {
        *sizep = size;
    }
    return ptr;
}
void limit_test(){
    long opm = open_max();
    printf("openmax--%ld\n", opm);
    int bfs = BUFSIZ;
    int mpl = MAXPATHLEN;
    printf("BUFSIZ--%d\n", bfs);
    printf("MAXPATHLEN--%d\n", mpl);
}
int main(int argc, char const *argv[]){

    limit_test();

    return 0;
}
