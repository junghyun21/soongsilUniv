#ifndef _REPLACEMENT_H_
#define _REPLACEMENT_H_

enum eAlgorithm {OPTIMAL = 1, FIFO, LIFO, LRU, LFU, SC, ESC, ALL};

void replace_optimal(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream);
void replace_fifo(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream);
void replace_lifo(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream);
void replace_lru(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream);
void replace_lfu(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream);
void replace_sc(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream);
void replace_esc(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream);
void replace_all(char *page_string, char *esc_page_string, int string_cnt, int frame_cnt, int ref_page_stream);

#endif