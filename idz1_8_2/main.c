/* Two independent processes of different programs, named pipes.
 *
 * Develop a console application that uses named pipes
 * and provides interaction according to the following scheme:
 * • the first process reads text data from a given file
 *   and transmits it to the second process through a named pipe;
 * • the second process processes data in accordance with the task
 *   and transmits the processing result through a named pipe
 *   back to the first process;
 * • the first process outputs data to the specified file. */

/* 9. Develop a program that “reverses in place” a given ASCII string of
 * characters after it has been completely written to the buffer of the
 * processing process (without copying the string to another buffer).
 * The formation of the required buffer in the case of reading a line in
 * parts is carried out dynamically. That is, present it either as a list
 * of dynamically generated partial strings, or when adding the next
 * fragment, select a longer section, transferring data from the
 * previously allocated one. In this case, it is possible to allocate
 * memory for a string in fragments whose size is 10 times larger than
 * the size of the buffer used to transmit data through the channel. */

//-----------------------------------------------------------------------------
//  standard headers
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  global variables
//-----------------------------------------------------------------------------
char *fifo1_n = "/tmp/idz1_8_1";    //  fifo name for process-1 & process-2
char *fifo2_n = "/tmp/idz1_8_2";    //  fifo name for process-2 & process-3
const size_t buff_size = 5000;
char buff[5000];
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  global functions
//-----------------------------------------------------------------------------
void usage();
void create_fifo();
void mission_2();
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 * Main program function
 */
//-----------------------------------------------------------------------------
int main(int argc, char **argv) {
    if (argc != 1) {
        usage();
    }
    create_fifo();
    mission_2();
    return 0;
}

//-----------------------------------------------------------------------------
/**
 * Print usage
 */
//-----------------------------------------------------------------------------
void usage() {
    printf("Usage:\n");
    printf("\tidz1_8_2\n");
    exit(0);
}
void break_on_cond_1(int _cond, char* _s1, char* _s2, int _errno) {
    if (_cond) {
        fprintf(stderr, _s1, _s2, _errno, strerror(_errno));
        exit(1);
    }
}
void break_on_cond_2(int _cond, char* _s1, int _errno) {
    if (_cond) {
        fprintf(stderr, _s1, _errno, strerror(_errno));
        exit(1);
    }
}

//-----------------------------------------------------------------------------
/**
 * Create fifos
 */
//-----------------------------------------------------------------------------
void create_fifo() {
    int rc1, rc2;
    //  create fifo1
    rc1 = mkfifo(fifo1_n, 0666);
    break_on_cond_1(rc1 != 0 && errno != EEXIST, "mkfifo(%s) error: %i, %s", fifo1_n, errno);
    //  create fifo2
    rc2 = mkfifo(fifo2_n, 0666);
    break_on_cond_1(rc2 != 0 && errno != EEXIST, "mkfifo(%s) error: %i, %s", fifo2_n, errno);
}

//-----------------------------------------------------------------------------
/**
 * The second process processes the data in accordance with the task option
 * and transmits the processing result through an named channel to the third process
 */
//-----------------------------------------------------------------------------
void mission_2() {
    printf("%s: started.\n", __func__);
    sleep(1);
    //  open input fifo
    int fifo1_d = open(fifo1_n, O_RDONLY);
    break_on_cond_1(fifo1_d < 0, "fifo open(%s) error: %i. %s\n", fifo1_n, errno);
    printf("%s: fifo open(%s) ok\n", __func__, fifo1_n);
    //  open output fifo
    int fifo2_d = open(fifo2_n, O_WRONLY);
    break_on_cond_1(fifo2_d < 0, "fifo open(%s) error: %i. %s\n", fifo2_n, errno);
    printf("%s: fifo open(%s) ok\n", __func__, fifo2_n);
    //  read data from fifo
    ssize_t data_len = read(fifo1_d, buff, buff_size);
    break_on_cond_1(data_len < 0, "fifo read(%s) error: %i. %s\n", fifo1_n, errno);
    printf("%s: fifo read(%s) ok. Data length = %zi\n", __func__, fifo1_n, data_len);
    //  close fifo
    close(fifo1_d);
    printf("%s: fifo close(%s) ok\n", __func__, fifo1_n);
    //  rework data
    for (ssize_t i = 0; i < data_len / 2; ++i) {
        char chr = buff[i];
        buff[i] = buff[data_len - 1 - i];
        buff[data_len - 1 - i] = chr;
    }
    //  write buffer to fifo
    ssize_t send_len = write(fifo2_d, buff, data_len);
    break_on_cond_1(send_len < 0, "fifo write(%s) error: %i. %s\n", fifo2_n, errno);
    printf("%s: fifo write(%s) ok. Data length = %zi\n", __func__, fifo2_n, send_len);
    //  close fifo
    close(fifo2_d);
    printf("%s: fifo close(%s) ok\n", __func__, fifo2_n);
    //
    printf("%s: finished.\n", __func__);
}
