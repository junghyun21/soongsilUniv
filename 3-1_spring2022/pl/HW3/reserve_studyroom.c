#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define ADMIN_FILE "branch"
#define RESERVATION_FILE "reservation"

#define MAX_BRANCH 6
#define MAX_SPACE 5
#define MAX_PEOPLE 10
#define MAX_COMPUTER 10
#define MAX_DESK 10
#define MAX_LENGTH 10
#define START_TIME 8
#define END_TIME 22
#define HOUR 24
#define MAX_BUF 128

typedef enum MODE {ADMIN0 = 1, USER0, QUIT0} Mode;
typedef enum ADMINMODE {BRANCH1 = 1, SPACE1, INIT1} AdminMode;
typedef enum ADMINWORK {ADD2 = 1, MODIFY2, DELETE2, INIT2} AdminWork;
typedef enum SPACEINFO {NAME3 = 1, INFO3, BOTH3, INIT3} SpaceInfo;
typedef enum USERMODE {SPACE_INFO4 = 1, NEW4, RESERVATION_INFO4, INIT4} UserMode;
typedef enum USERWORK {SHOW5 = 1, ADD5 = 1, MODIFY5, DELETE5, INIT5} UserWork;

typedef struct Space{
    char name[MAX_LENGTH + 1]; // 지점 내 스터디 공간의 이름
    int max_people; // 각 지점 내 스터디 공간의 최대 허용 인원
    int desks; // 책상 개수
    int computers; // 컴퓨터 개수
}Space;

typedef struct Branch{
    char name[MAX_LENGTH + 1]; // 지점의 이름
    bool isExist[MAX_SPACE + 1]; // 스터디룸의 존재 여부
    struct Space space[MAX_SPACE + 1]; // 지점 내 각 스터디 공간들
}Branch;

typedef struct Reservation{
    int date; // 예약 일자
    char userID[MAX_LENGTH + 1]; // 사용자 ID
    int branchNum; // 예약된 지점의 고유번호
    int spaceNum; // 예약된 공간의 고유번호
    int start_time; // 예약 시간
    int use_time; // 사용 예정 시간
    int num_people; // 사용 인원
}Reservation;

Mode prompt_select_Mode(); // 초기 화면(모드 선택) 출력
AdminWork prompt_select_AdminWork(AdminMode adminMode); // 지점 or 지점 내 스터디 공간의 추가/수정/삭제 작업 선택
AdminMode prompt_select_Modify(); // 수정할 지점 or 지점 내 스터디 공간 선택
unsigned int prompt_select_AdminNumber(AdminMode adminMode, AdminWork adminWork); // 지점 or 지점 내 스터디 공간의 고유 번호 선택
SpaceInfo prompt_select_SpaceInfo(); // 스터디 공간에서 수정할 부분 선택 (이름, 세부사항)
int prompt_input_AdminStr(AdminMode adminMode, AdminWork adminWork, char *name); // 지점 or 지점 내 스터디 공간의 이름 입력
int prompt_input_Space(AdminWork adminWork, Space *space); // 스터디 공간의 세부사항을 추가/수정할 지점 내 스터디 공간 번호 입력

int admin_mode(); // 관리자 모드
int adminBranch(Branch *branch); // 지점 관리
int adminSpace(Branch *branch); // 지점별 스터디 공간 관리
int adminAdd(Branch *branch, AdminMode adminMode, int branchNum); // 지점 및 지점별 스터디 공간 추가
int adminModify(Branch *branch, AdminMode adminMode, int branchNum); // 지점 및 지점별 스터디 공간 수정
int adminDelete(Branch *branch, AdminMode adminMode, int branchNum); // 지점 및 지점별 스터디 공간 삭제
bool isReserved(AdminMode adminMode, int branchNum, int spaceNum); // 예약 내역이 있는 스터디 공간인지 확인

UserMode prompt_select_UserMode(char *userID, int user_reservation); // 공간조회/신규예약/예약조회 기능 선택
UserWork prompt_select_UserWork(char *userID); // 예약 조회 기능에서 예약조회/수정/삭제 중 기능 선택
unsigned int prompt_select_UserNumber(UserWork userWork, int user_reservation); // 수정하거나 삭제할 예약 내역의 인덱스 선택
int prompt_input_UserStr(char *userID); // 유저 ID 입력 받음
int prompt_input_Reservation(UserWork userWork, Reservation *reservation); // 예약 정보를 받음

int user_mode(); // 사용자 모드
int list_Reservation(Reservation *reservation, int reservationNum, char *userID, int user_reservation); // 예약 조회
int reservationAdd(Reservation *reservation, int reservationNum, Reservation *newResrvation, char *userID); // 예약 추가
int reservationModify(Reservation *reservation, Reservation *listReservation, int reservationNum, int user_reservation, char *userID); // 예약 수정
int reservationDelete(Reservation *reservation, Reservation *listReservation, int reservationNum, int user_reservation); // 예약 삭제
int hasReserved(Reservation *reservation, int reservationNum, char *userID); // 예약 내역이 있는 user인지 판단
bool isPossible_reservation(Reservation *reservation, int reservationNum, Reservation reservationInfo, int branchNum, int spaceNum, UserWork userWork, Reservation modify); // 수정 및 추가가 가능한지 확인
bool isPossible_branch(Space space, Reservation reservationInfo); // 수정 및 추가가 가능한지 확인
void showAll(); // 현재 존재하는 모든 지점 및 스터디 공간 조회
void showReservation(Reservation *listReservation, char *userID, int user_reservation); // 예약 내역 조회
int showPossible(Reservation *reservation, int reservationNum, Reservation modifyReservation, int *branchNum, int *spaceNum, UserWork userWork, Reservation modify); // 예약 가능한 목록 출력

int todayDate(); // 오늘 날짜 YYMMDD
bool checkDate(int date); // 유효한 날짜인지 검사
bool checkYear(int year); // 윤년인지 검사

int main()
{
    Mode mode;

    while(true)
    {
        mode = prompt_select_Mode();
        
        switch(mode)
        {
            case ADMIN0: 
                if(admin_mode() < 0) printf("관리자 모드에서 오류가 발생하였습니다. 다시 시도해주세요.\n");
                break;
            
            case USER0:
                if(user_mode() < 0) printf("사용자 모드에서 오류가 발생하였습니다. 다시 시도해주세요.\n");
                break;  

            case QUIT0:
                printf("프로그램을 종료합니다.\n");
                return 0; 
        }
    }
}

