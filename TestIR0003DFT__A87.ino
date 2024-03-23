  //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Compteur de passage - ATTINY85 - TM1637 - Barette NeopiXEL - TCRT5000
  // Vidéo YouTube DFT_#A87 Compteur de passage - ATTINY85 - TM1637 - Barette NeopiXEL - TCRT5000
  // https://youtu.be/j5TxYYgkPBA
  // Claude DUFOURMONT
  // https://www.youtube.com/c/ClaudeDufourmont
  // claude.dufourmont@laposte.net
  //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
  #include <Adafruit_NeoPixel.h>                                // Librairie pour Néopixel
  #include <TM1637Display.h>                                    // Librairie pour afficheur 4 digit 7 segments drivé par TM1637
  #define CLK1 4                                                // PB4 affecté à la pin Clock TM1637
  #define DIO1 0                                                // PB0 affecté à la pin DIO TM1637
    
  #define BrocheCapteurInfraRouge 2                             // PB2 affecté à la pin D0 du TCRT5000 (capteur IR)
  #define BrocheBuzzer 1                                        // PB1 affecté au Buzzer
 //#define BrocheBuzzer 3
 //#define PIN      1
  #define PIN      3                                            // PB3 affecté à la broche DIN de la barette Néopixel
  #define N_LEDS 8
  
  TM1637Display display(CLK1, DIO1);                            // Objet afficheur avec ses ports affectés
  Adafruit_NeoPixel strip(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);   // Objet barette Néopixel
  
  int NbreDetectionCapteurInfraRouge = 0;                       // Initialisation à zéro du nombre de pasages détectés
  int NbrePoints = 0;                                           // Initialisation à zéro du nombre de points
  
  void setup() 
  {
  pinMode(BrocheCapteurInfraRouge, INPUT_PULLUP);               
  pinMode(BrocheBuzzer, OUTPUT);

  display.setBrightness(0x0b);                                  // Iniatialisation de la brillance (échelle max = 0x0F)de l'afficheur 7 segments
  display.clear ();                                             // Effacement afficheur 7 segments
  
  strip.begin();                                                // Préparation à afficher sur Néopixel
  strip.clear();                                                // Effacement afficheur Néopixel
  strip.setBrightness(20);                                      // Initialisation de la brillance (échelle max = 255) de la barette Néopixel
  strip.show();                                                 // Affichage Néopixel
 
  }

  void loop() 
  {
    
  display.showNumberDec(NbrePoints,false, 4,0) ;                // Affichage nombre de points sur 7 segments
 
  if(digitalRead(BrocheCapteurInfraRouge)==LOW)                 // Comptage conditionnel des points, affichage et animation sonore et lumineuse
  { 
          delay(10);
          if(NbreDetectionCapteurInfraRouge==0)
          {
          NbrePoints=NbrePoints+5;
          display.showNumberDec(NbrePoints,false, 4,0) ;
          AnimationPassage1 ();         //ROUGE
          }
          
          if(NbreDetectionCapteurInfraRouge==1)
          {
          NbrePoints=NbrePoints+10;
          display.showNumberDec(NbrePoints,false, 4,0) ;
          AnimationPassage2 ();         //VERT
          }
          
          if(NbreDetectionCapteurInfraRouge==2)
          {
          NbrePoints=NbrePoints+20;
          display.showNumberDec(NbrePoints,false, 4,0) ;
          AnimationPassage4 ();         //ETEINT
          }
          NbreDetectionCapteurInfraRouge++;
          
          if(NbreDetectionCapteurInfraRouge==3)             //BLEU
          {
          NbreDetectionCapteurInfraRouge=0;
          AnimationPassage3 ();
          }
          delay(20);
  }
  
  }

  void Buzzer (int TempsH, int TempsL, int nb)                            // TempsH => délai buzzer ON, TempsL => délai buzzer OFF, nb => nombre de bips
  {
  for (int x = 1; x <= nb; x++) // ************************************** // Boucle le nombre de fois voulu passé par l'argument "int nb"
  {
  digitalWrite(BrocheBuzzer, HIGH);                                       // Active le buzzer
  delay (TempsH);                                                         // Temporisation à l'état haut du buzzer pendant la durée passée par l'argument "int TempsH"
  digitalWrite(BrocheBuzzer, LOW);                                        // Désactive le buzzer
  delay (TempsL);                                                         // Temporisation à l'état bas du buzzer pendant la durée passée par l'argument "int TempsL"
  }
  }

  void AnimationPassage1 ()
  {
  for (int w = 0; w<= 3; w++)
  
  {
  strip.setPixelColor(w, 255, 0, 0);
  strip.show (); 
  }

  for (int w = 4; w<= 7; w++)
  
  {
  strip.setPixelColor(w, 255, 0, 255);
  strip.show (); 
  }
  
  
  Buzzer(50, 80, 1);
  delay (40);
  }
  
  void AnimationPassage2 ()
  {
  for (int w = 0; w<= 3; w++)
  {
  strip.setPixelColor(w, 0, 255, 0); 
  strip.show (); 
  }

  for (int w = 4; w<= 7; w++)
  {
  strip.setPixelColor(w, 0, 0, 255); 
  strip.show (); 
  }
  
  Buzzer(50, 80, 2);
  delay (5);
  }
  
  void AnimationPassage3 ()
  { 
  for (int w = 0; w<= 7; w++)
  {
  strip.setPixelColor(w, 0, 0, 255);
  strip.show (); 
  }
  
  Buzzer(500, 80, 3);
  delay (5);
  }
  
  void AnimationPassage4 ()
  {
  for (int w = 0; w<= 7; w++)
  {
  strip.setPixelColor(w, 0, 0, 0);
  strip.show (); 
  }
  
  //Buzzer(50, 80, 1);
  delay (5);
  }
  
