vm: main.c
	gcc $< -o $@
.PHONY: run clean

run:
	./vm
 
clean:
	rm vm
	rm correct2.txt