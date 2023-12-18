# crea el archivo .jar que agrupa los archivos .class creados anteriormente
jar: classes
	jar cfm test.jar manifest.mf -C build/classes .

# compila todos los archivos .java de la carpeta src, y los guarda como archivo .class en la carpeta build/classes
classes: dir
	javac -sourcepath src/ -d build/classes src/*.java

# crea los directorios build/classes y build/jar
dir:
	if [ ! -d build/classes ]; then mkdir -p build/classes; fi
	if [ ! -d build/jar ]; then mkdir -p build/jar; fi

# borra los archivos creados para volver a ejecutar
clean:
	if [ -d build ]; then rm build -R; fi
	if [ test.jar ]; then rm test.jar -R; fi

# ejecuta el archivo .jar
run:
	java -jar test.jar
