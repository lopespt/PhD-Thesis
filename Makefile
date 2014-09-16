build:
	qmake -project -o PhdThesis.pro QT+=core QT+=widgets
	qmake -o QMakefile
	make -f QMakefile
