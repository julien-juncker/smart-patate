//****************************************************************************************
// Illutron take on Disney style capacitive touch sensor using only passives and Arduino
// Dzl 2012
//****************************************************************************************


//                              10n
// PIN 9 --[10k]-+-----10mH---+--||-- OBJECT
//               |            |
//              3.3k          |
//               |            V 1N4148 diode
//              GND           |
//                            |
//Analog 0 ---+------+--------+
//            |      |
//          100pf   1MOmhm
//            |      |
//           GND    GND



#define SET(x,y) (x |=(1<<y))				//-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))       		// |
#define CHK(x,y) (x & (1<<y))           		// |
#define TOG(x,y) (x^=(1<<y))            		//-+



#define N 160  //How many frequencies

float results[N];            //-Filtered result buffer
float freq[N];            //-Filtered result buffer
int sizeOfArray = N;

 
   
   

void setup()
{
  
  
  TCCR1A=0b10000010;        //-Set up frequency generator
  TCCR1B=0b00011001;        //-+
  ICR1=110;
  OCR1A=55;

  pinMode(9,OUTPUT);        //-Signal generator pin
  pinMode(8,OUTPUT);        //-Sync (test) pin
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  
  Serial.begin(115200);

  for(int i=0;i<N;i++)      //-Preset results
    results[i]=0;         //-+
}

void loop()
{
  unsigned int d;

  int counter = 0;
  for(unsigned int d=0;d<N;d++)
  {
    int v=analogRead(0);    //-Read response signal
    CLR(TCCR1B,0);          //-Stop generator
    TCNT1=0;                //-Reload new frequency
    ICR1=d;                 // |
    OCR1A=d/2;              //-+
    SET(TCCR1B,0);          //-Restart generator

    results[d]=results[d]*0.5+(float)(v)*0.5; //Filter results
   
    freq[d] = d;
   Serial.println(v); 
  float valeur =analogRead(0);
  if ((440<=valeur) && (valeur<480)){
    digitalWrite(7,HIGH);
    digitalWrite(6,HIGH);
  }
  if ((485<=valeur) && (valeur<450)){
    digitalWrite(7,LOW);
    digitalWrite(6,HIGH);
  }
   if ((560<=valeur) && (valeur<620)){
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);
  }


 //   plot(v,0);              //-Display
 //   plot(results[d],1);
  // delayMicroseconds(1);
  }


PlottArray(1,freq,results); 
int me=analogRead(0);
 Serial.println(me); 
    if ((590>=me)&&(me<=1000)){
     digitalWrite(6,LOW);
     digitalWrite(7,LOW);
    }
    else if ((440>=me)&&(me<=489)){
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
    }

  TOG(PORTB,0);            //-Toggle pin 8 after each sweep (good for scope)
}
   
