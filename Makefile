PROGRAM=show_pci

$(PROGRAM): $(PROGRAM).o
	gcc $(PROGRAM).o -lpci -o $(PROGRAM)

$(PROGRAM).o: $(PROGRAM).c
	gcc -c -o $(PROGRAM).o $(PROGRAM).c

.PHONY: clean

clean:
	rm -f $(PROGRAM) $(PROGRAM).o
