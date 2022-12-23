/*
 * ȭ�ϸ� : my_assembler_00000000.c
 * ��  �� : �� ���α׷��� SIC/XE �ӽ��� ���� ������ Assembler ���α׷��� ���η�ƾ����,
 * �Էµ� ������ �ڵ� ��, ��ɾ �ش��ϴ� OPCODE�� ã�� ����Ѵ�.
 * ���� ������ ���Ǵ� ���ڿ� "00000000"���� �ڽ��� �й��� �����Ѵ�.
 */

/*
 *
 * ���α׷��� ����� �����Ѵ�.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>

// ���ϸ��� "00000000"�� �ڽ��� �й����� ������ ��.
#include "my_assembler_20201662.h"

/* ------------------------------------------------------------ * ���� : ����ڷ� ���� ����� ������ �޾Ƽ� ��ɾ��� OPCODE�� ã�� ����Ѵ�.
 * �Ű� : ���� ����, ����� ����
 * ��ȯ : ���� = 0, ���� = < 0
 * ���� : ���� ����� ���α׷��� ����Ʈ ������ �����ϴ� ��ƾ�� ������ �ʾҴ�.
 *           ���� �߰������� �������� �ʴ´�.
 * ------------------------------------------------------------ */
int main(int args, char *arg[])
{
    if (init_my_assembler() < 0)
    {
        printf("init_my_assembler: ���α׷� �ʱ�ȭ�� ���� �߽��ϴ�.\n");
        return -1;
    }

    if (assem_pass1() < 0)
    {
        printf("assem_pass1: �н�1 �������� �����Ͽ����ϴ�.\n");
        return -1;
    }

    // make_opcode_output(NULL);

    // make_symtab_output("symtab_20201662");
    make_symtab_output(NULL);
//    make_literaltab_output("literaltab_20201662");
//    if (assem_pass2() < 0)
//    {
//        printf(" assem_pass2: �н�2 �������� �����Ͽ����ϴ�.  \n");
//        return -1;
//    }
//
//    make_objectcode_output("output_20201662");
    
    return 0;
}

/* ------------------------------------------------------------ * ���� : ���α׷� �ʱ�ȭ�� ���� �ڷᱸ�� ���� �� ������ �д� �Լ��̴�.
 * �Ű� : ����
 * ��ȯ : �������� = 0 , ���� �߻� = -1
 * ���� : ������ ��ɾ� ���̺��� ���ο� �������� �ʰ� ������ �����ϰ� �ϱ� ���ؼ�
 *       ���� ������ �����Ͽ� ���α׷� �ʱ�ȭ�� ���� ������ �о� �� �� �ֵ���
 *       �����Ͽ���.
 * ------------------------------------------------------------ */

//
int init_my_assembler(void)
{
    int result;

    if ((result = init_inst_file("inst.data")) < 0)
        return -1;
    if ((result = init_input_file("input.txt")) < 0)
        return -1;
    
    
    return result;
}

/* ----------------------------------------------------------------------------------
 * ���� : �ӽ��� ���� ��� �ڵ��� ������ �о� ���� ��� ���̺�(inst_table)��
 *        �����ϴ� �Լ��̴�.
 * �Ű� : ���� ��� ����
 * ��ȯ : �������� = 0 , ���� < 0
 * ���� : ���� ������� ������ �����Ӱ� �����Ѵ�. ���ô� ������ ����.
 *
 *    ===============================================================================
 *           | �̸� | ���� | ���� �ڵ� | ���۷����� ���� | NULL|
 *    ===============================================================================
 *
 * ----------------------------------------------------------------------------------
 */
