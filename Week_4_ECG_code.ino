//------Functions--------//
static inline void initTimer(void) { 
  TCNT1 = 65483; //preload timer - is a little above 100Hz to make it a whole number (number of steps/peaks in the wave)
  TCCR1B |= (1 << CS12) | (1 << CS10);  //1024 prescalar (width of the wave)
  TIMSK1 |= (1 << TOIE1); //enable overflow timer
}

static inline void initIOPorts(void) { //initializes the GPIO ports
  DDRC &= (0<<PC0); //use the & operator to make sure that A2 pin stays as an input 
}

static inline void initADC(void) { //initialize the ADC 
  ADMUX |= (1 << REFS0);    // Reference voltage on the AVCC
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  //ADC prescalar
  ADCSRA |= (1 << ADEN);    //enables ADC
  ADCSRA |= (1 << ADIE);    //ADC interrupts Enable
}


//------Interrupt Service Routine--------//
ISR (TIMER1_OVF_vect) { //interrupt servie routine for the Timer 1 Overflow//
  ADCSRA |= (1 << ADSC); //starts the next ADC conversion
  TCNT1 = 65483; //sets timer as to 100Hz
}


ISR(ADC_vect) {
  //interrupt servie routine for the ADC//
  //executed when the ADC completes a coversion//
  Serial.println(ADC);  //prints the value of the ADC onto the serial moniter
  //TCNT1 = 65379; //sets timer as to 100Hz
}

int main(void) {
  
  Serial.begin(9600); //intializes the serial moniter
  initTimer();
  noInterrupts(); // disables interrupts functions- with the interrupts function it is the same as sei()
  initIOPorts(); 
  initADC();
  interrupts();
  
  while(1) {
     
  }
  return 0;
}