int admin_mode()
{
    AdminMode adminMode = BRANCH1;
    AdminWork adminWork;
    bool isExistBranch = false;

    FILE *fp;
    Branch branch[MAX_BRANCH + 1];

    // 구조체 branch 초기화
    // 처음 값: name == "", isExist == false, space.name == "", space.max_people, ... == 0
    for(int i = 0; i < MAX_BRANCH + 1; ++i)
    {
        memset(&branch[i], 0, sizeof(Branch));
    }
    
    // 파일 이름이 존재하지 않으면 새로 생성
    if(access(ADMIN_FILE, F_OK) < 0)
    {
        // w+: 파일의 읽기/쓰기 가능 + 파일이 없을 때 새로 생성 + 파일이 있을 때 기존 내용 삭제
        if((fp = fopen(ADMIN_FILE, "w+")) == NULL)
        {
            fprintf(stderr, "%s 파일을 열 수 없습니다.\n", ADMIN_FILE);
            exit(1);
        }

        if(fwrite(&branch[1], sizeof(Branch), MAX_BRANCH, fp) != MAX_BRANCH)
        {
            fprintf(stderr, "%s 파일에 쓸 수 없습니다.\n", ADMIN_FILE);
            exit(1);
        }
    }
    // 파일이 존재하면 기존 파일 open + 버퍼(branch)에 파일의 값들 저장
    else
    {
        isExistBranch = true;

        // r+: 파일의 읽기/쓰기 가능 + 파일이 없을 때 에러 + 파일이 있을 때 처음부터 읽음
        if((fp = fopen(ADMIN_FILE, "r+")) == NULL)
        {
            fprintf(stderr, "%s 파일을 열 수 없습니다.\n", ADMIN_FILE);
            exit(1);
        }

        if(fread(&branch[1], sizeof(Branch), MAX_BRANCH, fp) != MAX_BRANCH)
        {
            fprintf(stderr, "%s 파일을 읽을 수 없습니다.\n", ADMIN_FILE);
            exit(1);
        }   
    }

    while(true)
    {
        adminWork = prompt_select_AdminWork(adminMode);

        switch(adminWork)
        {
            case ADD2:
                if(adminAdd(branch, adminMode, 0) < 0)
                {
                    fclose(fp);
                    return 0;
                }
                break;

            // BRANCH: 지점의 이름을 수정할 것인가
            // SPACE: 지점 내의 스터디 공간들을 수정할 것인가
            case MODIFY2:
                if(!isExistBranch)
                {
                    printf("지점이 아무것도 존재하지 않아 수정이 불가합니다.\n\n");
                    continue;
                }
                adminMode = prompt_select_Modify();

                if(adminMode == BRANCH1)
                {
                    if(adminModify(branch, adminMode, 0) < 0)
                    {           
                        fclose(fp);
                        return 0;
                    }
                }
                else if(adminMode == SPACE1)
                {
                    if(adminSpace(branch) < 0)
                    {
                        fclose(fp);
                        return 0;
                    }
                }
                else
                {
                    printf("초기 화면으로 돌아갑니다.\n");
                    return 0;
                }
                break;

            case DELETE2:
                if(!isExistBranch)
                {
                    printf("지점이 아무것도 존재하지 않아 삭제가 불가합니다.\n\n");
                    continue;
                }
                if(adminDelete(branch, adminMode, 0) < 0)
                {
                    fclose(fp);
                    return 0;
                }
                break;

            case INIT2:
                printf("초기 화면으로 돌아갑니다.\n");
                return 0;
        }

        break;

    }

    fseek(fp, 0, SEEK_SET);

    // 변경된 값들 branch 파일에 저장
    if(fwrite(&branch[1], sizeof(Branch), MAX_BRANCH, fp) != MAX_BRANCH)
    {
        fprintf(stderr, "%s 파일에 쓸 수 없습니다.\n", ADMIN_FILE);
        exit(1);
    }

    fclose(fp);

    return 0;
}

int adminSpace(Branch *branch)
{
    AdminMode adminMode = SPACE1;
    AdminWork adminWork;
    unsigned int number; // 스터디 공간의 수정을 진행할 지점 번호
    bool isExistSpace = false;

    // 수정을 진행할 지점 번호 선택
    while(true)
    {
        number = prompt_select_AdminNumber(BRANCH1, MODIFY2);

        if(number == MAX_SPACE + 1)
        {
            printf("초기 화면으로 돌아갑니다.\n\n");
            return -1;
        }

        // 선택한 지점(number)이 존재하지 않으면 그 지점 내의 스터디 공간에 대한 추가/수정/삭제도 불가능
        // branch[number].name == "" -> number 지점은 존재하지 않는 지점
        if(strcmp(branch[number].name, ""))
        {
            break;
        }
        else
        {
            printf("%d번은 존재하지 않는 지점입니다. 다른 지점을 선택해주세요.\n\n", number);
        }
    }

    for(int i = 1; i <= MAX_SPACE; ++i)
    {
        if(branch[number].isExist[i])
        {
            isExistSpace = true;
            break;
        }
    }

    while(true)
    {
         // 추가/수정/삭제 중 어떤 작업을 할지 선택
        adminWork = prompt_select_AdminWork(adminMode);    

        switch(adminWork)
        {
            case ADD2:
                if(adminAdd(branch, adminMode, number) < 0) return -1;
                break;

            case MODIFY2:
                if(!isExistSpace)
                {
                    printf("지점 내 스터디 공간이 아무것도 존재하지 않아 수정이 불가합니다.\n\n");
                    continue;
                }
                if(adminModify(branch, adminMode, number) < 0) return -1;
                break;

            case DELETE2:
                if(!isExistSpace)
                {
                    printf("지점 내 스터디 공간이 아무것도 존재하지 않아 삭제가 불가합니다.\n\n");
                    continue;
                }
                if(adminDelete(branch, adminMode, number) < 0) return -1;
                break;

            case INIT2:
                printf("초기 화면으로 돌아갑니다.\n");
                return 0;
        }

        break;
    }

    return 0;
}

int adminAdd(Branch *branch, AdminMode adminMode, int branchNum)
{
    AdminWork adminWork = ADD2;
    unsigned int number;

    while(true)
    {
        number = prompt_select_AdminNumber(adminMode, adminWork);
        
        // 사용자 모드 > 지점 관리 모드일 때 -> number는 수정할 지점의 고유번호
        if(adminMode == BRANCH1)
        {
            if(number == MAX_BRANCH + 1)
            {
                printf("초기 화면으로 돌아갑니다.\n\n");
                return -1;
            }

            // 존재하지 않는 지점일 때(== 추가할 수 있는 지점일 때) -> 지점 이름 == ""
            if(!strcmp(branch[number].name, ""))
            {
                // 새로 추가할 이름을 해당 branch의 이름 부분에 저장
                if(prompt_input_AdminStr(adminMode, adminWork, branch[number].name) < 0)
                {
                    printf("초기 화면으로 돌아갑니다.\n\n");
                    return -1;
                }

                printf("%d번 지점(%s)이 추가되었습니다.\n\n", number, branch[number].name);

                break;
            }
            else
            {
                printf("%d번은 이미 존재하는 지점입니다. 다른 지점을 선택해주세요.\n\n", number);
            }

        }
        // 사용자 모드 > 지점 내 스터디 공간 관리 모드일 때 -> number는 수정할 스터디 공간의 고유번호
        else if(adminMode == SPACE1)
        {   
            if(number == MAX_SPACE + 1)
            {
                printf("초기 화면으로 돌아갑니다.\n\n");
                return -1;
            }

            // 스터디룸이 존재하지 않는 경우(false)에만 추가 가능
            // 스터디 공간의 이름 + 세부정보 모두 새로 저장
            if(!branch[branchNum].isExist[number])
            {
                Space space;
                memset(&space, 0, sizeof(Space));

                // 새로 추가할 공간의 이름 입력 받음
                if(prompt_input_AdminStr(adminMode, adminWork, space.name) < 0)
                {
                    printf("초기 화면으로 돌아갑니다.\n\n");
                    return -1;
                }

                // 새로 추가할 공간의 세부 사항 입력 받음
                if(prompt_input_Space(adminWork, &space) < 0)
                {
                    printf("초기 화면으로 돌아갑니다.\n\n");
                    return -1;
                }

                memcpy(&branch[branchNum].space[number], &space, sizeof(Space));
                branch[branchNum].isExist[number] = true;

                printf("%d번 지점(%s)의 %d번 스터디 공간(%s)이 추가되었습니다.\n\n", branchNum, branch[branchNum].name, number, branch[branchNum].space[number].name);

                break;
            }
            else
            {
                printf("%d번은 이미 존재하는 스터디 공간입니다. 다른 스터디 공간을 선택해주세요.\n\n", number);
            }
        }
        else
        {
            return -1;
        }

    }

    return 0;
}