int init_inst_file(char *inst_file)
{
    FILE *file = NULL;
    char *mode = "r";
    char buf[MAX_BUF] = "\0";
    char *ptr = NULL;
    
    // inst.data ���� open -> ���� ��, �����޼��� ��� �� -1 ����
    if((file = fopen(inst_file, mode)) == NULL)
    {
        perror("fopen error");
        return -1;
    }

    // ������ ���� ������ �����͸� �� �پ� �о��
    // �о�� �����͸� '\t'�� �������� ������ ���� ����
    // fgets: ���๮�ڸ� ����(���๮�ڱ���)���� �����͸� �о�� + �� ���� �����Ͱ� ������ NULL�� ��ȯ
    // inst_index: inst�� ����
    while(fgets(buf, sizeof(buf), file) != NULL)
    {
        inst_table[inst_index] = (inst*)malloc(sizeof(inst));
        
        ptr = strtok(buf, "\r\n");  // ���๮�� ����
        
        // "\t"�� �������� �� ������ ����
        ptr = strtok(ptr, "\t");
        strcpy(inst_table[inst_index]->str, ptr);
        
        ptr = strtok(NULL, "\t");
        inst_table[inst_index]->op = strtol(ptr, NULL, 16); // 16������ ��ȯ
        
        ptr = strtok(NULL, "\t");
        inst_table[inst_index]->format = atoi(ptr);
        
        ptr = strtok(NULL, "\t");
        inst_table[inst_index]->ops = atoi(ptr);
        
        ++inst_index; // inst_table���� ���� ����(��ɾ� ����) ����
    }

    fclose(file);
    
    return 0;
}

/* ----------------------------------------------------------------------------------
 * ���� : ����� �� �ҽ��ڵ带 �о� �ҽ��ڵ� ���̺�(input_data)�� �����ϴ� �Լ��̴�.
 * �Ű� : ������� �ҽ����ϸ�
 * ��ȯ : �������� = 0 , ���� < 0
 * ���� : ���δ����� �����Ѵ�.
 *
 * ----------------------------------------------------------------------------------
 */
int init_input_file(char *input_file)
{
    FILE *file = NULL;
    char *mode = "r";
    char buf[MAX_BUF] = "\0";
    
    if((file = fopen(input_file, mode)) == NULL)
    {
        perror("fopen error");
        return -1;
    }
    
    // input_file�� ���� �����͸� �� �پ� �о�ͼ� input_data�� ������
    while(fgets(buf, sizeof(buf), file) != NULL)
    {
        input_data[line_num] = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
        strcpy(input_data[line_num++], buf);
    }

    fclose(file);
    
    return 0;
}

/* ----------------------------------------------------------------------------------
 * ���� : �ҽ� �ڵ带 �о�� ��ū������ �м��ϰ� ��ū ���̺��� �ۼ��ϴ� �Լ��̴�.
 *        �н� 1�� ���� ȣ��ȴ�.
 * �Ű� : �Ľ��� ���ϴ� ���ڿ�
 * ��ȯ : �������� = 0 , ���� < 0
 * ���� : my_assembler ���α׷������� ���δ����� ��ū �� ������Ʈ ������ �ϰ� �ִ�.
 * ----------------------------------------------------------------------------------
 */
