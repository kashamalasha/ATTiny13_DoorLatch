#include <stdio.h>
#include <stdlib.h>

void InitMusic() {
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


int main(void){
    InitMusic();

    printf("Hello World");
    return 0;
}
