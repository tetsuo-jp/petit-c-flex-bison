#ifndef __NODE_H__
#define __NODE_H__


//
// ノードの種類を表す
//
typedef enum {
	ZERO_TYPE,		// 0
	VAR_TYPE,		// ξ
	SUC_TYPE,		// suc ε
	ASSIGN_TYPE,	// ξ:=ε
	FOR_DO_TYPE,	// for ε times do τ end
	SEMICOLON_TYPE,	// τ;τ
} NODE_TYPE;



// 前方宣言など
typedef struct _struct_node_ NODE;
typedef unsigned char BYTE;



// 0
NODE *create_zero_node();

// ξ
typedef struct {
	BYTE index; // ξ
} VAR_ARGS;
NODE *create_var_node(char);

// suc ε
typedef struct {
	NODE *expr; // ε
} SUC_ARGS;
NODE *create_suc_node(NODE*);

// ξ:=ε
typedef struct {
	NODE *var;	// ξ
	NODE *expr;	// ε
} ASSIGN_ARGS;
NODE *create_assign_node(NODE*, NODE*);

// for ε times do τ end
typedef struct {
	NODE *count;	// ε
	NODE *stmt;		// τ
} FOR_DO_ARGS;
NODE *create_for_do_node(NODE*, NODE*);

// τ1;τ2
typedef struct {
	NODE *former_stmt; // τ1
	NODE *latter_stmt; // τ2
} SEMICOLON_ARGS;
NODE *create_semicolon_node(NODE*, NODE*);



//
// ノードを表す
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
