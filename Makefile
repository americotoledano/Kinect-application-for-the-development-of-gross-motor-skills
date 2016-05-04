all: launcher game keyboard

launcher:
	make -f launcherMakefile

game:
	make -f gameMakefile

keyboard:
	make -f keyboardMakefile

clean:
	make -f launcherMakefile clean
	make -f gameMakefile clean
	make -f keyboardMakefile clean