int token_parsing(char *str)
{
    char *ptr = NULL;
    int cnt_tab = 0;
    int idx = 0;
    int len_operand = 0;
    
    token_table[token_line] = (token*)malloc(sizeof(token));
    
    // �ʱ�ȭ
    token_table[token_line]->label = NULL;
    token_table[token_line]->operator = NULL;
    for(int i = 0; i < MAX_OPERAND; ++i)
    {
        token_table[token_line]->operand[i] = NULL;
    }
    strcpy(token_table[token_line]->comment, "");
    token_table[token_line]->nixbpe = 0x00; // 00000000
    
    
    // strtok�� ���ӵ� �����ڸ� ������ ��, �� ���ڿ��� ��ȯ���� ����
    // ���ӵ� �����ڵ� �����ؾ��ϴ� ��찡 �־ �ڵ� ���� �ۼ���
    // ex. RSUB ... -> ...�� command�� �ƴ� operand�� �����
    // �ƿ��� ������ \r\n���� ����
    while(str[idx] != '\r' && str[idx] != '\n')
    {
        char buf[MAX_BUF] = "\0";
        int i = 0;
        
        // ������ ������ ������ buf�� �� ����
        while(TRUE)
        {
            if(str[idx] == '\t' || str[idx] == '\r')
            {
                ++idx;
                break;
            }
            
            buf[i++] = str[idx++];
        }
        
        // �� token�� ����
        // buf�� ���ڿ��̸� �ʱ�ȭ ���� NULL ���� -> �� ���� �� �������� ����
        // buf�� ���ڿ��� �ƴ� ��, �Ʒ� �ڵ�� ����
        if(strcmp(buf, ""))
        {
            // label
            if(cnt_tab == LABEL)
            {
                token_table[token_line]->label = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
                strcpy(token_table[token_line]->label, buf);
                
                // label ��ġ�� "."�� �ִ� ��� -> �ּ��� ���
                // �ּ� ǥ��(.)�� �ְų� or �ּ� ǥ�� �ڿ� comment�� �ٰų� -> 2���� ���
                if(!strcmp(token_table[token_line]->label, "."))
                {
                    cnt_tab = COMMENT;
                    continue;
                }
            }
            // operator
            else if(cnt_tab == OPERATOR)
            {
                token_table[token_line]->operator = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
                strcpy(token_table[token_line]->operator, buf);
            }
            // operand
            else if(cnt_tab == OPERAND)
            {
                int i = 0;
                // operand�� ',' �������� ����� ����
                ptr = strtok(buf, ",");
                
                while(ptr != NULL && i < MAX_OPERAND)
                {
                    ++len_operand;

                    token_table[token_line]->operand[i] = (char*)malloc(sizeof(char) * (strlen(ptr) + 1));
                    strcpy(token_table[token_line]->operand[i++], ptr);

                    ptr = strtok(NULL, ",");
                }
            }
            // command
            else if(cnt_tab == COMMENT)
            {
                strcpy(token_table[token_line]->comment, buf);
            }
            // token�� �Է� ������ ������ ���� �ԷµǾ��� �� -> error
            else
            {
                return -1;
            }
        }
        
        ++cnt_tab;
    }
    
    // token_table[token_line]->nixbpe�� �� ����
    
//    // n = 1, i = 1 (simple addressing in SIC/XE)
//    token_table[token_line]->nixbpe |= N;
//    token_table[token_line]->nixbpe |= I;
//
//    // �Ľ̵� ���� ���� n,i,e �� �ۼ�
//    // x�� assem_pass1���� Ȯ�� -> inst_table���� ops���� operand ���� ��, ���� �ʴ� ��� -> 1. �����ų�, 2. x�̰ų�(== x=1)
//    // b, p�� location conter �� ������ opcode ������ �� (�ֳ��ϸ� �� �ּҰ����� �˾ƾ� ��)
//    // operand: @->indirect(n=1, i=0), #->immediate(n=0, i=1)
//    // operator: +->4����(e=1)
//
//    // operator�� '+'�� �����ϸ� 4���� -> e = 1
//    if(token_table[token_line]->operator != NULL && token_table[token_line]->operator[0] == '+')
//    {
//        token_table[token_line]->nixbpe |= E;
//    }
//
//    idx = 0;
//    // n = 1, i = 1�� ����
//    while(token_table[token_line]->operand[idx] != NULL && idx < MAX_OPERAND)
//    {
//        // operand�� @�� �����ϸ� indirect addressing -> n = 1, i = 0
//        if(token_table[token_line]->operand[idx][0] == '@')
//        {
//            token_table[token_line]->nixbpe &= ~I;
//        }
//
//        // operand�� #�� �����ϸ� immediate addressing -> n = 0, i = 1
//        if(token_table[token_line]->operand[idx][0] == '#')
//        {
//            token_table[token_line]->nixbpe &= ~N;
//        }
//
//        ++idx;
//    }
    
    ++token_line;
    
    return len_operand;
}

/* ----------------------------------------------------------------------------------
 * ���� : �Է� ���ڿ��� ���� �ڵ������� �˻��ϴ� �Լ��̴�.
 * �Ű� : ��ū ������ ���е� ���ڿ�
 * ��ȯ : �������� = ���� ���̺� �ε���, ���� < 0
 * ���� :
 *
 * ----------------------------------------------------------------------------------
 */
int search_opcode(char *str)
{
    int idx = 0;
    
    if(str[0] == '+')
    {
        str = strtok(str, "+");
    }
    
    // �Է� ���ڿ�(��ɾ�)�� �ش��ϴ� opcode�� ������ �ش� opcode�� ��ġ�� ���̺��� �ε��� ����
    while(idx < inst_index)
    {
        if(!strcmp(str, inst_table[idx]->str))
        {
            break;
        }
        
        ++idx;
    }
    
    return idx;
}

