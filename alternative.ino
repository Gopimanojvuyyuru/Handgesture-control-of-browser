const int trigPin1 = 2; // the number of the trigger output pin ( sensor 1 )
const int echoPin1 = 3; // the number of the echo input pin ( sensor 1 )     
const int trigPin2 = 4;  // the number of the trigger output pin ( sensor 2 ) 
const int echoPin2 = 5;  // the number of the echo input pin ( sensor 2 ) 

////////////////////////////////// variables used for distance calculation 
long duration;                               
int distance1, distance2; 
float r;
unsigned long temp=0;
int temp1=0;
int l=0;


void find_distance (void);

// this function returns the value in cm.
/*we should not trigger the both ultrasonic sensor at the same time. 
it might cause error result due to the intraction of the both soundswaves.*/ 
void find_distance (void)                   
{ 
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration = pulseIn(echoPin1, HIGH, 5000);// here this pulsein function wont wait more then 5000us for the ultrasonic sound to came back. (due to this it wont measure more than 60cm)
                                           // it helps this project to use the gesture control in the defined space. 
                                           // so that, it will return zero if distance greater then 60m. ( it helps usually if we remove our hands infront of the sensors ).
 
  r = 3.4 * duration / 2;                  // calculation to get the measurement in cm using the time returned by the pulsein function.     
  distance1 = r / 100.00;
  /////////////////////////////////////////upper part for left sensor and lower part for right sensor
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration = pulseIn(echoPin2, HIGH, 5000);
  r = 3.4 * duration / 2;     
  distance2 = r / 100.00;
  delay(100);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT); // initialize the trigger and echo pins of both the sensor as input and output:
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  delay (1000);
    
}

void loop()
{
  find_distance(); 
                   
  if(distance2<=35 && distance2>=15) 
  { 
    temp=millis();                   
    while(millis()<=(temp+300))     
    find_distance();
    if(distance2<=35 && distance2>=15)  
    {
     temp=distance2;                         
     while(distance2<=50 || distance2==0)    
     {
       find_distance();                      
       if((temp+6)<distance2)                 
       {
       Serial.println("down");              
       }
       else if((temp-6)>distance2)           
       {
        Serial.println("up");                
       }
     }
    }
       else                                     // this condition becomes true, if we only swipe in front of the right sensor . 
      {
        Serial.println("next");                // send "next" serially.
      }
  }
  else if(distance1<=35 && distance1>=15)   
  { 
  
    temp=millis();                           
  
    while(millis()<=(temp+300))             
    {
       find_distance();
       if(distance2<=35 && distance2>=15)  
       {
         Serial.println("change");         
         l=1;                              
         break;                           
       }
    }
    
    if(l==0)                               
    {
    Serial.println("previous");            
    while(distance1<=35 && distance1>=15) 
    find_distance();                      
    }
    l=0;                                  
   
}
}
