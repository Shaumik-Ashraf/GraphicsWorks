picmaker: picmaker.c
	gcc -w -o picmaker picmaker.c -lm

push: picmaker
	./picmaker SA_image.ppm
	convert SA_image.ppm SA_image.png
	rm *.ppm
	rm picmaker
	git add --all
	git commit -a -m "image gallery hw"
	git push