/* ----------------------------------------------------------------------------------
 * ���� : �Է� label�� SYMTAB�� �̹� �����ϴ��� �˻��ϴ� �Լ��̴�.
 * �Ű� : label, �˻縦 ������ �ε���
 * ��ȯ : �̹� ������ �� = �ش� �ε��� ����, �������� ���� �� = -1 ����
 * ���� :
 *
 * ----------------------------------------------------------------------------------
 */
int search_symtab(char* label, int sym_start)
{
    for(int i = sym_start; i < sym_line; ++i)
    {
        if(!strcmp(label, sym_table[i].symbol))
        {
            return i;
        }
    }
    
    return -1;
}

/* ----------------------------------------------------------------------------------
 * ���� : �Է� literal�� LITTAB�� �̹� �����ϴ����� �˻��ϴ� �Լ��̴�.
 * �Ű� : literal, �˻縦 ������ �ε���
 * ��ȯ : �̹� ������ �� = �ش� �ε��� ����, �������� ���� �� = -1 ����
 * ���� :
 *
 * ----------------------------------------------------------------------------------
 */
int search_littab(char* literal, int literal_start)
{
    
}

/* ----------------------------------------------------------------------------------
* ���� : ����� �ڵ带 ���� �н�1������ �����ϴ� �Լ��̴�.
*           �н�1������..
*           1. ���α׷� �ҽ��� ��ĵ�Ͽ� �ش��ϴ� ��ū������ �и��Ͽ� ���α׷� ���κ� ��ū
*           ���̺��� �����Ѵ�.
*
* �Ű� : ����
* ��ȯ : ���� ���� = 0 , ���� = < 0
* ���� : ���� �ʱ� ���������� ������ ���� �˻縦 ���� �ʰ� �Ѿ �����̴�.
*      ���� ������ ���� �˻� ��ƾ�� �߰��ؾ� �Ѵ�.
*
* -----------------------------------------------------------------------------------
*/
static int assem_pass1(void)
{
    int index;
    int start_addr = 0;
    int sym_start = 0;
    int literal_start = 0;
    
    // input_data�� �޾ƿ� ������ �� �پ� parsing
    for(int i = 0; i < line_num; ++i)
    {
        if(token_parsing(input_data[i]) > MAX_OPERAND)
        {
            fprintf(stdout, "token_parsing() call error\n");
            return -1;
        }
    }
    
    // pass 1
    // 1. opcode�� �����Ͽ� ��ɾ� ���� �ľ�
    // 2. ��ɾ� or ����� ���þ��� ���� ���� location counter ũ�� ����
    // 3. program block�� ������ location counter 0���� �ʱ�ȭ
    // 4. ���ο� label ������ SYMTAB�� label�� ���� location counter ����
    // 5. ���ο� literal ������ LITTAB�� literal ����
    // 6. LTORG�� ���α׷� ���� ������ ���� location counter�� literal�� ����Ʈ ���� ����Ͽ� ����
    
    // �����ּ�: START��� ����� ���þ� �ڿ� ���� ���� �����ּ���
    if(!strcmp(token_table[0]->operator, "START"))
    {
        start_addr = atoi(token_table[0]->operand[0]);
        locctr = start_addr;
        
        // section�� header �̸� ����
        strcpy(section_table[count_section].header, token_table[0]->label);
    }
    
    for(int i = 0; i < token_line; ++i)
    {
        // token_table[i]->operator == NULL -> operator�� ����� ���þ �Էµ��� ����
        if(token_table[i]->operator == NULL)
        {
            continue;
        }
        
        // CSECT: ���ο� section���� ��Ÿ��
        if(!strcmp(token_table[i]->operator, "CSECT"))
        {
            // ���� section�� ���� ����
            section_table[count_section].length = locctr - start_addr;
            
            // ���ο� section�� ���۵Ǿ����Ƿ�, section�� ���� ����
            ++count_section;
            
            // section�� header �̸� ����
            strcpy(section_table[count_section].header, token_table[i]->label);
            
            start_addr = 0;
            locctr = start_addr;
            
            // SYMTAB���� ������ label�� ���� ��쿡�� label ����
            // <but> �ٸ� section�� ���, ������ label ����ص� ��� ����
            // -> ���̺� ���� ������ label�� �����ϴ��� Ȯ���� ��, ���� section �������� �˻��ϱ� ����
            // litearl�� SYMTAB�� ���� ����
            sym_start = sym_line;
            literal_start = literal_line;
        }
        
        // SYMTAB �ۼ�
        // token_table[i]->label == NULL -> label�� �������� ����
        if(token_table[i]->label != NULL)
        {
            // token_table[i]->label == "." -> �ּ��̹Ƿ� object program�� ���� �� �ʿ� ����
            if(!strcmp(token_table[i]->label, "."))
            {
                continue;
            }
            // opeartor�� EQU�̰� operand�� *�� ��� -> �ּҿ� ���� locctr �� ����
            // opeartor�� EQU�̰� operand�� *�� �ƴ� ��� -> �ּҿ� �����ּ� �� ����
            // �Ʒ��� ������ �����
            //
            else if(!strcmp(token_table[i]->operator, "EQU") && strcmp(token_table[i]->operator, "*"))
            {
                // ��ü SYMTAB�� �Ⱦ���ϹǷ�, �˻縦 ������ �ε���(�ι�° ����)�� 0
                //
                if(search_symtab(token_table[i]->label, 0) < 0)
                {
                    
                }
            }
            else
            {
                // ������ section�� SYMTAB�� ������ label�� �����ϴ��� Ȯ��
                // �����ϸ�(search_symtab() >= 0) label�� ���̺� �������� ����
                if(search_symtab(token_table[i]->label, sym_start) < 0)
                {
                    // SYMTAB�� �������� �ʴ� label�� ��쿡�� ����
                    strcpy(sym_table[sym_line].symbol, token_table[i]->label);
                    sym_table[sym_line].addr = locctr;
                    
                    ++sym_line;
                }
            }
        }
        
        // LITTAB �ۼ� -> literal �̸� ����
        for(int j = 0; j < MAX_OPERAND; ++j)
        {
            // token_table[i]->operand[j] == NULL -> �� �ڷ� �� �̻� operand �������� ����
            if(token_table[i]->operand[j] == NULL)
            {
                break;
            }
            
            isExist = FALSE;
            
            // literal�� �� �տ� '='�� ����
            if(token_table[i]->operand[j][0] == '=')
            {
                // ptr: literal�� ����� �˱� ���� ex. C, X, ...
                // str: literal�� �̸��� �˱� ���� ex. =C'EOF' -> str = EOF
                char *ptr, *str;
                ptr = strtok(token_table[i]->operand[j], "=");
                ptr = strtok(NULL, "'");
                str = strtok(NULL, "'");
                
                // ������ section�� LITTAB�� ������ literal�� �����ϴ��� Ȯ��
                // �����ϸ� litearl�� ���̺� �������� ����
                for(int k = literal_start; k < literal_line; ++k)
                {
                    if(!strcmp(sym_table[j].symbol, str))
                    {
                        isExist = TRUE;
                        break;
                    }
                }
                
                // LITTAB�� �������� �ʴ� literal�� ��쿡�� ����
                if(!isExist)
                {
                    literal_table[literal_line].literal = (char*)malloc(sizeof(char) * (strlen(str) + 1));
                    strcpy(literal_table[literal_line].literal, str);
                    
                    // literal�� ũ��
                    if(ptr[0] == 'C')
                    {
                        literal_table[literal_line].len = (int)strlen(str);
                    }
                    else if(ptr[0] == 'X')
                    {
                        literal_table[literal_line].len = 1;
                    }
                    else
                    {
                        fprintf(stdout, "literal error\n");
                        return -1;
                    }
                    
                    ++literal_line;
                }
            }
        }
        
        // LITTAB �ۼ� -> literal �ּ� ����
        if(!strcmp(token_table[i]->operator, "LTORG"))
        {
            // �ּҰ� ���� �ȵ� literal���� �ּҸ� LITTAB�� ����
            while(literal_addr < literal_line)
            {
                literal_table[literal_addr].addr = locctr;
                locctr += literal_table[literal_addr].len;
                
                ++literal_addr;
            }
        }
        else if(!strcmp(token_table[i]->operator, "END"))
        {
            // �ּҰ� ���� �ȵ� literal���� �ּҸ� LITTAB�� ����
            while(literal_addr < literal_line)
            {
                literal_table[literal_addr].addr = locctr;
                locctr += literal_table[literal_addr].len;
                
                ++literal_addr;
            }
            
            // ������ section�� ũ�� ����
            section_table[count_section].length = locctr - start_addr;
        }
        // '����� ���þ�' ���� lacation counter ũ�� ����
        // location counter�� �����ϴ� ��� -> WORD, BYTE, RESW, RESB
        else if(!strcmp(token_table[i]->operator, "WORD"))
        {
            
            
        }
        else if(!strcmp(token_table[i]->operator, "BYTE"))
        {
            
        }
        else if(!strcmp(token_table[i]->operator, "RESW"))
        {
            
        }
        else if(!strcmp(token_table[i]->operator, "RESB"))
        {
            
        }
        // '��ɾ�'�� ũ�� ���� location counter ũ�� �����ǰų�
        // ��ɾ �ƴϰ�, location counter�� �����ϴ� ����� ���þ �ƴ� ���
        // -> �� ��쿡�� �ƹ��͵� �������� ����
        else
        {
            // �ش��ϴ� inst_table�� �ε��� ���Ϲ���
            index = search_opcode(token_table[i]->operator);
            
            if(index < 0)
            {
                fprintf(stdout, "search_opcode() error\n");
                return -1;
            }
            // operator�� �ش��ϴ� ���� ��ɾ��� ��
            else if(index < inst_index)
            {
                // 1������ ��
                if(inst_table[index]->format == 1)
                {
                    locctr += 1;
                }
                // 2������ ��
                else if(inst_table[index]->format == 2)
                {
                    locctr += 2;
                }
                // 3,4������ ��
                else
                {
                    // 4������ ��
                    if(token_table[i]->operator[0] == '+')
                    {
                        locctr += 4;
                    }
                    // 3������ ��
                    else
                    {
                        locctr += 3;
                    }
                }
            }
            
            // ��ɾ �ƴϰ�, location counter�� �����ϴ� ����� ���þ �ƴ� ���
            // -> location counter�� �������� �ʴ� ����� ���þ��� ���
            // ex. EQU, EXTDEF, EXTREF, ...
        }
        
        printf("locctr: %d\n", locctr);
    }
    
    return 0;
}

