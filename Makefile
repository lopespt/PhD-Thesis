build:
	rm -rf build
	qmake -project -o PhdThesis.pro QT+=core QT+=widgets
	cat Makefile_dirs >> PhdThesis.pro
	qmake -o QMakefile
	make -f QMakefile
run:
	./release/PhDThesis.app/Contents/MacOS/PhDThesis

doc:
	doxygen config.gen

.PHONY: build run
