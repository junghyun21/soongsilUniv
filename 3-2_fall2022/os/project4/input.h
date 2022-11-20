#ifndef _INPUT_H_
#define _INPUT_H_

enum eCaller {SELECTALGO, PAGECNT, PAGESTRING};
enum eError {NONEXIST, CNT, ONLYALL};

int selectAlgorithm(int *algorithms); // 알고리즘 시뮬레이터 선택
int inputPageCnt(); // 페이지 프레임 개수 입력
int selectPageString(); // 데이터 입력 방식 선택

static void errorInput(enum eCaller caller, enum eError errno); // 입력 에러 처리 함수

#endif
