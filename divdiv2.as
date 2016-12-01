;sdhkjsd
;sjad		
		li r10 0     
        li r11 1     
        li r0 0      
		li r1 80   
		
		
		li r2 7   
		
		
		
		;Y aqui
		;what
		li r6 128    
        and r3 r1 r6 r0
        cmp r3 r10 
		bra sal     
		li r3 1      
sal1:	or r7 r1 r10 ;sal1 es una etiqueta de prueba
		sl r1 r7   
    	LI R4 0      
div:    li r8 254    
        or r7 r1 r10 ;aqui hay un or
        and r1 r7 r8 
    	or r7 r4 r10 
		sl r4 r7     ;sl es un nemonico
		sub r5 r3 r2 
		slt r10 r5   
		bra div1  	
        or r7 r4 r10 
        add r4 r7 r11 ;creo que r4 es para guardar el residuo
        or r3 r5 r10 
div1:   or r7 r0 r10 
        add r0 r7 r11
        li r8 8      
        cmp r0 r8    
        bra fin      
        or r8 r3 r10 
        sl r3 r8     
        and r8 r1 r6 
        cmp r8 r10   
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
        bra sal2     
        or r7 r3 r10 
		add r3 r7 r11
sal2:   or r7 r1 r10 
        sl r1 r7     
        jmp div      
fin:    jmp fin

