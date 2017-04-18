gen-file=serial-gen
time-file=serial-time

#---------GENERATIONS---------
gen: compile-gen run-gen
compile-gen:
	gcc-6 $(gen-file).c -o $(gen-file)
run-gen:
	./$(gen-file)


#---------GENERATIONS---------
time: compile-time run-time
compile-time:
	gcc-6 $(time-file).c -o $(time-file)
run-time:
	./$(time-file)
