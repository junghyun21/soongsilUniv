/*
 * my_assembler 함수를 위한 변수 선언 및 매크로를 담고 있는 헤더 파일이다.
 *
 */
#define MAX_INST 256
#define MAX_DIRECTIVE 128
#define MAX_LINES 5000
#define MAX_OPERAND 3
#define MAX_BUF 1024
#define MAX_CONTROLSECTION 10

#define N 0x20
#define I 0x10
#define X 0x08
#define B 0x04
#define P 0x02
#define E 0x01

#define TRUE 1
#define FALSE 0

enum token_item{
    LABEL
    , OPERATOR
    , OPERAND
    , COMMENT
};


 /*
  * instruction 목록 파일로 부터 정보를 받아와서 생성하는 구조체 변수이다.
  * 라인 별로 하나의 instruction을 저장한다.
  */
struct inst_unit
{
	char str[10]; // instruction의 이름
	unsigned char op; // 명령어의 OPCODE
	int format; // instrcution의 형식
	int ops; // instruction의 operand 개수
};
typedef struct inst_unit inst;
inst* inst_table[MAX_INST];
int inst_index;

/*
 * 어셈블리 할 소스코드를 입력받는 테이블이다. 라인 단위로 관리할 수 있다.
 */
char* input_data[MAX_LINES];
static int line_num;

/*
 * 어셈블리 할 소스코드를 토큰단위로 관리하기 위한 구조체 변수이다.
 * operator는 renaming을 허용한다.
 */
struct token_unit
{
	char* label;
	char* operator;
	char* operand[MAX_OPERAND];
	char comment[100];
	char nixbpe;
};

typedef struct token_unit token;
token* token_table[MAX_LINES];
static int token_line;

/*
 * 심볼을 관리하는 구조체이다.
 * 심볼 테이블은 심볼 이름, 심볼의 위치로 구성된다.
 */
struct symbol_unit
{
	char symbol[10];
	int addr;
};
typedef struct symbol_unit symbol;
symbol sym_table[MAX_LINES];
static int sym_line;

/*
* 리터럴을 관리하는 구조체이다.
* 리터럴 테이블은 리터럴의 이름, 리터럴의 위치로 구성된다.
*/
struct literal_unit {
	char* literal;
    int len;
	int addr;
};
typedef struct literal_unit literal;
literal literal_table[MAX_LINES];
static int literal_line;
static int literal_addr;

/*
* control section을 관리하는 구조체이다.
* control section 테이블은 section의 이름, section의 길이로 구성된다.
*/
struct control_section
{
    char header[10];
    int length;
};
typedef struct control_section cs;
cs section_table[MAX_CONTROLSECTION];
static int count_section;


static int locctr;
//--------------

static char* input_file;
static char* output_file;
int init_my_assembler(void);
int init_inst_file(char* inst_file);
int init_input_file(char* input_file);
int token_parsing(char* str);
int search_opcode(char* str);
static int assem_pass1(void);
void make_opcode_output(char* file_name);

void make_symtab_output(char* file_name);
static int assem_pass2(void);
void make_objectcode_output(char* file_name);
void make_literaltab_output(char* file_name);

int search_symtab(char* label ,int sym_start);
int search_littab(char* literal, int literal_start);