/* ----------------------------------------------------------------------------------
* ���� : �Էµ� ���ڿ��� �̸��� ���� ���Ͽ� ���α׷��� ����� �����ϴ� �Լ��̴�.
*        ���⼭ ��µǴ� ������ ��ɾ� ���� OPCODE�� ��ϵ� ǥ(���� 3��) �̴�.
* �Ű� : ������ ������Ʈ ���ϸ�
* ��ȯ : ����
* ���� : ���� ���ڷ� NULL���� ���´ٸ� ���α׷��� ����� ǥ��������� ������
*        ȭ�鿡 ������ش�.
*        ���� ���� 3�������� ���̴� �Լ��̹Ƿ� ������ ������Ʈ������ ������ �ʴ´�.
* -----------------------------------------------------------------------------------
*/
//void make_opcode_output(char *file_name)
//{
//    FILE *file = NULL;
//        char buf[25];
//        char empty = '\0';
//
//        // ���� �̸��� NULL�̸� ȭ�鿡 ���
//        if(file_name == NULL)
//        {
//            file = stdout; // ȭ�鿡 ���
//        }
//        else
//        {
//            if((file = fopen(file_name, "w")) < 0)
//            {
//                fprintf(stderr, "open error for %s\n", file_name);
//            }
//        }
//
//        for(int i = 0; i < token_line; ++i)
//        {
//            buf[0] = '\0';
//
//            // label
//            if(token_table[i]->label != NULL)
//            {
//                fprintf(file, "%-7s", token_table[i]->label); // label ���
//
//                // �ּ��� �� -> comment�� ����ϰ� �Ѿ
//                if(!strcmp(token_table[i]->label, "."))
//                {
//                    fprintf(file, "%-25s\n", token_table[i]->comment);
//                    continue;
//                }
//            }
//            // NULL�� ��� ���� �и����� ������ (null)�� ��µ�
//            else
//            {
//                fprintf(file, "%-8c", empty);
//            }
//
//            // operator
//            if(token_table[i]->operator != NULL)
//            {
//                fprintf(file, "%-7s", token_table[i]->operator); // operator ���
//            }
//            else
//            {
//                fprintf(file, "%-8c", empty);
//            }
//
//            // operand
//            for(int j = 0; j < MAX_OPERAND; ++j)
//            {
//                if(token_table[i]->operand[j] == NULL)
//                {
//                    break;
//                }
//
//                strcat(buf, token_table[i]->operand[j]);
//            }
//            fprintf(file, "%-25s", buf); // operand ���
//
//            // opcode
//            if(opcode[i] >= 0)
//            {
//                fprintf(file, "%02X", opcode[i]);
//            }
//
//            fprintf(file, "\n");
//        }
//
//        // ������ �����Ͽ� ���Ͽ� ����� ���� ��, ���� �ݱ�
//        if(file_name != NULL)
//        {
//            fclose(file);
//        }
//
//        return;
//}

