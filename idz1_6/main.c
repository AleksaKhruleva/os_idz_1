/* Two related processes of the same program, unnamed pipes.
 *
 * Develop a console application that uses unnamed pipes,
 * providing interaction according to the following scheme:
 * - the first process reads text data from a given file and
 *   transmits it to the second process through an unnamed pipe;
 * - the second process processes data in accordance with the task
 *   and transmits the processing result through an unnamed
 *   channel back to the first process;
 * - the first process outputs data to the specified file. */

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
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  global variables
//-----------------------------------------------------------------------------
int mission_id = 1;
int child_pid_1;
char *input_file_name = NULL;
char *output_file_name = NULL;
int pipes12[2];  //  pipes pair between process-1 & process-2
int pipes21[2];  //  pipes pair between process-2 & process-1
const size_t buff_size = 5000;
char buff[5000];
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  global functions
//-----------------------------------------------------------------------------
void extract_args(int argc, char **argv);
void create_pipes();
void create_processes();
void mission_1();
void mission_2();
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 * Main program function
 */
//-----------------------------------------------------------------------------
int main(int argc, char **argv) {
    extract_args(argc, argv);
    create_pipes();
    create_processes();
    switch (mission_id) {
        case 1:
            mission_1();
            while (wait(NULL) > 0);
            printf("%s: finished.\n", __func__);
            break;
        case 2:
            mission_2();
            break;
        default:
            fprintf(stderr, "Unexpected mission id: %i.\n", mission_id);
            exit(0);
    }
    return 0;
}

//-----------------------------------------------------------------------------
/**
 * Print usage
 */
//-----------------------------------------------------------------------------
void usage() {
    printf("Usage:\n");
    printf("\tidz1_6 -i input_file_name -o output_file_name\n");
    exit(0);
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
 * Break program on condition
 */
//-----------------------------------------------------------------------------
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
 * Create pipes
 */
//-----------------------------------------------------------------------------
void create_pipes() {
    int rc1, rc2;
    rc1 = pipe(pipes12);
    rc2 = pipe(pipes21);
    break_on_cond_2(rc1 != 0 || rc2 != 0, "Pipes create error, pipe(): %i, %s", errno);
}

//-----------------------------------------------------------------------------
/**
 * Create child process
 */
//-----------------------------------------------------------------------------
void create_processes() {
    child_pid_1 = fork();
    break_on_cond_2(child_pid_1 == -1, "Fork process error, fork(): %i, %s", errno);
    if (child_pid_1 == 0) {
        mission_id = 2; //  child #1
        return;
    }
}

//-----------------------------------------------------------------------------
/**
 *  the first process reads text data from a given file and
 *  transmits it to the second process through an unnamed pipe
 *
 *  the first process outputs data to the specified file
 */
//-----------------------------------------------------------------------------
void mission_1() {
    printf("%s: started.\n", __func__);
    sleep(1);
    //  open input file
    int fd = open(input_file_name, O_RDONLY);
    break_on_cond_1(fd < 0, "open(%s) error: %i. %s\n", input_file_name, errno);
    printf("%s: open(%s) ok.\n", __func__, input_file_name);
    //  read input file
    ssize_t data_len = read(fd, buff, buff_size);
    break_on_cond_1(data_len < 0, "read(%s) error: %i. %s\n", input_file_name, errno);
    printf("%s: read(%s) ok. Data length = %zi\n", __func__, input_file_name, data_len);
    //  close file
    close(fd);
    printf("%s: close(%s) ok\n", __func__, input_file_name);
    //  write buffer to pipe
    ssize_t send_len = write(pipes12[1], buff, data_len);
    break_on_cond_2(send_len < 0, "write(pipe-1-1) error: %i. %s\n", errno);
    printf("%s: write(pipe-1-1) ok. Data length = %zi\n", __func__, send_len);
    //  close pipe-1-1
    close(pipes12[1]);
    printf("%s: close(pipe-1-1) ok\n", __func__);
    //  read data from pipe-2-0
    data_len = read(pipes21[0], buff, buff_size);
    break_on_cond_2(data_len < 0, "read(pipe-2-0) error: %i. %s\n", errno);
    printf("%s: read(pipe-2-0) ok. Data length = %zi\n", __func__, data_len);
    //  close pipe-2-0
    close(pipes21[0]);
    printf("%s: close(pipe-1-0) ok\n", __func__);
    //  create output file
    fd = open(output_file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    break_on_cond_1(fd < 0, "open(%s) error: %i. %s\n", input_file_name, errno);
    printf("%s: open(%s) ok.\n", __func__, input_file_name);
    //  read input file
    ssize_t rc = write(fd, buff, data_len);
    break_on_cond_1(rc < 0, "write(%s) error: %i. %s\n", input_file_name, errno);
    printf("%s: write(%s) ok. Data length = %zi\n", __func__, input_file_name, data_len);
    //  close file
    close(fd);
    printf("%s: close(%s) ok\n", __func__, input_file_name);
    //
    printf("%s: finished.\n", __func__);
}

//-----------------------------------------------------------------------------
/**
 * the second process processes data in accordance with the task and
 * transmits the processing result through an unnamed channel back
 * to the first process
 */
//-----------------------------------------------------------------------------
void mission_2() {
    printf("%s: started.\n", __func__);
    sleep(1);
    //  read data from pipe-1-0
    ssize_t data_len = read(pipes12[0], buff, buff_size);
    break_on_cond_2(data_len < 0, "read(pipe-1-0) error: %i. %s\n", errno);
    printf("%s: read(pipe-1-0) ok. Data length = %zi\n", __func__, data_len);
    //  close pipe-1-0
    close(pipes12[0]);
    printf("%s: close(pipe-1-0) ok\n", __func__);
    //  rework data
    for (ssize_t i = 0; i < data_len / 2; ++i) {
        char chr = buff[i];
        buff[i] = buff[data_len - 1 - i];
        buff[data_len - 1 - i] = chr;
    }
    //  write buffer to pipe
    ssize_t send_len = write(pipes21[1], buff, data_len);
    break_on_cond_2(send_len < 0, "write(pipe-2-1) error: %i. %s\n", errno);
    printf("%s: write(pipe-2-1) ok. Data length = %zi\n", __func__, send_len);
    //  close pipe-1-1
    close(pipes21[1]);
    printf("%s: close(pipe-2-1) ok\n", __func__);
    //
    printf("%s: finished.\n", __func__);
}
