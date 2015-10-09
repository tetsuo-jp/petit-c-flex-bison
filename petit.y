%{
#include <stdio.h>
#include "../node.h"
#include "../program.h"
//#define YYERROR_VERBOSE

static int line = 1;			// 現在の行数
static NODE *root;				// 抽象構文木の根
static BOOL is_interactive;		// インタラクティブモードかどうか
%}

%union {
	NODE *node;
}

%token ASSIGN SUC FOR TIMES_DO END NL
%token <node> VAR
%token <node> ZERO
%left SEMICOLON
%type <node> prog
%type <node> expr

%%

input
	: prog { root = $1; }
	| prog NL { root = $1; if (is_interactive) YYACCEPT; }
	;

prog
	: VAR ASSIGN expr				{ $$ = create_assign_node($1, $3); }
	| FOR expr TIMES_DO prog END	{ $$ = create_for_do_node($2, $4); }
	| prog SEMICOLON prog			{ $$ = create_semicolon_node($1, $3); }
	;

expr
	: ZERO		{ $$ = $1; }
	| VAR		{ $$ = $1; }
	| SUC expr	{ $$ = create_suc_node($2); }
	;

%%

#include "lex.yy.c"

// エラー報告関数
int yyerror(const char *err) {
	fprintf(stderr, is_interactive ? "ERROR: %s.\n" : "ERROR: %s at line %d.\n", err, line);
	return 0;
}

// エントリポイント
int main(int argc, char *argv[]) {
	// 初期化
	initialize();
	
	// インタラクティブモード判定
	is_interactive = argc == 1;
	
	// ファイル実行モード
	if (argc == 2) {
		yyin = fopen(argv[1], "r");
		// ファイルが存在しない場合はエラー終了
		if (yyin == NULL) {
			fprintf(stderr, "Can't open file \"%s\".", argv[1]);
			return -1;
		}
	}
	// コマンドライン引数が多すぎる場合はエラー終了
	else if (2 < argc) {
		fputs("Too many arguments.\n", stderr);
		return -1;
	}
	
	// インタラクティブモードならリアルタイム実行
	do {
		if (yyparse() && !is_interactive) return -1;
		if (root != NULL) execute(root);
		root = NULL;
	} while (is_interactive);
	
	return 0;
}
