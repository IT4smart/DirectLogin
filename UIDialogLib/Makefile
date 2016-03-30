all: UIDialogLib.so

CFLAGS=-fpic -Wall -I../inc

.c.o:
	$(CC) -std=c11 -c $(CFLAGS) -o $@ $+

UIDialogLib.so: UIDialogLibUtil.o UIDialogLib.o
	$(CC) -shared -o UIDialogLib.so $+

clean:
	rm -f UIDialogLibUtil.o UIDialogLib.o UIDialogLib.so