int adminModify(Branch *branch, AdminMode adminMode, int branchNum)
{
    AdminWork adminWork = MODIFY2;
    unsigned int number;
    char name[MAX_LENGTH + 1];

    while(true)
    {
        number = prompt_select_AdminNumber(adminMode, adminWork);
        
        // 사용자 모드 > 지점 관리 모드일 때 -> number는 수정할 지점의 고유번호
        // 지점 이름 수정
        if(adminMode == BRANCH1)
        {
            if(number == MAX_BRANCH + 1)
            {
                printf("초기 화면으로 돌아갑니다.\n\n");
                return -1;
            }

            // 존재하는 지점일 때(== 수정할 수 있는 지점일 때) -> 지점 이름 != ""
            if(strcmp(branch[number].name, ""))
            {
                // 기존 이름
                strcpy(name, branch[number].name);
                // 새로 수정할 이름을 해당 branch의 이름 부분에 저장
                if(prompt_input_AdminStr(adminMode, adminWork, branch[number].name) < 0)
                {
                    printf("초기 화면으로 돌아갑니다.\n\n");
                    return -1;
                }

                printf("%d번 지점의 이름이 '%s'에서 '%s'로 변경되었습니다.\n\n", number, name, branch[number].name);

                break;
            }
            else
            {
                printf("%d번은 존재하지 않는 지점입니다. 다른 지점을 선택해주세요.\n\n", number);
            }

        }
        // 사용자 모드 > 지점 내 스터디 공간 관리 모드일 때 -> number는 수정할 스터디 공간의 고유번호
        // 지점 내의 스터디 공간 수정
        else if(adminMode == SPACE1)
        {
            if(number == MAX_SPACE + 1)
            {
                printf("초기 화면으로 돌아갑니다.\n\n");
                return -1;
            }

            // 스터디룸이 존재하는 경우(true)에만 수정 가능
            if(branch[branchNum].isExist[number])
            {
                SpaceInfo spaceInfo;
                Space space;
                bool isReservation;
                bool isName = false, isInfo = false;

                // 예약 내역이 있는 스터디 공간인지 확인
                // 해당 스터디룸에 예약이 없는 경우(false)에만 수정 가능
                isReservation = isReserved(adminMode, branchNum, number);
                if(isReservation)
                {
                    printf("%d번 지점(%s)의 %d번 스터디 공간(%s)은 예약 내역이 존재하기 때문에 수정이 불가합니다. 다른 스터디 공간을 선택해주세요.\n\n", branchNum, branch[branchNum].name, number, branch[branchNum].space[number].name);
                    continue;
                }

                // 기존에 존재하던 정보들로 초기화
                memcpy(&space, &branch[branchNum].space[number], sizeof(Space));

                // 기존 이름
                strcpy(name, branch[branchNum].space[number].name);

                // 수정할 부분 선택 -> 스터디 공간의 이름, 스터디 공간의 세부사항, 둘 다
                spaceInfo = prompt_select_SpaceInfo();
                switch(spaceInfo)
                {
                    case NAME3: 
                        isName = true;
                        break;

                    case INFO3: 
                        isInfo = true; 
                        break;

                    case BOTH3: 
                        isName = true;
                        isInfo = true;
                        break;

                    case INIT3: 
                        printf("초기 화면으로 돌아갑니다.\n");
                        return 0;
                }

                // 스터디 공간의 이름 수정
                if(isName)
                {
                    if(prompt_input_AdminStr(adminMode, adminWork, space.name) < 0)
                    {
                        printf("초기 화면으로 돌아갑니다.\n\n");
                        return -1;
                    }
                
                }

                // 스터디 공간의 세부사항 수정
                if(isInfo)
                {
                    if(prompt_input_Space(adminWork, &space) < 0)
                    {
                        printf("초기 화면으로 돌아갑니다.\n\n");
                        return -1;
                    }        
                }

                // 수정 사항 저장
                memcpy(&branch[branchNum].space[number], &space, sizeof(Space));

                // 변경 사항 출력
                switch(spaceInfo)
                {
                    case NAME3:
                        printf("%d번 지점(%s)의 %d번 스터디 공간의 이름이 '%s'에서 '%s'로 변경되었습니다.\n\n", branchNum, branch[branchNum].name, number, name, branch[branchNum].space[number].name);
                        break;

                    case INFO3: 
                        printf("%d번 지점(%s)의 %d번 스터디 공간(%s)의 세부사항이 변경되었습니다.\n\n", branchNum, branch[branchNum].name, number, branch[branchNum].space[number].name);
                        break;

                    case BOTH3: 
                        printf("%d번 지점(%s)의 %d번 스터디 공간의 이름('%s'->'%s')과 세부사항이 변경되었습니다.\n\n", branchNum, branch[branchNum].name, number, name, branch[branchNum].space[number].name);
                        break;

                    default: 
                        return -1;
                }

                break;
            }
            else
            {
                printf("%d번은 존재하지 않는 스터디 공간입니다. 다른 스터디 공간을 선택해주세요.\n\n", number);
            }
        }
        else
        {
            return -1;
        }

    }

    return 0;
}

int adminDelete(Branch *branch, AdminMode adminMode, int branchNum)
{
    AdminWork adminWork = DELETE2;
    unsigned int number;
    char name[MAX_LENGTH + 1];
    bool isReservation;

    while(true)
    {
        number = prompt_select_AdminNumber(adminMode, adminWork);

        // 사용자 모드 > 지점 관리 모드일 때 -> number는 삭제할 지점의 고유번호
        // 지점 자체 삭제
        if(adminMode == BRANCH1)
        {
            if(number == MAX_BRANCH + 1)
            {
                printf("초기 화면으로 돌아갑니다.\n\n");
                return -1;
            }

            // 존재하는 지점일 때(== 삭제할 수 있는 지점일 때) -> 지점 이름 != ""
            if(strcmp(branch[number].name, ""))
            {
                // 예약 내역이 있는 지점인지 확인
                // 해당 지점에 예약이 없는 경우(false)에만 수정 가능
                isReservation = isReserved(adminMode, number, 0);
                if(isReservation)
                {
                    printf("%d번 지점(%s)은 예약 내역이 존재하기 때문에 삭제가 불가합니다. 다른 지점을 선택해주세요.\n\n", number, branch[number].name);
                    continue;
                }

                // 기존 이름
                strcpy(name, branch[branchNum].space[number].name);

                memset(&branch[number], 0, sizeof(Branch));

                printf("%d번 지점(%s)이 삭제되었습니다.\n\n", number, name);

                break;
            }
            else
            {
                printf("%d번은 존재하지 않는 지점입니다. 다른 지점을 선택해주세요.\n\n", number);
            }
            
            // 지점 내 스터디 공간에 예약 내역이 있는 경우 -> 지점 삭제 불가

        }
        // 사용자 모드 > 지점 내 스터디 공간 관리 모드일 때 -> number는 삭제할 스터디 공간의 고유번호
        // 지점 내 스터디 공간 삭제
        else if(adminMode == SPACE1)
        {
            if(number == MAX_SPACE + 1)
            {
                printf("초기 화면으로 돌아갑니다.\n\n");
                return -1;
            }
           
            // 스터디룸이 존재하는 경우(true)에만 삭제 가능
            if(branch[branchNum].isExist[number])
            {   
                // 예약 내역이 있는 스터디 공간인지 확인
                // 해당 스터디룸에 예약이 없는 경우(false)에만 삭제 가능
                isReservation = isReserved(adminMode, branchNum, number);
                if(isReservation)
                {
                    printf("%d번 지점(%s)의 %d번 스터디 공간(%s)은 예약 내역이 존재하기 때문에 삭제가 불가합니다. 다른 지점을 선택해주세요.\n\n", branchNum, branch[branchNum].name, number, branch[branchNum].space[number].name);
                    continue;
                }

                // 기존 이름
                strcpy(name, branch[branchNum].space[number].name);

                memset(&branch[branchNum].space[number], 0, sizeof(Space));
                branch[branchNum].isExist[number] = false;

                printf("%d번 지점(%s)의 %d번 스터디 공간(%s)이 삭제되었습니다.\n\n", branchNum, branch[branchNum].name, number, name);

                break;
            }
            else
            {
                printf("%d번은 존재하지 않는 스터디 공간입니다. 다른 스터디 공간을 선택해주세요.\n\n", number);
            }
        }
        else
        {
            return -1;
        }
    }

    return 0;
}

