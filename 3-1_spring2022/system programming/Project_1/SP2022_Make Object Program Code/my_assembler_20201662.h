/*
 * my_assembler �Լ��� ���� ���� ���� �� ��ũ�θ� ��� �ִ� ��� �����̴�.
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
  * instruction ��� ���Ϸ� ���� ������ �޾ƿͼ� �����ϴ� ����ü �����̴�.
  * ���� ���� �ϳ��� instruction�� �����Ѵ�.
  */
struct inst_unit
{
	char str[10]; // instruction�� �̸�
	unsigned char op; // ��ɾ��� OPCODE
	int format; // instrcution�� ����
	int ops; // instruction�� operand ����
};
typedef struct inst_unit inst;
inst* inst_table[MAX_INST];
int inst_index;

/*
 * ����� �� �ҽ��ڵ带 �Է¹޴� ���̺��̴�. ���� ������ ������ �� �ִ�.
 */
char* input_data[MAX_LINES];
static int line_num;

/*
 * ����� �� �ҽ��ڵ带 ��ū������ �����ϱ� ���� ����ü �����̴�.
 * operator�� renaming�� ����Ѵ�.
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
 * �ɺ��� �����ϴ� ����ü�̴�.
 * �ɺ� ���̺��� �ɺ� �̸�, �ɺ��� ��ġ�� �����ȴ�.
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
* ���ͷ��� �����ϴ� ����ü�̴�.
* ���ͷ� ���̺��� ���ͷ��� �̸�, ���ͷ��� ��ġ�� �����ȴ�.
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
* control section�� �����ϴ� ����ü�̴�.
* control section ���̺��� section�� �̸�, section�� ���̷� �����ȴ�.
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

