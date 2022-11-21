#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

extern char* yytext;
A_TYPE *int_type, *char_type, *void_type, *float_type, *string_type;
A_NODE *root;
A_ID *current_id = NIL;

int syntax_err = 0;
int line_no = 1;
int current_level = 0;

A_NODE*		makeNode (NODE_NAME, A_NODE *, A_NODE *, A_NODE *);
A_NODE*		makeNodeList (NODE_NAME, A_NODE *, A_NODE *);
A_ID*		makeIdentifier(char *);
A_ID*		makeDummyIdentifier();
A_TYPE*		makeType(T_KIND);
A_SPECIFIER*	makeSpecifier(A_TYPE *, S_KIND);
A_ID*		searchIdentifier(char *, A_ID *);
A_ID*		searchIdentifierAtCurrentLevel(char *, A_ID *);
A_SPECIFIER*	updateSpecifier(A_SPECIFIER *, A_TYPE *, S_KIND);
void			checkForwardReference();
void			setDefaultSpecifier(A_SPECIFIER *);
A_ID*		linkDeclaratorList(A_ID *, A_ID *);
A_ID*		getIdentifierDeclared(char *);
A_TYPE*		getTypeOfStructOrEnumRefIdentifier(T_KIND, char *, ID_KIND);
A_ID*		setDeclaratorInit(A_ID *, A_NODE *);
A_ID*		setDeclaratorKind(A_ID *, ID_KIND);
A_ID*		setDeclaratorType(A_ID *, A_TYPE *);
A_ID*		setDeclaratorElementType(A_ID *, A_TYPE *);
A_ID*		setDeclaratorTypeAndKind(A_ID *, A_TYPE *, ID_KIND);
A_ID*		setDeclaratorListSpecifier(A_ID *, A_SPECIFIER *);
A_ID*		setFunctionDeclaratorSpecifier(A_ID *, A_SPECIFIER *);
A_ID*		setFunctionDeclaratorBody(A_ID *, A_NODE *);
A_ID*		setParameterDeclaratorSpecifier(A_ID *, A_SPECIFIER *);
A_ID*		setStructDeclaratorListSpecifier(A_ID *, A_TYPE *);
A_TYPE*		setTypeNameSpecifier(A_TYPE *, A_SPECIFIER *);
A_TYPE*		setTypeElementType(A_TYPE *, A_TYPE *);
A_TYPE*		setTypeField(A_TYPE *, A_ID *);
A_TYPE*		setTypeExpr(A_TYPE *, A_NODE *);
A_TYPE*		setTypeAndKindOfDeclarator(A_TYPE *, ID_KIND, A_ID *);
A_TYPE*		setTypeStructOrEnumIdentifier(T_KIND, char *, ID_KIND);
BOOLEAN		isNotSameFormalParameters(A_ID *, A_ID *);
BOOLEAN		isNotSameType(A_TYPE *, A_TYPE *);
BOOLEAN		isPointerOrArrayType(A_TYPE *);

void syntax_error();
void initialize();

// 신택스 트리를 위한 새로운 노드를 하나 만들어,
// 파라미터로 받은 값들을 각각 name, link, clink, rlink 필드에 지정하고
// 그 노드의 주소값 리턴
A_NODE* makeNode (NODE_NAME n, A_NODE *a, A_NODE *b, A_NODE *c) {
	A_NODE *m;
	m = (A_NODE*) malloc(sizeof(A_NODE)); // 노드 생성
	m -> name = n;
	m -> llink = a;
	m -> clink = b;
	m -> rlink = c;
	m -> type = NIL;
	m -> line = line_no; // 현재 분석중인 원시 프로그램의 줄번호 저장
	m -> value = 0;
	return(m);
}

// 신택스 트리의 단말 노드에 다른 단말 노드를 연결하여
// 하나의 목록처럼 만듦
A_NODE* makeNodeList (NODE_NAME n, A_NODE *a, A_NODE *b) { 
	A_NODE *m, *k;
	k = a;
	while (k -> rlink)
		k = k-> rlink;
	m = (A_NODE*) malloc(sizeof(A_NODE));
	m -> name = k -> name;
	m -> llink = NIL;
	m -> clink = NIL;
	m -> rlink = NIL;
	m -> type = NIL;
	m -> line = line_no; // 현재 분석중인 원시 프로그램의 줄번호 저장
	m -> value = 0;
	k -> name = n;
	k -> llink = b;
	k -> rlink = m;
	return (a);
}