bool isReserved(AdminMode adminMode, int branchNum, int spaceNum)
{
    FILE* fp;
    Reservation reservation;
    int size;
    int reservationNum;
    bool isReservation = false;

    // 파일 이름이 존재하지 않으면 -> 예약 내역 하나도 없음
    // 따라서 예약 파일이 존재하는 경우에만 체크
    if(access(RESERVATION_FILE, F_OK) == 0)
    {
        // r+: 파일의 읽기/쓰기 가능 + 파일이 없을 때 에러 + 파일이 있을 때 처음부터 읽음
        if((fp = fopen(RESERVATION_FILE, "r+")) == NULL)
        {
            fprintf(stderr, "%s 파일을 열 수 없습니다.\n", RESERVATION_FILE);
            exit(1);
        }

        // reservation 파일의 사이즈
        fseek(fp, 0, SEEK_END);
        size = (int)ftell(fp);
        reservationNum = size / sizeof(Reservation);

        fseek(fp, 0, SEEK_SET);

        // 해당 지점에 예약 내역이 하나라도 있으면 true 리턴
        if(adminMode == BRANCH1)
        {
            // reservation 파일을 예약 단위로 읽으면서 해당 공간에 예약 내역이 있으면 -> true 리턴
            for(int i = 0; i < reservationNum; ++i)
            {
                if(fread(&reservation, sizeof(Reservation), 1, fp) != 1)
                {
                    fprintf(stderr, "%s 파일을 읽을 수 없습니다.\n", ADMIN_FILE);
                    exit(1);
                }  

                if(reservation.branchNum == branchNum)
                {
                    isReservation = true;
                    break;
                }
            }

        }
        // 해당 지점의 해당 스터디 공간에 예약 내역이 있으면 true 리턴
        else if(adminMode == SPACE1)
        {
            // reservation 파일을 예약 단위로 읽으면서 해당 공간에 예약 내역이 있으면 -> true 리턴
            for(int i = 0; i < reservationNum; ++i)
            {
                if(fread(&reservation, sizeof(Reservation), 1, fp) != 1)
                {
                    fprintf(stderr, "%s 파일을 읽을 수 없습니다.\n", ADMIN_FILE);
                    exit(1);
                }  

                if(reservation.branchNum == branchNum && reservation.spaceNum == spaceNum)
                {
                    isReservation = true;
                    break;
                }
            }
        }

    }

    fclose(fp);

    return isReservation;
}


int user_mode()
{
    FILE *fp;
    UserMode userMode;
    Reservation newReservation;
    char userID[MAX_LENGTH + 1];
    int user_reservation;
    int size;
    int reservationNum;
    
    memset(&newReservation, 0, sizeof(Reservation));

    // 관리자 파일이 없다 == 예약할 수 있는 지점 및 공간이 아예 없다
    if(access(ADMIN_FILE, F_OK) < 0)
    {
        printf("지점 및 스터디 공간이 아예 존재하지 않습니다.\n");
        printf("관리자 모드에서 지점 및 스터디 공간을 먼저 생성해주세요.\n");

        return 0;
    }

    // 사용자 ID 받아옴
    if(prompt_input_UserStr(userID) < 0)
    {
        printf("초기 화면으로 돌아갑니다.\n\n");
        return -1;
    }

    // 파일 이름이 존재하지 않으면 새로 생성
    if(access(RESERVATION_FILE, F_OK) < 0)
    {
        // w+: 파일의 읽기/쓰기 가능 + 파일이 없을 때 새로 생성 + 파일이 있을 때 기존 내용 삭제
        if((fp = fopen(RESERVATION_FILE, "w+")) == NULL)
        {
            fprintf(stderr, "%s 파일을 열 수 없습니다.\n", RESERVATION_FILE);
            exit(1);
        }
    }
    // 파일이 존재하면 기존 파일 open + 버퍼(branch)에 파일의 값들 저장
    else
    {
        // r+: 파일의 읽기/쓰기 가능 + 파일이 없을 때 에러 + 파일이 있을 때 처음부터 읽음
        if((fp = fopen(RESERVATION_FILE, "r+")) == NULL)
        {
            fprintf(stderr, "%s 파일을 열 수 없습니다.\n", RESERVATION_FILE);

            exit(1);
        }
    }

    fseek(fp, 0, SEEK_END);
    size = (int)ftell(fp);
    reservationNum = size / sizeof(Reservation);

    Reservation reservation[reservationNum + 1];
    for(int i = 0; i <= reservationNum; ++i)
    {
        memset(&reservation[i], 0, sizeof(Reservation));
    }

    fseek(fp, 0, SEEK_SET);

    // 빈파일이 아닌 경우
    if(size != 0)
    {
        if(fread(&reservation[1], sizeof(Reservation), reservationNum, fp) != reservationNum)
        {
            fprintf(stderr, "%s 파일을 읽을 수 없습니다.: %d\n", RESERVATION_FILE ,errno);
            exit(1);
        }

        // 예약 내역이 있는 사용자인지 확인 -> 예약 내역 여부따라 사용 가능한 기능 달라짐
        // 사용자의 예약 개수 리턴
        user_reservation = hasReserved(reservation, reservationNum, userID);
    }
    // 빈파일인 경우 -> 예약 내역 아무것도 없음
    else
    {
        user_reservation = 0;
    }

    fclose(fp);

    int idx;

    userMode = prompt_select_UserMode(userID, user_reservation);
    switch(userMode)
    {
        case SPACE_INFO4:
            showAll();
            break;

        // 신규 예약을 하는 경우 -> 파일의 맨 끝에 sizeof(reservation) 크기의 레코드 저장 
        case NEW4:
            if(reservationAdd(reservation, reservationNum, &newReservation, userID) < 0) break;

            if((fp = fopen(RESERVATION_FILE, "a")) == NULL)
            {
                fprintf(stderr, "%s 파일을 열 수 없습니다.\n", RESERVATION_FILE);
                exit(1);
            }

            if(fwrite(&newReservation, sizeof(Reservation), 1, fp) != 1)
            {
                fprintf(stderr, "%s 파일에 쓸 수 없습니다.\n", RESERVATION_FILE);
                exit(1);
            }
            fclose(fp);
            break;

        // 기존에 예약 내역이 있는 사용자인 경우에만 가능
        // 기존 예약 내역 수정 및 삭제 -> 파일 덮어쓰기
        case RESERVATION_INFO4:
            if(list_Reservation(reservation, reservationNum, userID, user_reservation) < 0) break;
            
            if((fp = fopen(RESERVATION_FILE, "w+")) == NULL)
            {
                fprintf(stderr, "%s 파일을 열 수 없습니다.\n", RESERVATION_FILE);
                exit(1);
            }

            reservationNum = 0;

            // reservation[idx].date == 0 -> 파일의 끝
            // 삭제한 경우 reservationNum의 개수 줄어듦
            idx = 1;
            while(reservation[idx].date != 0)
            {
                ++reservationNum;
                // printf("%d\n", reservation[idx].date);
                ++idx;
            }

            // printf("reservationNum: %d\n", reservationNum);

            if(fwrite(&reservation[1], sizeof(Reservation), reservationNum, fp) != reservationNum)
            {
                fprintf(stderr, "%s 파일에 쓸 수 없습니다.\n", RESERVATION_FILE);
                exit(1);
            }
            fclose(fp);

            // fp = fopen("reservation", "r+");
            // fseek(fp, 0, SEEK_END);
            // size = ftell(fp);

            // printf("size: %d\n", size);

            break;

        case INIT4:
            printf("초기 화면으로 돌아갑니다.\n");
            break;
    }

    return 0;
}

int list_Reservation(Reservation *reservation, int reservationNum, char *userID, int user_reservation)
{
    UserWork userWork;
    Reservation temp;
    Reservation listReservation[user_reservation + 1];

    for(int i = 0; i <= user_reservation; ++i)
    {
        memset(&listReservation[i], 0, sizeof(Reservation));
    }
    
    // printf("%d\n", user_reservation);

    int i = 1, j =1;
    while(i <= user_reservation)
    {
        // reservation[idx].userID == userID -> 기존 예약 내역 정보 복사
        if(!strcmp(reservation[j].userID, userID))
        {
            memcpy(&listReservation[i], &reservation[j], sizeof(Reservation));
            ++i;
        }
        ++j;
    }
    
    // // userID의 예약 리스트를 날짜에 맞춰 정렬
    // for(int i = 1; i < user_reservation - 1; ++i)
    // {
    //     for(int j = 2; j < user_reservation - i; ++j)
    //     {
    //         if(listReservation[j - 1].date > listReservation[j].date)
    //         {
    //             memcpy(&temp, &listReservation[j - 1], sizeof(Reservation));
    //             memcpy(&listReservation[j - 1], &listReservation[j], sizeof(Reservation));
    //             memcpy(&listReservation[j], &temp, sizeof(Reservation));
    //         }  
    //     }
    // }

    while(true)
    {
        // userID에 해당하는 사용자의 예약 내역 출력
        showReservation(listReservation, userID, user_reservation);

        userWork = prompt_select_UserWork(userID);
        switch(userWork)
        {
            case SHOW5:
                continue;

            case MODIFY5:
                if(reservationModify(reservation, listReservation, reservationNum, user_reservation, userID) < 0) return -1;
                break;

            case DELETE5:
                if(reservationDelete(reservation, listReservation, reservationNum, user_reservation) < 0) return -1;
                break;

            case INIT5:
                printf("초기 화면으로 돌아갑니다.\n");
                return 0;
        }

        break;
    }

    return 0;
}

