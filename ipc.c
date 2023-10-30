// TODO: add the appropriate header files here
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>


/**************************************************************
 *  ipc_create - creates a shared memory object called lab2 and
 *               returns a char pointer to the memory shared
 *               memory object.
 * 
 *  size - is the size of the memory object to create.
 *   
 ***************************************************************/
char* ipc_create(int size){
    /* shared memory file descriptor */
    int fd;
    /* pointer to shared memory obect */
    char* ptr;
    
    fd = shm_open("lab2",O_CREAT | O_RDWR, 0666);
    if(fd == -1){
        exit(1);
    }

    if(ftruncate(fd,size) == -1){
        close(fd);
        exit(1);
    }

    ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr ==MAP_FAILED){
        close(fd);
        exit(1);
    }
    close(fd);
    // TODO: create the shared memory object called lab2

    // TODO: configure the size of the shared memory object 

    // TODO: memory map the shared memory object */

    return ptr;
}


/**************************************************************
 * ipc_close - closes the ipc communication channel that was
 *             created with ipc_create.
 * 
 **************************************************************/
void ipc_close(){
    shm_unlink("lab2");
}