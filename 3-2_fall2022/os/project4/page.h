#ifndef _PAGE_STRING_H_
#define _PAGE_STRING_H_

#include <stdio.h>

enum eString {RAND = 1, USERFILE};

// FIFO, LIFO
typedef struct _PageTable
{
    int input_time;
    int frame;
    char vi;
} PageTable;

// Optimal
typedef struct _PageTable_Optimal
{
    int frame;
    char vi;
} PageTable_Optimal;

// LRU
typedef struct _PageTable_LRU
{
    int ref_time;
    int frame;
    char vi;
} PageTable_LRU;

// LFU
typedef struct _PageTable_LFU
{
    int ref_cnt;
    int frame;
    char vi;
} PageTable_LFU;

// SC
typedef struct _PageTable_SC
{
    int frame;
    char vi;
    char r_bit;
} PageTable_SC;

// ESC
typedef struct _PageTable_ESC
{
    int frame;
    char vi;
    char r_bit;
    char w_bit;
} PageTable_ESC;

void string_random(char *page_string, char *esc_page_string);
void string_userfile(char *page_string, char *esc_page_string);
void separate_page_space(char *page_string, int *page_string_no_space);
void separte_page_bit(char *esc_page_string, int *esc_page_string_page, char *esc_page_string_bit);

void output_page_string(char* page_string);
void output_frame(FILE *fp, int processed_page_string, char page_fault, int *frame, int frame_cnt);

#endif