.equ MOSI = PB3
.equ MISO = PB4
.equ SCLK = PB5
.equ SPI_DDR = DDRB
.equ CS = PB2


ANOD_X:
.db $0, $C, $18, $24, $30, $3C, $48, $54, $00
.cseg



SPI_MASTER_INIT: // Enable spi_spcr, sätta att vi är master, sänka hastigheten (Fosc/128)= sänka till långsamste hastigheten
		ldi r17, (1<<MOSI)|(1<<SCLK)|(1<<PB2)
		out SPI_DDR, r17
		ldi r17, (1<<SPE) | (1<<MSTR) | (1<< SPR0)
		out SPCR, r17
		ret

//----------------------------------------------------------------
RETREIVE_PIXEL:
		//ldi r25, 8

SENDEIGHT: 
		//call	SEND_LINE_4X
		ldi		r19,12
		cpi		r30, $b1
		brlo	matrix_loop
		ldi		r30,$50
		ldi		r31,0b00000001

	//Set radnr 
		
MATRIX_LOOP: // Plocka in värdet från videominnet+0, lägg in i r16 -> lägg in i slussen
		ld		r16,Z+
		call	SPI_TRANSMIT
		clr		r16
		dec		r19
		cpi		r19, 0
		brne	MATRIX_LOOP
		
SPI_SEND:
		sbi PORTB,PB2
		nop
		cbi PORTB,PB2
		ret
	
//----------------------------------------------------------------

SPI_TRANSMIT:
		// push r16
		out SPDR, r16
		// jmp WAIT_TRANSMIT


WAIT_TRANSMIT:
		in r16,SPSR
		sbrs r16, SPIF
		rjmp WAIT_TRANSMIT
		ret


SHORT_WAIT:
		adiw r24,8 //1ms
		brne SHORT_WAIT
		ret
