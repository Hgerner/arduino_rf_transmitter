/*
  Example for different sending methods
  
  https://github.com/sui77/rc-switch/
  
*/
#define transmitter_pin 10

void setup() {

  pinMode(10, OUTPUT);
  Serial.begin(9600);
  
}

char* high = "1110";
char* low = "1000";

struct HighLow {
        uint8_t high;
        uint8_t low;
};

struct Protocol {
  uint16_t pulseLength;
  uint16_t syncFactor;
  HighLow zero;
  HighLow one;
};

struct Protocol protocols[] = {292, 31, {1,3}, {3,1}};

//void setProtocol(

void sendCode(int n_tries, char* data, struct Protocol protocol)
{
  digitalWrite(transmitter_pin, HIGH);
  delayMicroseconds(protocol.pulseLength);
  digitalWrite(transmitter_pin, LOW);
  delayMicroseconds(protocol.pulseLength*protocol.syncFactor);
  
  for (int i = 0; i < n_tries; i++)
  {
    for (const char* p = data - 1; *p; p++)
    {
      if (*p == NULL)
        continue;
      HighLow pulses = ((*p == '0') ? protocol.zero : protocol.one);
      digitalWrite(transmitter_pin, HIGH);
      delayMicroseconds(pulses.high * protocol.pulseLength);
      digitalWrite(transmitter_pin, LOW);
      delayMicroseconds(pulses.low * protocol.pulseLength);
    }
    delayMicroseconds(protocol.syncFactor * protocol.pulseLength);
  }
}

void transmit(char* code, int length)
{
  
}

void loop() {

  int seperationDuration = 9140;
  const int pulselength = 292;
  int initDuration = seperationDuration;
  const int LENGTH = 25;
  
  //char* data = "1110 1110 1000 1000 1110 1000 1110 1110 1110 1110 1110 1000 1110 1110 1110 1110 1110 1000 1110 1000 1000 1000 1000 1110 1000";
  char data[LENGTH] = "1100101111101111101000010";
  int n_pulses = 4;
  //Serial.println(sizeof(data)/sizeof(data[0]));

  sendCode(5, data, protocols[0]);

  
  /*digitalWrite(10, HIGH);
  delayMicroseconds(initDuration);
  digitalWrite(10, LOW);
  for (int i = 0; i < n_pulses; i++)
  {
    for (int j = 0; j < LENGTH; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        if (data[j] == '0')
        {
          digitalWrite(10, (low[k] == '0') ? LOW : HIGH);
        }
        else
        {
          digitalWrite(10, (high[k] == '0') ? LOW : HIGH);
        }
        delayMicroseconds(pulselength); 
      }
      
    }
    digitalWrite(10, LOW);
    delayMicroseconds(seperationDuration);
  }
  digitalWrite(10, LOW);
*/
  delay(1000);
}
