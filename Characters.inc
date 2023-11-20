DINO_ANIMATION1:		//lägger rätt anod data i var 4 byte 

		inc r28
		inc r24
		cpi r24, 44 //36
		brlo DINO_ANIMATION1
		clr r24
		call MOVE
		ret

DINO_ANIMATION2:
		ldi		YL, $70
		call	MOVE
		ret

DINO_ANIMATION3:
		ldi		YL, $64
		call	MOVE
		ret

MOVE:	//flyttar pekaren 12 positioner och sätter in nya värden i dom första 3 byten
		call INC_BYTES
MOVE_LOOP:
		inc r28
		inc r24
		cpi r24,10 //36
		brlo MOVE_LOOP
		call INC_TAIL
		clr r24
PUT_TAIL:
		inc r28
		inc r24
		cpi	r24,10
		brne PUT_TAIL
		call INC_BYTES
		clr r24
REMOVE_FEET:
		inc r28
		inc r24
		cpi r24,10
		brne REMOVE_FEET
		call REMOVE_BYTES
		clr r24
		call RESET_POINTER
		ret

DOWN:	//flyttar pekaren 12 positioner och sätter in nya värden i dom första 3 byten
		call REMOVE_BYTES
DOWN_LOOP:
		inc r28
		inc r24
		cpi r24,10 //36
		brlo DOWN_LOOP
		call INC_BYTES
		clr r24
PUT_TAIL_D:
		inc r28
		inc r24
		cpi	r24,10
		brne PUT_TAIL_D
		call INC_TAIL
		clr r24
ADD_FEET:
		inc r28
		inc r24
		cpi r24,10
		brne ADD_FEET
		call INC_BYTES
		call RESET_POINTER

		clr r24
	
		ret

INC_BYTES:				// var r18 förut 
		push	r20
		ldi		r20,0b00110000
		st		Y, r20
		inc		r28
		st		Y,r20
		inc		r28
		st		Y, r20
		pop		r20
		ret

REMOVE_BYTES:
		st		Y, r19
		inc		r28
		st		Y,r19
		inc		r28
		st		Y, r19
		ret

INC_TAIL:
		push	r20
		ldi		r20, 0b01110000
		st		Y, r22
		inc		r28
		st		Y, r22
		inc		r28
		st		Y,r22
		pop		r20
		ret

LOAD_FLOOR: 
		push	r17
		push	r19
		
		ldi		r19, $00
		ldi		r17, $FF

		sts		vmem+92,r19
		sts		vmem+93,r17
		sts		vmem+94, r19
	
		sts		vmem+88,r19
		sts		vmem+89,r17
		sts		vmem+90, r19

		sts		vmem+96,r19
		sts		vmem+97,r17
		sts		vmem+98, r19

		pop		r19
		pop		r17
		ret

LOAD_DINO: 
		push	r16
		push	r18
		
		ldi		r16, 0b01110000
		ldi		r18, 0b00110000

		sts		vmem+56, r18
		sts		vmem+57, r18
		sts		vmem+58, r18
		
		sts		vmem+68, r16
		sts		vmem+69, r16
		sts		vmem+70, r16

		sts		vmem+80, r18
		sts		vmem+81, r18
		sts		vmem+82, r18

		pop		r18
		pop		r16
		ret
