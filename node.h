#ifndef __NODE_H__
#define __NODE_H__


//
// �m�[�h�̎�ނ�\��
//
typedef enum {
	ZERO_TYPE,		// 0
	VAR_TYPE,		// ��
	SUC_TYPE,		// suc ��
	ASSIGN_TYPE,	// ��:=��
	FOR_DO_TYPE,	// for �� times do �� end
	SEMICOLON_TYPE,	// ��;��
} NODE_TYPE;



// �O���錾�Ȃ�
typedef struct _struct_node_ NODE;
typedef unsigned char BYTE;



// 0
NODE *create_zero_node();

// ��
typedef struct {
	BYTE index; // ��
} VAR_ARGS;
NODE *create_var_node(char);

// suc ��
typedef struct {
	NODE *expr; // ��
} SUC_ARGS;
NODE *create_suc_node(NODE*);

// ��:=��
typedef struct {
	NODE *var;	// ��
	NODE *expr;	// ��
} ASSIGN_ARGS;
NODE *create_assign_node(NODE*, NODE*);

// for �� times do �� end
typedef struct {
	NODE *count;	// ��
	NODE *stmt;		// ��
} FOR_DO_ARGS;
NODE *create_for_do_node(NODE*, NODE*);

// ��1;��2
typedef struct {
	NODE *former_stmt; // ��1
	NODE *latter_stmt; // ��2
} SEMICOLON_ARGS;
NODE *create_semicolon_node(NODE*, NODE*);



//
// �m�[�h��\��
//
struct _struct_node_ {
	NODE_TYPE type;
	union {
		VAR_ARGS		var;
		SUC_ARGS		suc;
		ASSIGN_ARGS		assign;
		FOR_DO_ARGS		for_do;
		SEMICOLON_ARGS	semicolon;
	} args;
} /* NODE */;

#endif
