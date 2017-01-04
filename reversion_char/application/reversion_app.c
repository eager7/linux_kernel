#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define DEV "/dev/reversion"

int dev_file = 0;

int dev_open()
{
    if(access(DEV,F_OK)){
        FILE *fp = popen("cat /proc/devices | awk '{if($2==\"reversion\")print $1}'", "r");
        char auMajor[5] = {0};
        if(0 == fread(auMajor, 1, sizeof(auMajor), fp))
        {
            printf("fread error:%s\n", strerror(errno));
            return -1;
        }
        int iMajor = atoi(auMajor);
        printf("the device major is:%d\n", iMajor);
    
        char auCommand[256] = {0};
        snprintf(auCommand, sizeof(auCommand), "mknod /dev/reversion c %d 0", iMajor);
        printf("command:%s\n", auCommand);
        system(auCommand);
    }
    dev_file = open(DEV,O_RDWR);
    if(dev_file == -1){
        printf("open error:%s\n", strerror(errno));
        return -1;
    }

    return 0;
}

int main()
{
    dev_open(); 

    write(dev_file, "test", sizeof("test"));
    char auRead[256] = {0};
    if(read(dev_file, auRead, sizeof(auRead)) == -1){
        printf("read error:%s\n", strerror(errno));
        return -1;
    }
    printf("read:%s\n", auRead);

    return 0;
}
