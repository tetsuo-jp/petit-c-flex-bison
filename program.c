#include <stdio.h>
#include "program.h"
#include "node.h"

#define LETTERS	('Z'-'A' + 1)


static int values[LETTERS];		// 変数の値
static BOOL is_init[LETTERS];	// 変数の初期化状態


// 初期化関数
void initialize(){
	// 変数の初期化済フラグを全て下げる
	for (int i = 0; i < LETTERS; i++) is_init[i] = FALSE;
}


// 評価関数
static int evaluate(NODE *expr, int *result) {
	switch (expr->type) {
		// 0
		case ZERO_TYPE: {
			// 0を返して正常終了
			*result = 0;
			return 0;
		}
		// ξ
		case VAR_TYPE: {
			// 未初期化変数の取得はエラー
			if (!is_init[expr->args.var.index]) {
				fprintf(stderr, "Undefined variable.\n");
				return -1;
			}
			*result = values[expr->args.var.index];
			return 0;
		}
		// suc ε
		case SUC_TYPE: {
			if (evaluate(expr->args.suc.expr, result)) return -1;
			(*result)++;
			return 0;
		}
		default: {
			// 不明な式表現はエラー
			fprintf(stderr, "Evaluation error.\n");
			return -1;
		}
	}
}


// 実行関数
int execute(NODE *stmt) {
	switch (stmt->type) {
		// ξ := ε
		case ASSIGN_TYPE: {
			// 代入値の取得を試みる
			int value;
			if (evaluate(stmt->args.assign.expr, &value)) return -1;
			
			// 値を代入して実行結果を表示
			int index = stmt->args.assign.var->args.var.index;
			values[index] = value;
			printf("Variable %c becomes %d.\n", 'A'+index, values[index]);
			
			// 初期化済みフラグを立てる
			is_init[index] = TRUE;
			return 0;
		}
		// for ε times do τ end
		case FOR_DO_TYPE: {
			// 実行回数の取得を試みる
			int length;
			if (evaluate(stmt->args.for_do.count, &length)) return -1;
			
			// 実行回数分ステートメントを実行
			for (int i = 0; i < length; i++) execute(stmt->args.for_do.stmt);
			return 0;
		}
		// τ;τ
		case SEMICOLON_TYPE: {
			// ステートメントを順番に実行
			execute(stmt->args.semicolon.former_stmt);
			execute(stmt->args.semicolon.latter_stmt);
			return 0;
		}
		default: {
			// 不明なステートメントはエラー
			fprintf(stderr, "Execution error.\n");
			return -1;
		}
	}
}

