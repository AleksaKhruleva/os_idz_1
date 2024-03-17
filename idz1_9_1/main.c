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
#include <ctype.h>
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
char *input_file_name = NULL;
char *output_file_name = NULL;
char *fifo1_n = "/tmp/idz1_9_1";    //  fifo name for process-1 & process-2
char *fifo2_n = "/tmp/idz1_9_2";    //  fifo name for process-2 & process-3
char *buff;
size_t buff_size = 128;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  global functions
//-----------------------------------------------------------------------------
void break_on_cond_1(int _cond, char* _s1, char* _s2, int _errno);
void break_on_cond_2(int _cond, char* _s1, size_t _i1, int _errno);
void extract_args(int argc, char **argv);
void alloc_buff();
void create_fifo();
void mission_1();
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 * Main program function
 */
//-----------------------------------------------------------------------------
int main(int argc, char **argv) {
    extract_args(argc, argv);
    alloc_buff();
    create_fifo();
    mission_1();
    return 0;
}

//-----------------------------------------------------------------------------
/**
 * Print usage
 */
//-----------------------------------------------------------------------------
void usage() {
    printf("Usage:\n");
    printf("\tidz1_9_1 -i input_file_name -o output_file_name\n");
    exit(0);
}

//-----------------------------------------------------------------------------
/**
 * Break program on condition
 */
//-----------------------------------------------------------------------------
void break_on_cond_1(int _cond, char* _s1, char* _s2, int _errno) {
    if (_cond) {
        fprintf(stderr, _s1, _s2, _errno, strerror(_errno));
        exit(1);
    }
}
void break_on_cond_2(int _cond, char* _s1, size_t _i1, int _errno) {
    if (_cond) {
        fprintf(stderr, _s1, _i1, _errno, strerror(_errno));
        exit(1);
    }
}

//-----------------------------------------------------------------------------
/**
 * Allocate buffer
 */
//-----------------------------------------------------------------------------
void alloc_buff() {
    buff = malloc(buff_size);
    break_on_cond_2(buff == NULL, "malloc(%ul) error: %i, %s", buff_size, errno);
}

//-----------------------------------------------------------------------------
/**
 * Extract command line arguments
 * @param argc - command line arguments count
 * @param argv - command line arguments values
 * @return
 */
//-----------------------------------------------------------------------------
void extract_args(int argc, char **argv) {
    int c;
    if (argc != 5) {
        usage();
    }
    opterr = 0;
    while ((c = getopt(argc, argv, "i:o:")) != -1)
        switch (c) {
            case 'i':
                input_file_name = optarg;
                break;
            case 'o':
                output_file_name = optarg;
                break;
            case '?':
                if (optopt == 'i' || optopt == 'o')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
                exit(1);
            default:
                abort();
        }
    if (input_file_name == NULL || output_file_name == NULL) usage();
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
    remove(fifo2_n);
    rc2 = mkfifo(fifo2_n, 0666);
    break_on_cond_1(rc2 != 0, "mkfifo(%s) error: %i, %s", fifo2_n, errno);
}

//-----------------------------------------------------------------------------
/**
 *  The first process reads text data from the given file
 *  and passes it through an named pipe to the second process
 */
//-----------------------------------------------------------------------------
void mission_1() {
    printf("%s: started.\n", __func__);
    sleep(1);
    //  open output fifo
    int fifo1_d = open(fifo1_n, O_WRONLY);
    break_on_cond_1(fifo1_d < 0, "fifo open(%s) error: %i. %s\n", fifo1_n, errno);
    printf("%s: fifo open(%s) ok\n", __func__, fifo1_n);
    //  open input file
    int fd = open(input_file_name, O_RDONLY);
    break_on_cond_1(fd < 0, "file open(%s) error: %i. %s\n", input_file_name, errno);
    printf("%s: file open(%s) ok.\n", __func__, input_file_name);
    //  read input file
    ssize_t data_len;
    while ((data_len = read(fd, buff, buff_size)) != 0) {
        break_on_cond_1(data_len < 0, "file read(%s) error: %i. %s\n", input_file_name, errno);
        printf("%s: file read(%s) ok. Data length = %zi\n", __func__, input_file_name, data_len);
        //  write buffer to fifo
        ssize_t send_len = write(fifo1_d, buff, data_len);
        break_on_cond_1(send_len < 0, "fifo write(%s) error: %i. %s\n", fifo1_n, errno);
        printf("%s: fifo write(%s) ok. Data length = %zi\n", __func__, fifo1_n, send_len);
    }
    //  close file
    close(fd);
    printf("%s: file close(%s) ok\n", __func__, input_file_name);
    //  close fifo
    close(fifo1_d);
    printf("%s: fifo close(%s) ok\n", __func__, fifo1_n);
    //  open input fifo
    int fifo2_d = open(fifo2_n, O_RDONLY);
    break_on_cond_1(fifo2_d < 0, "fifo open(%s) error: %i. %s\n", fifo2_n, errno);
    //  create output file
    fd = open(output_file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    break_on_cond_1(fd < 0, "file open(%s) error: %i. %s\n", input_file_name, errno);
    printf("%s: file open(%s) ok.\n", __func__, output_file_name);
    //  read data from fifo
    while ((data_len = read(fifo2_d, buff, buff_size)) != 0) {
        break_on_cond_1(data_len < 0, "fifo read(%s) error: %i. %s\n", fifo2_n, errno);
        printf("%s: fifo read(%s) ok. Data length = %zi\n", __func__, fifo2_n, data_len);
        //  write output file
        ssize_t rc = write(fd, buff, data_len);
        break_on_cond_1(rc < 0, "file write(%s) error: %i. %s\n", input_file_name, errno);
        printf("%s: file write(%s) ok. Data length = %zi\n", __func__, input_file_name, data_len);
    }
    //  close fifo
    close(fifo2_d);
    printf("%s: fifo close(%s) ok\n", __func__, fifo2_n);
    //  close file
    close(fd);
    printf("%s: file close(%s) ok\n", __func__, output_file_name);
    //
    printf("%s: finished.\n", __func__);
}