int reservationAdd(Reservation *reservation, int reservationNum, Reservation *newReservation, char *userID)
{
    UserWork userWork = ADD5;
    Reservation addReservation;
    unsigned int number;
    int possibleNum;
    int branchNum[MAX_BUF];
    int spaceNum[MAX_BUF];

    memset(&addReservation, 0, sizeof(Reservation));
    strcpy(addReservation.userID, userID);

    while(true)
    {
        // 추가할 값 저장 -> 지점 고유번호, 스터디 공간 고유번호 제외한 나머지 부분 저장
        if(prompt_input_Reservation(userWork, &addReservation) < 0)
        {
            printf("초기 화면으로 돌아갑니다.\n\n");
            return -1;
        }

        // 입력된 수정할 값을 바탕으로 예약 가능한 목록 출력
        // 리턴 값 -> 예약 가능한 목록의 개수
        possibleNum = showPossible(reservation, reservationNum, addReservation, branchNum, spaceNum, userWork, addReservation);

        if(possibleNum == 0) printf("신규 예약 정보 입력 화면으로 돌아갑니다.\n");
        else break;
    }

    // 지점 및 스터디 공간 고유번호 선택
    number = prompt_select_UserNumber(userWork , possibleNum);
    if(number == possibleNum + 1)
    {
        printf("초기 화면으로 돌아갑니다.\n\n");
        return -1;
    }

    addReservation.branchNum = branchNum[number];
    addReservation.spaceNum = spaceNum[number];

    memcpy(newReservation, &addReservation, sizeof(Reservation));

    printf("선택하신 예약 내역이 추가되었습니다.\n\n");

    return 0;
}

int reservationModify(Reservation *reservation, Reservation *listReservation, int reservationNum, int user_reservation, char *userID)
{
    UserWork userWork = MODIFY5;
    Reservation modifyReservation, modifiedReservation;
    unsigned int number;
    int date;
    int possibleNum;
    int branchNum[MAX_BUF];
    int spaceNum[MAX_BUF];

    memset(&modifiedReservation, 0, sizeof(Reservation));
    strcpy(modifiedReservation.userID, userID);
    strcpy(modifyReservation.userID, userID);

    while(true)
    {
        // 수정할 예약 내역 선택
        number = prompt_select_UserNumber(userWork , user_reservation);
        if(number == user_reservation + 1)
        {
            printf("초기 화면으로 돌아갑니다.\n\n");
            return -1;
        }

        // 오늘 날짜이면 수정 불가
        date = todayDate();
        if(date == listReservation[number].date)
        {
            printf("오늘 날짜의 예약 내역은 수정이 불가합니다. 다른 예약 내역을 선택해주세요.\n\n");
            continue;
        }

        memcpy(&modifiedReservation, &listReservation[number], sizeof(Reservation));

        // 수정할 값 저장 -> 지점 고유번호, 스터디 공간 고유번호 제외한 나머지 부분 저장
        if(prompt_input_Reservation(userWork, &modifyReservation) < 0)
        {
            printf("초기 화면으로 돌아갑니다.\n\n");
            return -1;
        }

        // 입력된 수정할 값을 바탕으로 예약 가능한 목록 출력
        // 리턴 값 -> 예약 가능한 목록의 개수
        possibleNum = showPossible(reservation, reservationNum, modifyReservation, branchNum, spaceNum, userWork, modifiedReservation);

        if(possibleNum == 0) printf("수정할 예약 내역 번호 선택 화면으로 돌아갑니다.\n");
        else break;
    }

    // 지점 및 스터디 공간 고유번호 선택
    number = prompt_select_UserNumber(userWork , possibleNum);
    if(number == possibleNum + 1)
    {
        printf("초기 화면으로 돌아갑니다.\n\n");
        return -1;
    }

    modifyReservation.branchNum = branchNum[number];
    modifyReservation.spaceNum = spaceNum[number];

    int idx = 1;
    while(idx <= reservationNum)
    {
        if(!memcmp(&reservation[idx], &modifiedReservation, sizeof(Reservation)))
        {
            memcpy(&reservation[idx], &modifyReservation, sizeof(Reservation));
           
            printf("선택하신 예약 내역이 수정되었습니다.\n\n");

            printf("[수정 전]\n");
            printf("> 예약 일자(YYMMDD): %d\n", modifiedReservation.date);
            printf("> 지점 번호: %d\n", modifiedReservation.branchNum);
            printf("> 스터디 공간 번호: %d\n", modifiedReservation.spaceNum);
            printf("> 예약 시간: %d\n", modifiedReservation.start_time);
            printf("> 사용 예정 시간: %d\n", modifiedReservation.use_time);
            printf("> 사용 인원: %d\n\n", modifiedReservation.num_people);

            printf("[수정 후]\n");
            printf("> 예약 일자(YYMMDD): %d\n", reservation[idx].date);
            printf("> 지점 번호: %d\n", reservation[idx].branchNum);
            printf("> 스터디 공간 번호: %d\n", reservation[idx].spaceNum);
            printf("> 예약 시간: %d\n", reservation[idx].start_time);
            printf("> 사용 예정 시간: %d\n", reservation[idx].use_time);
            printf("> 사용 인원: %d\n\n", reservation[idx].num_people);
            
            break;
        }
        ++idx;
    }
    
    return 0;
}

int reservationDelete(Reservation *reservation, Reservation *listReservation, int reservationNum, int user_reservation)
{
    UserWork userWork = DELETE5;
    Reservation deleteReservation;
    unsigned int number;
    int date;

    while(true)
    {
        // 삭제할 예약 내역 선택
        number = prompt_select_UserNumber(userWork, user_reservation);
        if(number == user_reservation + 1)
        {
            printf("초기 화면으로 돌아갑니다. \n");
            return 0;
        }

        // 오늘 날짜이면 삭제 불가
        date = todayDate();
        if(date != listReservation[number].date)
        {
            memcpy(&deleteReservation, &listReservation[number], sizeof(Reservation));
            break;
            
        }

        printf("오늘 날짜의 예약 내역은 삭제가 불가합니다. 다른 예약 내역을 선택해주세요.\n\n");
    }

    int idx = 1;
    while(idx <= reservationNum)
    {
        if(!memcmp(&reservation[idx], &deleteReservation, sizeof(Reservation)))
        {
            // 마지막 값 복사 및 마지막 값은 0으로 초기화 -> 예약 내역의 개수를 세기 위함
            memcpy(&reservation[idx], &reservation[reservationNum], sizeof(Reservation));
            memset(&reservation[reservationNum], 0, sizeof(Reservation));
            
            printf("선택하신 예약 내역이 삭제되었습니다.\n\n");

            printf("[삭제 내역]\n");
            printf("> 예약 일자(YYMMDD): %d\n", deleteReservation.date);
            printf("> 지점 번호: %d\n", deleteReservation.branchNum);
            printf("> 스터디 공간 번호: %d\n", deleteReservation.spaceNum);
            printf("> 예약 시간: %d\n", deleteReservation.start_time);
            printf("> 사용 예정 시간: %d\n", deleteReservation.use_time);
            printf("> 사용 인원: %d\n\n", deleteReservation.num_people);

            break;
        }

        ++idx;
    }

    return 0;
}

int hasReserved(Reservation *reservation, int reservationNum, char *userID)
{
    int user_reservation = 0;

    for(int i = 1; i <= reservationNum; ++i)
    {
        // reservation[i].userID == userID -> 기존 예약 내역이 존재한다(true)
        if(!strcmp(reservation[i].userID, userID))
        {
            ++user_reservation;
        }
    }
    
    return user_reservation;
}

