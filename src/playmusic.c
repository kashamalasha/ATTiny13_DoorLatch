/*
	Music demo.

	Microcontroller: ATTiny45
	Clock: 8 MHz
	External hardware: Piezzo buzzer/speaker connected to PB2/OCR1B (PDIP pin 7)
	Compiler: AVR GCC

	http://aquaticus.info/pwm-music
*/

#include <avr/io.h>
#include <util/delay.h>
#include "notes.h"      //Нотная тетрадь
#include "playmusic.h"  //Forward declaration

/**
	Initialize timer1

	PWM output on OCR1B
*/

void InitMusic(){
	// Configure OC1B pin as output
	DDRB |=
        	(1 << PB2); //OC1B as output

	// timer1 configuration (for PWM)
	TCCR1A |=
        	(1 << COM1B1);  // Clear OC1A/OC1B on compare match

	TCCR1B |=
        	(1 << WGM13) |	//mode 8, PWM, Phase and Frequency Correct (TOP value is ICR1)
        	(1 << CS11); 		//prescaler(8)
}


/**
	Plays music.
*/

void PlayMusic( const int* pMusicNotes /** Pointer to table containing music data */,
				uint8_t tempo /** paying tempo from 0 to 100. Higher value = slower playback*/ ){
	int duration;
	int note;
	int i;
	uint16_t delay = tempo * 1000;

	while( *pMusicNotes ){
		note = *pMusicNotes;
		pMusicNotes++;

		duration = *pMusicNotes;
		pMusicNotes++;

		if( p == note ){
			//pause, do not generate any sound
			OCR1B = 0;
		} else {
			//not a pause, generate tone
			OCR1B = DEFAULT_VOLUME;

			//set frequency
			ICR1H = (note >> 8);
			ICR1L = note;
		}

		//wait duration
		for(i=0;i<32-duration;i++){
			_delay_loop_2( delay );
		}
	}

	//turn off any sound
	OCR1B = 0;
}

//https://www.youtube.com/watch?v=h-JTggIpH3k - разбор мелодии
const int PinkPanther[] = {
    P, 16,
    D4x, 16, E4, 16, P, 4, P, 4,
    F4x, 16, G4, 16, P, 4, P, 4,
    D4x, 16, E4, 16, P, 16,
    F4x, 16, G4, 16, P, 16,
    C5, 16, B4, 16, P, 16,
    E4, 16, G4, 16, P, 16,
    B4, 16, A4x, 2, A4x, 2, P, 16,  					//0,22
    A4, 16, G4, 16, E4, 16, D4, 16, E4, 2, E4, 2, P, 8, P, 2, P, 2, 	//0,24
    D4x, 16, E4, 16, P, 4, P, 4,
    F4x, 16, G4, 16, P, 4, P, 4,
    D4x, 16, E4, 16, P, 16,
    F4x, 16, G4, 16, P, 16,
    C5, 16, B4, 16, P, 16,
    G4, 16, B4, 16, P, 16,
    E5, 16, D5x, 2, D5x, 2, D5x, 16, P, 4, P, 2, P, 2,			//0,33
    D4x, 16, E4, 16, P, 4, P, 4,
    F4x, 16, G4, 16, P, 4, P, 4,
    D4x, 16, E4, 16, P, 16,
    F4x, 16, G4, 16, P, 16,
    C5, 16, B4, 16, P, 16,
    E4, 16, G4, 16, P, 16,
    B4, 16, A4x, 2, A4x, 2, P, 16,  					//0,39
    A4, 16, G4, 16, E4, 16, D4, 16, E4, 2, E4, 2, P, 8, P, 2, P, 2, 	//0,41
    E5, 2, D5, 8, B4, 2, A4, 8, H4, 4, E4, 16, A4x, 16, A4, 8, A4x, 16, A4, 8, A4x, 16, A4, 8, H4, 16, E4, 16, D4, 16, E4, 2, E4, 2, E4, 2, //0,48
    MUSIC_END
};