// 명칭 s를 위한 새로운 심볼테이블 하나 생성하여 그 주소 리턴
// 해당 명칭이 앞으로 사용될 수 있도록 사용 가능한 심볼 테이블 목록으로 등록해야함
A_ID *makeIdentifier (char *s) { 
	A_ID *id;
	id = malloc(sizeof(A_ID));
	id -> name = s;
	id -> kind = 0;
	id -> specifier = 0;
	id -> level = current_level; // 명칭이 나타난 레벨 값 저장
	id -> address = 0;
	id -> init = NIL;
	id -> type = NIL;
	id -> link = NIL;
	id -> line = line_no; // 명칭이 나타난 줄 번호 저장
	id -> value = 0;
	id -> prev = current_id;
	current_id = id;
	return (id);
}

// 명칭을 갖지 않는 새로운 심볼 테이블을 하나 생성하여 그 주소 리턴
// 선언문에서 심볼의 명칭이 없이 타입만 선언되는 경우에 호출됨
A_ID *makeDummyIdentifier () { 
	A_ID *id;
	id = malloc(sizeof(A_ID));
	id -> name = "";
	id -> kind = 0;
	id -> specifier = 0;
	id -> level = current_level; // 현재 분석 중인 원시프로그램의 레벨 값 저장
	id -> address = 0;
	id -> init = NIL;
	id -> type = NIL;
	id -> link = NIL;
	id -> line = line_no; // 현재 분석 중인 원시프로그램의 줄번호 저장
	id -> value = 0;
	id -> prev = 0;
	return (id);
}

// 새로운 타입 테이블을 만들어 그 종류를 k로 설정
// 그 타입 테이블의 주소 리턴 
A_TYPE *makeType (T_KIND k) { 
	A_TYPE *t;
	t = malloc(sizeof(A_TYPE));
	t -> kind = k;
	t -> size = 0;
	t -> local_var_size = 0;
	t -> element_type = NIL;
	t -> field = NIL;
	t -> expr = NIL;
	t -> prt = FALSE;
	t -> line = line_no; // 현재 분석 중인 원시프로그램 줄번호도 저장
	return (t);
}

// specifier 테이블을 하나 생성하여 그 주소를 리턴
A_SPECIFIER *makeSpecifier(A_TYPE *t, S_KIND s) {
	A_SPECIFIER *p;
	p = malloc(sizeof(A_SPECIFIER));
	p -> type = t;
	p -> stor = s;
	p -> line = line_no;
	return (p);
}

// 명칭 s가 현재 분석하고 있는 위치에서 사용될 수 있는 명칭인지 검색
A_ID *searchIdentifier(char *s, A_ID *id) {
	while (id) {
		if (strcmp(id->name, s) == 0)
			break;
		id = id -> prev;
	}
	return (id);
}

// 명칭 id가 중복되어 선언되어 있는지 검사
A_ID *searchIdentifierAtCurrentLevel(char *s, A_ID *id) {
	while (id) {
		if (id -> level < current_level)
			return(NIL);
		if (strcmp(id->name, s) == 0)
			break;
		id = id -> prev;
	}
	return (id);
}

// 구조체를 참조하는 경우
// 같은 스코프 범위 내에서 뒷 부분에 선언되어 있는지 검사
void checkForwardReference() {
	A_ID *id;
	A_TYPE *t;
	id = current_id;
	while (id) {
		if (id -> level < current_level)
			break;
		t = id -> type;
		if (id -> kind == ID_NULL)
			syntax_error(31, id -> name);
		else if ((id -> kind == ID_STRUCT || id -> kind == ID_ENUM) && t -> field == NIL)
			syntax_error(32, id -> name);
		id = id -> prev;
	}
}

// 명시자에서 타입 명시자나 기억장소명시자가 생략되어있을 때 기본 값 설정
void setDefaultSpecifier(A_SPECIFIER *p) { 
	A_TYPE *t;
	if (p -> type == NIL)
		p -> type = int_type;
	if (p -> stor == S_NULL)
		p -> stor = S_AUTO;
}