bool isPossible_reservation(Reservation *reservation, int reservationNum, Reservation reservationInfo, int branchNum, int spaceNum, UserWork userWork, Reservation modify)
{
    bool isPossible = true;
    bool reservationInfo_time[HOUR];
    bool reservation_time[HOUR];

    memset(reservationInfo_time, 0, sizeof(bool) * HOUR);
    memset(reservation_time, 0, sizeof(bool) * HOUR);

    // 신규 예약 및 수정할 시간에 해당되면 true
    for(int i = reservationInfo.start_time; i < reservationInfo.start_time + reservationInfo.use_time; ++i)
    {
        reservationInfo_time[i] = true;
    }

    for(int i = 1; i <= reservationNum; ++i)
    {
        // 해당 지점이 아니면 날짜 및 시간대 볼 필요 없음
        if(reservation[i].branchNum != branchNum || reservation[i].spaceNum != spaceNum) continue;

        if(userWork == MODIFY5 && !memcmp(&reservation[i], &modify, sizeof(Reservation)))
        {
            continue;
        }

        // 동일한 날짜인가
        // 동일한 날짜에 동일한 지점 내 스터디 공간에 예약이 있을 때
        if(reservation[i].date == reservationInfo.date)
        {
            for(int j = reservation[i].start_time; j < reservation[i].start_time + reservation[i].use_time; ++j)
            {
                reservation_time[j] = true;
            }
            
            // 동일한 시간대인가
            for(int j = START_TIME; j < END_TIME; ++j)
            {
                // 둘 다 true -> 시간이 겹친다 -> 예약 불가
                if(reservationInfo_time[j] && reservation_time[j])
                {
                    isPossible = false;
                    break;
                }
            }

            // isPossible == false -> 예약이 불가하므로 더 이상 훑어볼 필요 없음
            if(!isPossible) break;

            // 다시 false로 초기화
            memset(reservation_time, 0, sizeof(bool) * HOUR);
        }
    }

    return isPossible;
}

bool isPossible_branch(Space space, Reservation reservationInfo)
{
    bool isPossible = true;

    if(space.max_people < reservationInfo.num_people)
    {
        isPossible = false;
    }

    return isPossible;
}

void showAll()
{
    FILE *fp;
    Branch branch[MAX_BRANCH + 1];
    char buf[MAX_BUF];

    // 파일 이름이 존재하지 않으면 -> 현재 존재하는 지점 및 스터디 공간 없음
    if(access(ADMIN_FILE, F_OK) < 0)
    {
        printf("현재 존재하는 스터디 지점 및 공간이 없습니다.\n\n");
    }
    else
    {
        // r+: 파일의 읽기/쓰기 가능 + 파일이 없을 때 에러 + 파일이 있을 때 처음부터 읽음
        if((fp = fopen(ADMIN_FILE, "r+")) == NULL)
        {
            fprintf(stderr, "%s 파일을 열 수 없습니다.\n", ADMIN_FILE);
            exit(1);
        }

        if(fread(&branch[1], sizeof(Branch), MAX_BRANCH, fp) != MAX_BRANCH)
        {
            fprintf(stderr, "%s 파일을 읽을 수 없습니다.\n", ADMIN_FILE);
            exit(1);
        }   

        printf("============    스터디 공간 조회 화면   ============\n");

        for(int i = 1; i <= MAX_BRANCH; ++i)
        {
            if(!strcmp(branch[i].name, "")) continue;

            for(int j = 1; j <= MAX_SPACE; ++j)
            {
                // 스터디 공간이 존재하는 경우에만 출력
                if(branch[i].isExist[j])
                {
                    printf("[%d번 지점: %s]\n", i, branch[i].name);
                    printf("> %d번 스터디 공간\n", j);
                    printf("  이름: %s, 최대 허용 인원수: %d, 책상 개수: %d, 컴퓨터 개수 %d\n", branch[i].space[j].name, branch[i].space[j].max_people, branch[i].space[j].desks, branch[i].space[j].computers);
                }
            }

            printf("\n");   
        }

        fclose(fp);
    }

    printf("아무거나 입력하면 초기 화면으로 돌아갑니다.\n");
    printf("> ");
    fgets(buf, sizeof(buf), stdin);

    return;
}

void showReservation(Reservation *listReservation, char *userID, int user_reservation)
{
    printf("============    %s님의 스터디 공간 예약 정보 조회 화면   ============\n", userID);

    for(int i = 1; i <= user_reservation; ++i)
    {
        printf("[%d]\n", i);
        printf("> 예약일자: %d\n", listReservation[i].date);
        printf("> 예약 공간: %d번 지점, %d번 스터디 공간\n", listReservation[i].branchNum, listReservation[i].spaceNum);
        printf("> 시작 예정 시간: %d시\n", listReservation[i].start_time);
        printf("> 종료 예정 시간: %d시\n", listReservation[i].start_time + listReservation[i].use_time);
        printf("> 총 예정 사용 시간: %d시간\n", listReservation[i].use_time);
        printf("> 인원수: %d명\n", listReservation[i].num_people);
        printf("\n");
    }

    return;
}

int showPossible(Reservation *reservation, int reservationNum, Reservation reservationInfo, int *branchNum, int *spaceNum, UserWork userWork, Reservation modify)
{
    FILE *fp;
    Branch branch[MAX_BRANCH + 1];
    int cnt = 0;

    // 구조체 branch 초기화
    // 처음 값: name == "", isExist == false, space.name == "", space.max_people, ... == 0
    for(int i = 0; i <= MAX_BRANCH; ++i)
    {
        memset(&branch[i], 0, sizeof(Branch));
    }

    // 이전에 파일 존재 여부 검사 미리 다함
    if((fp = fopen(ADMIN_FILE, "r+")) == NULL)
    {
        fprintf(stderr, "%s 파일을 열 수 없습니다.\n", ADMIN_FILE);
        exit(1);
    }

    if(fread(&branch[1], sizeof(Branch), MAX_BRANCH, fp) != MAX_BRANCH)
    {
        fprintf(stderr, "%s 파일을 읽을 수 없습니다.\n", ADMIN_FILE);
        exit(1);
    } 

    fclose(fp);

    printf("============    예약 가능한 스터디 공간 조회 화면   ============\n");

    // 존재하는 지점 중 존재하는 스터디 공간만 확인
    for(int i = 1; i <= MAX_BRANCH; ++i)
    {
        // branch[i].name == "" -> 존재하지 않는 지점
        if(!strcmp(branch[i].name, "")) continue;

        for(int j = 1; j <= MAX_SPACE; ++j)
        {   

            // branch[i].isExist[j] == false -> 존재하지 않는 스터디 공간
            if(!branch[i].isExist[j]) continue;

            // 입력된 사용 인원수가 스터디 공간의 최대 인원수보다 크면 -> false 리턴
            if(isPossible_branch(branch[i].space[j], reservationInfo))
            {
                // 예약 내역을 다 살펴본 결과, 예약 가능한 스터디 공간이면 -> true 리턴(출력)
                if(isPossible_reservation(reservation, reservationNum, reservationInfo, i, j, userWork, modify))
                {
                    ++cnt;
                    
                    branchNum[cnt] = i;
                    spaceNum[cnt] = j;

                    printf("[%d]\n", cnt);
                    printf("%d번 지점 %d번 스터디 공간\n", i, j);
                    printf("> 최대 허용 인원수: %d\n", branch[i].space[j].max_people);
                    printf("> 책상 개수: %d\n", branch[i].space[j].desks); 
                    printf("> 컴퓨터 개수: %d\n", branch[i].space[j].computers);  
                }
            }
        }

    }

    if(cnt == 0)
    {
        printf("입력한 예약 정보에 부합하는 스터디 공간이 없습니다.\n");
    }

    return cnt;
}


