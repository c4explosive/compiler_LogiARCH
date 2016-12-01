ds:
li	r10	0
pr: li	r11	1
pwr: li	r0	0      
li	r1	80
op:
li	r2	7
st:
jmp aqui
li	r6	128
ty:
and	r3	r1 r6
pu: cmp	r3	r10
or R4 R5 r5
spc R4
aqui: jmp aqui