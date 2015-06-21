# Very rudimentary Makefile for the llvm tutorial
# See http://llvm.org/docs/tutorial/
# See also http://koichitamura.blogspot.de/2011/01/since-i-went-to-held-several-weeks-ago.html
# for a necessary "fix" (!)
#
# This Makefile written by Prof. R. C. Moore, fbi.h-da.de


###############################################################################
#Sollte es hiermit Probleme geben bescheid sagen und ich such ne andere Lösung#
###############################################################################

#Hier einfach nur den Namen einfügen wenn ihr was neues geaddet habt ist wichtig für den Clean Build

PROGS=main Token Parser TreeNode
CC=clang++-3.5
# (Rather) Maximialist
CFLAGS=-O3 `llvm-config-3.5 --cxxflags --ldflags --libs all` -rdynamic

#Hier jede neue erstellte Datei dazuschreiben, ja man kann es auch Dynamisch
#machen und ja beim Moore ists auch so das man nur oben 
#bei Progs was dazu schreiben muss aber nicht hier. Ich versuch das 
#noch irgendwie reinzukriegen aber das macht mir im moment
#mehr Ärger als nutzen


iHateMakeFiles: main.cpp Token.cpp Token.h Parser.cpp Parser.h TreeNode.h
	$(CC) -g $< $(CFLAGS) -o $@


clean:
	$(RM) *~ $(PROGS) ModuleMaker.bc

#Quellen: http://www.ijon.de/comp/tutorials/makefile.html#targets
#	: http://mrbook.org/blog/tutorials/make/
