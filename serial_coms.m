s = serial('/dev/tty.usbmodemM4321001');
set(s,'BaudRate',9600);
fopen(s);


fprintf(s,'g')
fscanf(s)

fprintf(s,'a')
fscanf(s)

fprintf(s,'n')
fscanf(s)

fprintf(s,'g')
fscanf(s)



fclose(s)
delete(s)
clear s