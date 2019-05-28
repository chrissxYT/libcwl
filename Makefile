all:
	@gcc -O3 *.c -shared -s -o libcwl.so

test:
	@gcc -Og *.c -shared -o libcwl.so