// 선언문에서 선언자 앞에 나오는 선언 명시자가 여러 개일 때 이를 병합하고 업데이트 함
// 함수는 앞서 나온 선언 명시자 p가 있을 때 나중에 오는 타입 명시자 t나 기억장소 명시자 s가 합쳐도 되는지 검사
// 합친 다음 그 주소 리턴
A_SPECIFIER *updateSpecifier(A_SPECIFIER *p, A_TYPE *t, S_KIND s) { 
	if (t)
		if (p->type)
			if (p->type == t)
				;
			else
				syntax_error(24, "");
		else
			p -> type = t;
	if (s) {
		if (p -> stor)
			if (s == p -> stor)
				;
			else
				syntax_error(24, "");
		else
			p -> stor = s;
	}
	return (p);
}

// 파라미터로 받은 두 개의 심볼 테이블 목록인 id1과 id2 연결
// 심볼 테이블의 link 필드에 계속 연결되도록 함
// 맨 앞의 주소 값 리턴
A_ID *linkDeclaratorList(A_ID *id1, A_ID *id2) { 
	A_ID *m = id1;
	if (id1 == NIL)
		return (id2);
	while (m -> link)
		m = m -> link;
	m->link = id2;
	return (id1);
}

// 명칭 s가 미리 선언되어 있는지 검사
// 선언되어 있어 사용할 수 있는 경우 심볼 테이블 주소 리턴
A_ID *getIdentifierDeclared(char *s) { 
	A_ID *id;
	id = searchIdentifier(s, current_id);
	if (id == NIL)
		syntax_error(13, s);
	return (id);
}

// 명칭이 선언되어 사용될 수 있는지 심볼 테이블 목록에서 검색
// 명칭의 종류가 kk인지 검사하고 타입 테이블의 주소 리턴
A_TYPE *getTypeOfStructOrEnumRefIdentifier(T_KIND k, char *s, ID_KIND kk) { 
	A_TYPE *t;
	A_ID *id;
	id = searchIdentifier(s, current_id);
	if (id)
		if (id -> kind == kk && id -> type -> kind == k)
			return (id -> type);
		else
			syntax_error(11, s);
	// 명칭이 앞서 선언되어 있지 않은 경우 -> 뒷 부분에서 새로운 명칭과 타입으로 사용할 수 있도록 등록
	t = makeType(k);
	id = makeIdentifier(s);
	id -> kind = kk;
	id -> type = t;
	return (t);
}

// 심볼 테이블 id의 init 필드에 주어진 신택스 트리 n을 연결
// 명칭에 초기화된 수식 가리킴
A_ID *setDeclaratorInit (A_ID *id, A_NODE *n) { 
	id -> init = n;
	return (id);
}

// 주어진 명칭이 원시 프로그램 내 같은 레벨에서 중복 선언 여부 검사
// 명칭 id의 종류를 k로 설정하고 그 주소를 리턴
A_ID *setDeclaratorKind (A_ID *id, ID_KIND k) { 
	A_ID *a;
	a = searchIdentifierAtCurrentLevel(id -> name, id -> prev);
	if (a)
		syntax_error(12, id -> name);
	id -> kind = k;
	return (id);
}

// 심볼테이블 id의 타입 정보를 주어진 매개변수 t로 설정
A_ID *setDeclaratorType (A_ID *id, A_TYPE *t) { 
	id -> type = t;
	return (id);
}

// 심볼 테이블 id에 타입 테이블 주소인 t 연결
A_ID *setDeclaratorElementType (A_ID *id, A_TYPE *t) { 
	A_TYPE *tt;
    // 명칭에 타입 정보가 없는 경우 -> 바로 연결
	if (id -> type == NIL)
		id -> type = t;
    // 복합 구조 타입인 경우 -> 마지막 엘리먼트 타입으로 연결
	else {
		tt = id -> type;
		while (tt -> element_type)
			tt = tt -> element_type;
		tt -> element_type = t;
	}
	return (id);
}

// initialize() 함수에서만 사용
// 심볼 테이블의 타입과 종류 설정
A_ID *setDeclaratorTypeAndKind (A_ID *id, A_TYPE *t, ID_KIND k) { 
	id = setDeclaratorElementType(id, t);
	id = setDeclaratorKind(id, k);
	return (id);
}

