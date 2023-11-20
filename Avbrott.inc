.equ TIMER2_TICK = 60					// 16 000 000 / prescaler 256 / 15625 = 4 (fyra avbrott i sekunden)
//----------------------------------------------------------------------------


// Initiering av timern, görs i början av programmet t.ex. i någon HARDWARE_INIT
FPS_INIT:															
	ldi		r16, (1<<WGM12)|(1<<CS12)		// Waveform gen mode 12 | Clock select 12 (= prescaler 256)
	sts		TCCR1B, r16
	ldi		r16, HIGH(TIMER2_TICK)			// Höga delen av TIMER1_TICK
	sts		OCR1AH, r16
	ldi		r16, LOW(TIMER2_TICK)			// Låga delen av TIMRE1_TICK
	sts		OCR1AL, r16
	ldi		r16,(1<<OCIE1A)					// Tillåt avbrott	
	sts		TIMSK1, r16
	ret
//----------------------------------------------------------------------------


// ----- Rutinen som utförs --------------------------------------------------
FPS_RUTIN:

call RETREIVE_PIXEL
	// pusha register och flaggor
	// blablabla
	// poppa register och flaggor
	reti
// ---------------------------------------------------------------------------


.equ TIMER1_TICK =  15625					// 16 000 000 / prescaler 256 / 15625 = 4 (fyra avbrott i sekunden)
//----------------------------------------------------------------------------


// Initiering av timern, görs i början av programmet t.ex. i någon HARDWARE_INIT
AVBROTTSRUTIN_INIT:															
	ldi		r16, (1<<WGM12)|(1<<CS12)		// Waveform gen mode 12 | Clock select 12 (= prescaler 256)
	sts		TCCR1B, r16
	ldi		r16, HIGH(TIMER1_TICK)			// Höga delen av TIMER1_TICK
	sts		OCR1AH, r16
	ldi		r16, LOW(TIMER1_TICK)			// Låga delen av TIMRE1_TICK
	sts		OCR1AL, r16
	ldi		r16,(1<<OCIE1A)					// Tillåt avbrott	
	sts		TIMSK1, r16
	ret
//------------------------------------------A----------------------------------


// ----- Rutinen som utförs --------------------------------------------------
AVBROTTSRUTIN:

	push YL
	push r17
	push r25
	call DINO_ANIMATION1
//	call RETREIVE_PIXEL
	pop r25
	pop r17
	pop YL
	// pusha register och flaggor
	// blablabla
	// poppa register och flaggor
	reti
// ---------------------------------------------------------------------------