Mode prompt_select_Mode()
{
    int mode;
    
    while(true)
    {
        printf("============    실행 모드 선택 화면    ============\n");
        printf("관리자 모드: 1\n");
        printf("사용자 모드: 2\n");
        printf("프로그램 종료: 3\n");
        printf("> ");

        scanf("%d", &mode);

        // %d는 버퍼 값이 구분자인 경우에는 무시하고 다음 값을 읽지만
        // 버퍼 값이 문자인 경우에는 값을 읽지도, 무시하지도 못해서 무한루프에 빠지게 됨
        if(getchar() == '\n')
        {
            if(mode == ADMIN0 || mode == USER0 || mode == QUIT0) break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 번호가 입력되었습니다. 다시 입력해주세요.\n\n"); 
    }

    return (Mode)mode;
}

AdminWork prompt_select_AdminWork(AdminMode adminMode)
{
    char mode[MAX_BUF];
    int adminWork;

    switch (adminMode)
    {
        case BRANCH1: 
            strcpy(mode, "지점");
            break;

        case SPACE1: 
            strcpy(mode, "스터디 공간");
            break;

        default:
            fprintf(stderr, "에러\n");
            exit(1);
    }

    while(true)
    {
        printf("============   %s 내 작업 선택 화면    ============\n", mode);
        printf("추가: 1\n");
        printf("수정: 2\n");
        printf("삭제: 3\n");
        printf("초기 화면 이동: 4\n");
        printf("> ");

        scanf("%d", &adminWork);

        if(getchar() == '\n')
        {
            if(adminWork == ADD2 || adminWork == MODIFY2 || adminWork == DELETE2 || adminWork == INIT2) break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 번호가 입력되었습니다. 다시 입력해주세요.\n\n"); 
    }

    return (AdminWork)adminWork;
}

AdminMode prompt_select_Modify()
{
    int adminMode;

    while(true)
    {
        printf("============    수정 작업 선택 화면    ============\n");
        printf("지점 이름 수정: 1\n");
        printf("지점 내 스터디 공간 수정: 2\n");
        printf("초기 화면 이동: 3\n");
        printf("> ");

        scanf("%d", &adminMode);

        if(getchar() == '\n')
        {
            if(adminMode == BRANCH1 || adminMode == SPACE1 || adminMode == INIT1) break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 번호가 입력되었습니다. 다시 입력해주세요.\n\n"); 
    }

    return (AdminMode)adminMode;
}

unsigned int prompt_select_AdminNumber(AdminMode adminMode, AdminWork adminWork)
{
    char mode[MAX_BUF];
    char work[MAX_BUF];
    int max_num;
    unsigned int number;
    
    switch (adminMode)
    {
        case BRANCH1: 
            strcpy(mode, "지점");
            max_num = MAX_BRANCH;
            break;

        case SPACE1: 
            strcpy(mode, "스터디 공간");
            max_num = MAX_SPACE;
            break;

        default:
            fprintf(stderr, "에러\n");
            exit(1);
    }

    switch (adminWork)
    {
        case ADD2: 
            strcpy(work, "추가");
            break;

        case MODIFY2: 
            strcpy(work, "수정");
            break;

        case DELETE2: 
            strcpy(work, "삭제");
            break;

        default:
            fprintf(stderr, "에러\n");
            exit(1);
    }
    
    while(true)
    {
        printf("============   %s할 %s의 번호 선택 화면    ============\n", work, mode);
        printf("%s 번호: 1 ~ %d\n", mode, max_num);
        printf("초기 화면 이동: %d\n", max_num + 1);
        printf("> ");

        scanf("%d", &number);

        if(getchar() == '\n')
        {
            if(1 <= number && number <= max_num + 1) break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 번호가 입력되었습니다. 다시 입력해주세요.\n\n"); 

    }

    return number;
}

SpaceInfo prompt_select_SpaceInfo()
{
    int spaceInfo;

    while(true)
    {
        printf("============   스터디 공간 내 수정할 부분 선택 화면    ============\n");
        printf("스터디 공간의 이름: 1\n");
        printf("스터디 공간의 세부사항(최대 인원수, 책상 개수, 컴퓨터 개수): 2\n");
        printf("이름과 세부사항 모두 수정: 3\n");
        printf("> ");

        scanf("%d", &spaceInfo);

        if(getchar() == '\n')
        {
            if(spaceInfo == NAME3 || spaceInfo == INFO3 || spaceInfo == BOTH3 || spaceInfo == INIT3) break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 번호가 입력되었습니다. 다시 입력해주세요.\n\n"); 

    }
    
    return (SpaceInfo)spaceInfo;
}

int prompt_input_AdminStr(AdminMode adminMode, AdminWork adminWork, char *name)
{
    char buf[MAX_BUF];
    char mode[MAX_BUF];
    char work[MAX_LENGTH];
    int max_num;
    int len;
    
    switch (adminMode)
    {
        case BRANCH1: 
            strcpy(mode, "지점");
            max_num = MAX_BRANCH;
            break;

        case SPACE1: 
            strcpy(mode, "스터디 공간");
            max_num = MAX_SPACE;
            break;

        default:
            fprintf(stderr, "에러\n");
            exit(1);
    }

    // 지점 또는 지점 내 스터디 공간의 이름은 이를 추가하거나 수정할 때만 필요
    // 삭제할 때에는 고유번호로만 진행되므로, 관리자는 지점 또는 스터디 공간의 이름을 입력할 필요가 없음
    switch (adminWork)
    {
        case ADD2: 
            strcpy(work, "추가");
            break;

        case MODIFY2:
            strcpy(work, "수정");
            break;

        default:
            fprintf(stderr, "에러\n");
            exit(1);
    }

    while(true)
    {
        printf("============    %s할 %s 이름 입력 화면    ============\n", work, mode);
        printf("영문자 및 숫자 조합으로 최대 10글자까지 입력 가능합니다.\n");
        printf("초기화면으로 돌아가려면 아무 것도 입력하지 않은 상태에서 엔터를 누르세요.\n");
        printf("> ");

        memset(buf, 0, sizeof(buf)); // buf 초기화
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = '\0';

        len = strlen(buf);

        // 입력한 값이 10글자를 넘지 않으면 name에 입력받은 값 저장
        if(len <= 0)
        {
            return -1;
        }
        else if(len <= 10)
        {
            strcpy(name, buf);
            break;
        }
        else
        {
            printf("이름은 최소 1글자, 최대 10글자가 되어야합니다. 다시 입력해주세요.\n\n"); 
        }
    }

    return 0;
}

int prompt_input_Space(AdminWork adminWork, Space *space)
{
    int max_people = 0, desks = 0, computers = 0;
    char work[MAX_LENGTH];

    // 지점 내 스터디 공간의 정보는 추가하거나 수정할 때만 필요
    switch (adminWork)
    {
        case ADD2: 
            strcpy(work, "추가");
            break;

        case MODIFY2:
            strcpy(work, "수정");
            break;

        default:
            fprintf(stderr, "에러\n");
            exit(1);
    }

    printf("============    \"%s\" 스터디 공간의 세부 정보 %s 화면    ============\n", space->name, work);
    printf("초기 화면으로 이동하고 싶다면, 0을 입력해주세요.\n");

    // 그 외 멤버변수 -> 최대 허용 인원
    while(true)
    {
        printf("최대 허용 인원(최소 1명부터 최대 %d명까지 가능합니다.)\n", MAX_PEOPLE);
        printf("> ");

        scanf("%d", &max_people);

        if(getchar() == '\n')
        {
            if(max_people == 0) return -1;
            if(1 <= max_people && max_people <= MAX_PEOPLE) break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 인원 수가 입력되었습니다. 다시 입력해주세요.\n\n"); 
    }

    // 그 외 멤버변수 -> 책상 개수
    while(true)
    {
        printf("책상 개수(1개부터 최대 %d개까지 가능합니다.)\n", MAX_DESK);
        printf("> ");

        scanf("%d", &desks);

        if(getchar() == '\n')
        {
            if(desks == 0) return -1;
            if(1 <= desks && desks <= MAX_DESK) break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 개수가 입력되었습니다. 다시 입력해주세요.\n\n"); 
    }

    // 그 외 멤버변수 -> 컴퓨터 개수
    while(true)
    {
        printf("컴퓨터 개수(최소 1개부터 최대 %d개까지 가능합니다.)\n", MAX_COMPUTER);
        printf("> ");

        scanf("%d", &computers);

        if(getchar() == '\n')
        {
            if(computers == 0) return -1;
            if(1 <= computers && computers <= MAX_COMPUTER) break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 개수가 입력되었습니다. 다시 입력해주세요.\n\n"); 
    }

    space->max_people = max_people;
    space->desks = desks;
    space->computers = computers;

    return 0;
}

UserMode prompt_select_UserMode(char *userID, int user_reservation)
{
    int userMode;
    
    while(true)
    {
        printf("============   %s님의 작업 선택 화면    ============\n", userID);
        printf("스터디 공간 조회: 1\n");
        printf("신규 예약: 2\n");
        printf("예약 내역 조회: 3\n");
        printf("초기 화면 이동: 4\n");
        printf("> ");

        scanf("%d", &userMode);

        if(getchar() == '\n')
        {
            if(userMode == SPACE_INFO4 || userMode == NEW4 || userMode == INIT4) break;

            // 기존에 예약 내역이 있는 사용자인 경우에만 예약 내역 조회 가능
            // user_reservation == 0 -> 기존 예약 내역이 없음
            if(userMode == RESERVATION_INFO4)
            {
                if(user_reservation) break;
                else printf("%s님의 예약 내역이 존재하지 않으므로, 스터디 공간 조회 및 신규 예약만 가능합니다.\n\n", userID);

                continue;
            }
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 번호가 입력되었습니다. 다시 입력해주세요.\n\n"); 
    }

    return (UserMode)userMode;
}

UserWork prompt_select_UserWork(char *userID)
{
    int userWork;

    while(true)
    {
        printf("%s님의 예약 내역 다시 조회: 1\n", userID);
        printf("예약 내역 수정: 2\n");
        printf("예약 내역 삭제: 3\n");
        printf("초기 화면 이동: 4\n");
        printf("> ");

        scanf("%d", &userWork);

        if(getchar() == '\n')
        {
            if(userWork == SHOW5 || userWork == MODIFY5 || userWork == DELETE5 || userWork == INIT5) break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 번호가 입력되었습니다. 다시 입력해주세요.\n\n"); 
    }

    return (UserWork)userWork;
}

unsigned int prompt_select_UserNumber(UserWork userWork, int user_reservation)
{
    char work[MAX_BUF];
    unsigned int number;

    switch(userWork)
    {
        case ADD5:
            strcpy(work, "신규예약");
            break;
        
        case MODIFY5: 
            strcpy(work, "수정");
            break;

        case DELETE5: 
            strcpy(work, "삭제");
            break;

        default:
            fprintf(stderr, "에러\n");
            exit(1);
    }

    while(true)
    {
        printf("============   %s할 번호 선택 화면    ============\n", work);
        printf("%s할 [번호]를 입력하세요.\n", work);
        printf("초기 화면으로 이동하려면 %d를 입력하세요.\n", user_reservation + 1);
        printf("> ");

        scanf("%d", &number);

        if(getchar() == '\n')
        {
            if(1 <= number && number <= user_reservation + 1) break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 번호가 입력되었습니다. 다시 입력해주세요.\n\n"); 

    }
    
    return number;
}

int prompt_input_UserStr(char *userID)
{
    char buf[MAX_BUF];
    int len = 0;

    while(true)
    {
        printf("============    사용자 ID 입력 화면    ============\n");
        printf("영문자 및 숫자 조합으로 최소 5글자, 최대 10글자까지 입력 가능합니다.\n");
        printf("초기화면으로 돌아가려면 아무 것도 입력하지 않은 상태에서 엔터를 누르세요.\n");
        printf("> ");

        memset(buf, 0, sizeof(buf)); // buf 초기화
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = '\0';

        len = strlen(buf);

        if(len <= 0)
        {
            return -1;
        }

        // 입력한 값이 5~10글자이면 입력받은 값 저장
        if(5 <= len && len <= 10)
        {
            strcpy(userID, buf);
            break;
        }
        else
        {
            printf("이름은 최소 5글자, 최대 10글자가 되어야합니다. 다시 입력해주세요.\n\n"); 
        }
    }
    
    return 0;
}

int prompt_input_Reservation(UserWork userWork, Reservation *reservation)
{
    int date = 0, branchNum = 0, spaceNum = 0, start_time = 0, use_time = 0, num_people = 0;
    int today;
    char work[MAX_BUF];

    // 지점 내 스터디 공간의 정보는 추가하거나 수정할 때만 필요
    switch (userWork)
    {
        case ADD5: 
            strcpy(work, "신규 예약");
            break;

        case MODIFY5:
            strcpy(work, "수정");
            break;

        default:
            fprintf(stderr, "에러\n");
            exit(1);
    }

    today = todayDate();

    printf("============    %s할 예약 정보 입력 화면    ============\n", work);
    printf("초기화면으로 돌아가려면 0을 입력하세요.\n");

    // 예약 일자
    while(true)
    {
        printf("예약 일자(YYMMDD)\n");
        printf("> ");

        scanf("%d", &date);

        if(getchar() == '\n')
        {
            if(date == 0) return -1;
            
            //  자릿수가 6이 아니면 잘못된 값 입력된 것
            int cnt = 0, num = date;
            while(num != 0)
            {
                num = num / 10;
                ++cnt;
            }
            if(cnt != 6)
            {
                printf("예약 일자는 6자리 숫자(YYMMDD)로 입력해주세요.\n\n");
                continue;
            }

            // 유효한 날짜인지 체크 -> 유효하지 않은 날짜이면 false 리턴
            if(!checkDate(date))
            {
                printf("%d는 존재하지 않는 일자입니다. 다시 입력해주세요.\n\n", date);
                continue;
            }

            // 당일 예약 불가 -> 다음날부터 가능
            if(date <= today)
            {
                printf("내일 날짜(%d)부터 %s이 가능합니다. 다시 입력해주세요.\n\n", today + 1, work);
                continue;
            }

            break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 예약일자가 입력되었습니다. 다시 입력해주세요.\n\n"); 
    }

    // 사용 인원
    while(true)
    {
        printf("사용 인원(최소 1명부터 최대 %d명까지 입력 가능합니다.)\n", MAX_PEOPLE);
        printf("> ");

        scanf("%d", &num_people);


        if(getchar() == '\n')
        {
            if(num_people == 0) return -1;
            
            if(1 <= num_people && num_people <= MAX_PEOPLE) break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 인원 수가 입력되었습니다. 다시 입력해주세요.\n\n"); 
    }

    // 예약 시작 시간
    while(true)
    {
        printf("시작 시간(8~21시 사이의 시간을 입력해주세요.)\n");
        printf("> ");

        scanf("%d", &start_time);


        if(getchar() == '\n')
        {
            if(start_time == 0) return -1;
            
            if(START_TIME <= start_time && start_time < END_TIME) break;
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 시간이 입력되었습니다. 다시 입력해주세요.\n\n"); 
    }

    // 사용 시간
    while(true)
    {
        printf("사용 시간(시간 단위로 입력해주세요.)\n");
        printf("> ");

        scanf("%d", &use_time);

        if(getchar() == '\n')
        {
            if(use_time == 0) return -1;

            if(1 <= use_time && use_time + start_time <= END_TIME) break;

            if(use_time < 1 || END_TIME - START_TIME < use_time )
            {
                printf("올바르지 않은 시간이 입력되었습니다. 다시 입력해주세요.\n\n"); 
            }
            else if(use_time + start_time > END_TIME)
            {
                printf("%d시 이후로는 이용할 수 없습니다. 다시 입력해주세요.\n\n", END_TIME);
            }
        }
        else
        {
            while(getchar() != '\n');
        }

        printf("올바르지 않은 시간이 입력되었습니다. 다시 입력해주세요.\n\n"); 
    }

    reservation->date = date;
    reservation->start_time = start_time;
    reservation->use_time = use_time;
    reservation->num_people = num_people;

    return 0;
}

int todayDate()
{
    int year, month, day, today;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    year = (tm.tm_year + 1900) - 2000;
    month = tm.tm_mon + 1;
    day = tm.tm_mday;

    today = year * 10000 + month * 100 + day;

    return today;
}

bool checkDate(int date)
{
    bool isExist = false;
    int allMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year = date / 10000;
    int month = (date - year * 10000) / 100;
    int day = date - year * 10000 - month * 100;

    // 윤년인지 검사 -> 윤년이면 true 리턴
    if(checkYear(2000 + year))
    {
        if (month >= 1 && month <= 12)
        {
			if (month != 2)
            {
				if (day > 0 && day <= allMonth[month - 1]) isExist = true;
			}
			else 
            {
				if (day > 0 && day <= 29) isExist = true;
			}
		}
    }
    else
    {
        if (month >= 1 && month <= 12)
        {
			if (day > 0 && day <= allMonth[month - 1]) isExist = true;
		}
    }
    
    return isExist;
}

bool checkYear(int year)
{
    if (year % 4 != 0) {
		return false;
	}
	else {
		if (year % 100 != 0) {
			return true;
		}
		else {
			if (year % 400 == 0) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}