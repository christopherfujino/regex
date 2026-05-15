chris.exe: grep-chris.c
	gcc -std=c99 $< -o $@

a.out: grep.c
	gcc -std=c89 -Wno-return-type -Wno-implicit-int -fno-strict-aliasing $< -o $@
