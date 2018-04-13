OBJ = main.o sound.o screen.o comm.o
APPNAME = sound.a

#link rule
$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm -lcurl

#compling rule
%.o : %.c
	gcc -c -o $@ $<

clean :
	rm $(OBJ) $(APPNAME)

tar :
	tar cf project.tar *
