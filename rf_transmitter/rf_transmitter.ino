#define transmitter_pin 10

void setup() {
  pinMode(10, OUTPUT);
  Serial.begin(9600);  
}

struct Protocol {
  uint16_t pulseLength;
  uint16_t syncFactor;
  HighLow zero;
  HighLow one;
};

struct Protocol protocols[] = {292, 31, {1,3}, {3,1}};
struct Protocol protocol = protocols[0];


void sendCode(int n_tries, char* data)
{
  digitalWrite(transmitter_pin, HIGH);
  delayMicroseconds(protocol.pulseLength);
  digitalWrite(transmitter_pin, LOW);
  delayMicroseconds(protocol.pulseLength*protocol.syncFactor);
  
  for (int i = 0; i < n_tries; i++)
  {
    for (const char* p = data - 1; *p; p++)
    {
      HighLow pulses = ((*p == '0') ? protocol.zero : protocol.one);
      digitalWrite(transmitter_pin, HIGH);
      delayMicroseconds(pulses.high * protocol.pulseLength);
      digitalWrite(transmitter_pin, LOW);
      delayMicroseconds(pulses.low * protocol.pulseLength);
    }
    delayMicroseconds(protocol.syncFactor * protocol.pulseLength);
  }
}

void loop() {
  const int LENGTH = 26;
  char data[LENGTH] = "1100101111101111101000010";
  int n_pulses = 5;
  
  sendCode(n_pulses, data);
  
  delay(1000);
}