// 심볼 테이블 id의 명칭이 함수 타입으로 잘 선언되어있는지 검사
// 해당 타입 테이블에서 함수의 리턴 타입을 선언지시자 p의 타입 정보로 설정
A_ID *setFunctionDeclaratorSpecifier (A_ID *id, A_SPECIFIER *p) { 
	A_ID *a;
	// check storage class
	if (p -> stor)
		syntax_error(25, "");

	setDefaultSpecifier(p);
	// '(' 직전에 함수 식별자 확인
	if (id -> type == 0 || id -> type -> kind != T_FUNC) {
		syntax_error(21, "");
		return (id);
	} else {
		id = setDeclaratorElementType(id, p -> type);
		id -> kind = ID_FUNC;
	}
	// 중복 선언 검사
	a = searchIdentifierAtCurrentLevel(id -> name, id -> prev);
	if (a)
		if (a -> kind != ID_FUNC || a -> type -> expr)
			syntax_error(12, id->name);
        // 프로토타입과 비교 검샤
		else { 
			if (isNotSameFormalParameters(a -> type -> field, id -> type -> field))
				syntax_error(22, id -> name);
			if (isNotSameType(a -> type -> element_type, id -> type -> element_type))
				syntax_error(26, a -> name);
		}
	// 함수의 파라미터 명칭 목록을 함수 몸체의 복합문 안에서 사용할 수 있도록 파라미터의 스코프 변경
	a = id -> type -> field;
	while (a) {
		if (strlen(a -> name))
			current_id = a;
		else if (a -> type)
			syntax_error(23, "");
		a = a -> link;
	}
	return (id);
}

// 심볼테이블 id의 타입이 함수 명칭이고
// 그에 연결된 타입 테이블에서 expr 필드에 함수의 몸체를 나타내는 node n 연결
// node n은 신택스 트리의 루트노드 
A_ID *setFunctionDeclaratorBody (A_ID *id, A_NODE *n) {
	id -> type -> expr = n;
	return (id);
}

// 선언문에서 선언자 앞에 선언 명시자가 여러 개 나올 때
// 먼저 나온 선언 명시자와 다음 나오는 선언 명시자가 의미적으로 올바르게 사용되는지 여부
// 함수는 앞서 나온 선언 명시자 p가 있을 때
// 나중에 나오는 타입 명시자 t나 기억장소 명시자 s가 합쳐도 되는지 검사하고 합침
// 합친 그 주소
A_ID *setDeclaratorListSpecifier (A_ID *id, A_SPECIFIER *p) { 
	A_ID *a;
	setDefaultSpecifier(p);
	a = id;
	while (a) {
		if (strlen(a->name) && searchIdentifierAtCurrentLevel(a -> name, a -> prev))
			syntax_error(12, a -> name);
		a = setDeclaratorElementType(a, p -> type);
		if (p->stor == S_TYPEDEF)
			a -> kind = ID_TYPE;
		else if (a->type->kind == T_FUNC)
			a -> kind = ID_FUNC;
		else
			a -> kind = ID_VAR;
		a -> specifier = p -> stor;
		if (a -> specifier == S_NULL)
			a -> specifier = S_AUTO;
		a = a -> link;
	}
	return (id);
}

// 심볼테이블 id의 타입 정보를 p로, 명칭의 종류를 ID_RARM로 설정
A_ID *setParameterDeclaratorSpecifier (A_ID *id, A_SPECIFIER *p) { 
	// 동일한 명칭이 같은 파라미터 목록에 중복 선언되어 있는지 검사
	if (searchIdentifierAtCurrentLevel(id -> name, id -> prev))
		syntax_error(12, id -> name);
	// 기억장소 명시자가 포함되어 있거나 void 타입인지 검사
	if (p -> stor || p -> type == void_type)
		syntax_error(14, "");
	setDefaultSpecifier(p);
	id = setDeclaratorElementType(id, p -> type);
	id -> kind = ID_PARM;
	return (id);
}

