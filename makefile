# ターゲットファイル名
target	= petit

# オブジェクトファイル名
objects	= program.o node.o

# 作業ディレクトリ
gen_dir	= ./temp

# コンパイラ
cc		= cc -std=c99



# 自動生成変数
_lexyyc		= $(gen_dir)/lex.yy.c
_ytabc		= $(gen_dir)/y.tab.c
objects		+= y.tab.o
_objects	= $(objects:%.o=$(gen_dir)/%.o)



$(target): $(_objects)
	$(cc) -o $(target) $(_objects)

$(gen_dir)/%.o: %.c %.h
	@mkdir -p $(gen_dir)
	$(cc) -o $@ -c $<

$(gen_dir)/y.tab.o: $(_ytabc) $(_lexyyc)
	@mkdir -p $(gen_dir)
	$(cc) -Wno-implicit-function-declaration -o $@ -c $<

$(_lexyyc): $(target).l
	@mkdir -p $(gen_dir)
	flex -o $@ $<

$(_ytabc): $(target).y
	@mkdir -p $(gen_dir)
	bison -o $@ -d $<

rebuild: clean $(target)

clean:
	rm -fr $(gen_dir) $(target)

.PHONY: clean rebuild

