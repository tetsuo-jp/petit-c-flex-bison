#include <stdlib.h>
#include "node.h"


// �m�[�h�̐���
static NODE *create_node(NODE_TYPE type) {
	NODE *node = (NODE*)malloc(sizeof(NODE));
	node->type = type;
	return node;
}


// 0 �m�[�h�̐���
NODE *create_zero_node() {
	return create_node(ZERO_TYPE);
}

// �� �m�[�h�̐���
NODE *create_var_node(char letter) {
	NODE *node = create_node(VAR_TYPE);
	node->args.var.index = letter-'A';
	return node;
}

// suc �� �m�[�h�̐���
NODE *create_suc_node(NODE* expr) {
	NODE *node = create_node(SUC_TYPE);
	node->args.suc.expr = expr;
	return node;
}

// ��:=�� �m�[�h�̐���
NODE *create_assign_node(NODE *var, NODE *expr) {
	NODE *node = create_node(ASSIGN_TYPE);
	node->args.assign.var = var;
	node->args.assign.expr = expr;
	return node;
}

// for �� times do �� end �m�[�h�̐���
NODE *create_for_do_node(NODE *count, NODE *stmt) {
	NODE *node = create_node(FOR_DO_TYPE);
	node->args.for_do.count = count;
	node->args.for_do.stmt = stmt;
	return node;
}

// ��1;��2 �m�[�h�̐���
NODE *create_semicolon_node(NODE *former, NODE *latter) {
	NODE *node = create_node(SEMICOLON_TYPE);
	node->args.semicolon.former_stmt = former;
	node->args.semicolon.latter_stmt = latter;
	return node;
}