// 심볼테이블 목록 id에 연결된 모든 명칭에 대해 중복 선언 검사
// 심볼의 종류는 ID_FIELD
// 그 타입을 주어진 타입테이블의 주소인 t로 설정
A_ID *setStructDeclaratorListSpecifier(A_ID *id, A_TYPE *t) {
	A_ID *a;
	a = id;
	while (a) {
		if (searchIdentifierAtCurrentLevel(a -> name, a -> prev))
			syntax_error(12, a -> name);
		a = setDeclaratorElementType(a, t);
		a -> kind = ID_FIELD;
		a = a -> link;
	}
	return (id);
}

// 타입 명시자 p가 기억 장소 명시자를 포함하고 있는지 검사 및 생략된 타입 명시자 확인하여 설정
// 타입 t의 엘리먼트 타입으로 타입 명시자 p의 타입 정보 지정
A_TYPE *setTypeNameSpecifier (A_TYPE *t, A_SPECIFIER *p) { 
	// check storage class in type name
	if (p -> stor)
		syntax_error(20, "");
	setDefaultSpecifier(p);
	t = setTypeElementType(t, p -> type);
	return (t);
}

// 타입 테이블 t의 엘리먼트 타입으로 s 연결
A_TYPE *setTypeElementType (A_TYPE *t, A_TYPE *s) {
	A_TYPE *q;
    // 명칭에 타입 정보가 없는 경우 -> 바로 연결
	if (t == NIL)
		return (s);
	q = t;
    // 복합구조의 타입인 경우 -> 마지막 엘리먼트의 타입으로 연결
	while (q -> element_type)
		q = q -> element_type;
	q -> element_type = s;
	return (t);
}

// 타입테이블 t의 필드 목록을 주어진 심볼테이블 목록 n으로 설정
A_TYPE *setTypeField (A_TYPE *t, A_ID *n) { 
	t -> field = n;
	return (t);
}

// 타입 테이블 t의 expr 필드에 신택스 트리 n 연결
A_TYPE *setTypeExpr (A_TYPE *t, A_NODE *n) { 
	t -> expr = n;
	return (t);
}

// 구조체 혹은 나열형 타입의 명칭 s를 새로 선언
// 중복 선언 검사 및 명칭을 위한 심볼 테이블 하나 생성
// 명칭의 종류는 kk이고 k 종류의 새로운 타입테이블을 하나 생성하여 그 주소를 심볼 테이블에 저장
// 타입 테이블 주소 리턴
A_TYPE *setTypeStructOrEnumIdentifier (T_KIND k, char *s, ID_KIND kk) {
	A_TYPE *t;
	A_ID *id, *a;
	// check redeclaration or forward declaration
	a = searchIdentifierAtCurrentLevel(s, current_id);
	if (a)
		if (a -> kind == kk && a -> type -> kind == k)
			if (a -> type -> field)
				syntax_error(12, s);
			else
				return (a -> type);
		else
			syntax_error(12, s);
	// make a new struct (or enum) identifier
	id = makeIdentifier(s);
	t = makeType(k);
	id -> type = t;
	id -> kind = kk;
	return (t);
}

// initialize() 함수에서만 사용
// 심볼 테이블의 타입과 종류 설정
A_TYPE *setTypeAndKindOfDeclarator (A_TYPE *t, ID_KIND k, A_ID *id) { 
	if (searchIdentifierAtCurrentLevel(id -> name, id -> prev))
		syntax_error(12, id -> name);
	id -> type = t;
	id -> kind = k;
	return (t);
}

// 프로토타입이나 함수의 파라미터 목록 a와 지금 새롭게 선언하는 함수 파라미터의 목록 b의 타입과 개수가 일치하는지 검사
BOOLEAN isNotSameFormalParameters (A_ID *a, A_ID *b) { 
	if (a == NIL) // 프로토타입에 파라미터가 없는 경우
		return (FALSE);
	while (a) {
		if (b == NIL || isNotSameType(a -> type, b -> type))
			return (TRUE);
		a = a -> link;
		b = b -> link;
	}
	if (b)
		return (TRUE);
	else
		return (FALSE);
}

// 타입 t1과 t2가 같은 주소의 타입 테이블을 가리키는지 검사
BOOLEAN isNotSameType (A_TYPE *t1, A_TYPE *t2) {
	if (isPointerOrArrayType(t1) || isPointerOrArrayType(t2))
		return (isNotSameType(t1 -> element_type, t2 -> element_type));
	else
		return (t1 != t2);
}