/* ----------------------------------------------------------------------------------
* ���� : �Էµ� ���ڿ��� �̸��� ���� ���Ͽ� ���α׷��� ����� �����ϴ� �Լ��̴�.
*        ���⼭ ��µǴ� ������ SYMBOL�� �ּҰ��� ����� TABLE�̴�.
* �Ű� : ������ ������Ʈ ���ϸ�
* ��ȯ : ����
* ���� : ���� ���ڷ� NULL���� ���´ٸ� ���α׷��� ����� ǥ��������� ������
*        ȭ�鿡 ������ش�.
*
* -----------------------------------------------------------------------------------
*/
void make_symtab_output(char *file_name)
{

        
    return;
}

/* ----------------------------------------------------------------------------------
* ���� : �Էµ� ���ڿ��� �̸��� ���� ���Ͽ� ���α׷��� ����� �����ϴ� �Լ��̴�.
*        ���⼭ ��µǴ� ������ LITERAL�� �ּҰ��� ����� TABLE�̴�.
* �Ű� : ������ ������Ʈ ���ϸ�
* ��ȯ : ����
* ���� : ���� ���ڷ� NULL���� ���´ٸ� ���α׷��� ����� ǥ��������� ������
*        ȭ�鿡 ������ش�.
*
* -----------------------------------------------------------------------------------
*/
void make_literaltab_output(char* filen_ame)
{
    /* add your code here */
}