// 타입 t가 배열 혹은 포인터인지 검사
BOOLEAN isPointerOrArrayType(A_TYPE *t) {
	if (t && ( t->kind == T_POINTER || t->kind == T_ARRAY))
		return(TRUE);
	else
		return(FALSE);
}

// 신택스 분석을 시작하기 전에 수행
void initialize() {
	
	// 타입을 검사하는데 사용되는 전역변수를 정의
	int_type = setTypeAndKindOfDeclarator(makeType(T_ENUM),ID_TYPE,makeIdentifier("int"));
	float_type = setTypeAndKindOfDeclarator(makeType(T_ENUM),ID_TYPE,makeIdentifier("float"));
	char_type = setTypeAndKindOfDeclarator(makeType(T_ENUM),ID_TYPE,makeIdentifier("char"));
	void_type = setTypeAndKindOfDeclarator(makeType(T_VOID),ID_TYPE,makeIdentifier("void"));
	string_type = setTypeElementType(makeType(T_POINTER),char_type);

    // 타입 관련 예약어를 심볼 테이블 목록에 미리 저장
    // 관련 타입 정보를 설정하여 연결
	int_type->size=4;
	int_type->check=TRUE;
	
	float_type->size=4; 
	float_type->check=TRUE;
	
	char_type->size=1; 
	char_type->check=TRUE;
	
	void_type->size=0; 
	void_type->check=TRUE;

	string_type->size=4; 
	string_type->check=TRUE;

	// print() 라이브러리 함수 정의
	setDeclaratorTypeAndKind(makeIdentifier("printf"),setTypeField(setTypeElementType(makeType(T_FUNC),void_type),
		linkDeclaratorList(setDeclaratorTypeAndKind(makeDummyIdentifier(),string_type,ID_PARM),
		setDeclaratorKind(makeDummyIdentifier(),ID_PARM))),ID_FUNC);

	// scanf() 라이브러리 함수 정의
	setDeclaratorTypeAndKind(makeIdentifier("scanf"),setTypeField(setTypeElementType(makeType(T_FUNC),void_type),
		linkDeclaratorList(setDeclaratorTypeAndKind(makeDummyIdentifier(),string_type,ID_PARM),
		setDeclaratorKind(makeDummyIdentifier(),ID_PARM))),ID_FUNC);

	// malloc() 라이브러리 함수 정의
	setDeclaratorTypeAndKind(makeIdentifier("malloc"),setTypeField(setTypeElementType(makeType(T_FUNC),string_type),
		setDeclaratorTypeAndKind(makeDummyIdentifier(),int_type,ID_PARM)),ID_FUNC);
}

// 신택스 분석 중 발생하는 오류 메세지를 종류별로 출력
void syntax_error(int i,char *s) {

	syntax_err++;
	printf("line %d: syntax error: ", line_no);

	switch (i) { 
		case 11: 
			printf("illegal referencing struct or union identifier %s",s);
			break; 

		case 12: 
			printf("redeclaration of identifier %s",s); 
			break; 

		case 13: 
			printf("undefined identifier %s",s); 
			break; 

		case 14: 
			printf("illegal type specifier in formal parameter"); 
			break;
	    
		case 20: 
			printf("illegal storage class in type specifiers"); 
			break; 

		case 21: 
			printf("illegal function declarator"); 
			break; 

		case 22: 
			printf("conflicting parm type in prototype function %s",s);
			break; 

		case 23: 
			printf("empty parameter name"); 
			break; 

		case 24: 
			printf("illegal declaration specifiers"); 
			break; 

		case 25: 
			printf("illegal function specifiers"); 
			break; 

		case 26: 
			printf("illegal or conflicting return type in function %s",s);
			break;

		 case 31: 
			printf("undefined type for identifier %s",s); 
			break; 

		case 32: 
			printf("incomplete forward reference for identifier %s",s);
			break; 

		default: 
			printf("unknown"); 
			break;
	}
	
	if (strlen(yytext)==0)
		printf(" at end\n");
	else
		printf(" near %s\n", yytext);
}