/* ----------------------------------------------------------------------------------
* ���� : ����� �ڵ带 ���� �ڵ�� �ٲٱ� ���� �н�2 ������ �����ϴ� �Լ��̴�.
*           �н� 2������ ���α׷��� ����� �ٲٴ� �۾��� ���� ������ ����ȴ�.
*           ������ ���� �۾��� ����Ǿ� ����.
*           1. ������ �ش� ����� ��ɾ ����� �ٲٴ� �۾��� �����Ѵ�.
* �Ű� : ����
* ��ȯ : �������� = 0, �����߻� = < 0
* ���� :
* -----------------------------------------------------------------------------------
*/
static int assem_pass2(void)
{

    /* add your code here */
    
    return 0;
}

/* ----------------------------------------------------------------------------------
* ���� : �Էµ� ���ڿ��� �̸��� ���� ���Ͽ� ���α׷��� ����� �����ϴ� �Լ��̴�.
*        ���⼭ ��µǴ� ������ object code (������Ʈ 1��) �̴�.
* �Ű� : ������ ������Ʈ ���ϸ�
* ��ȯ : ����
* ���� : ���� ���ڷ� NULL���� ���´ٸ� ���α׷��� ����� ǥ��������� ������
*        ȭ�鿡 ������ش�.
*
* -----------------------------------------------------------------------------------
*/
void make_objectcode_output(char *file_name)
{
    /* add your code here */
}

