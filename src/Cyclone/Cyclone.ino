// schrdh 2024
// Interfaced for pinduino shield v0.3
// Uses pinduino library

#include <pinduino.h>
int aLEDNum1 = 50;
int aLEDNum2 = 50;

pinduino pd(aLEDNum1, aLEDNum2, "Nano");

int attract_on = 1;                       // flag for running attract mode
unsigned long timeLastEvent = 0;          // time last event was last triggered
unsigned long startChaseWaitTime = 20000; // Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "white";                   // attract color
int attract_style = 1;

void setup()
{
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset();
}

void loop()
{
  if (attract_on)
  {
    attractMode();
  }

  //   Print the pin states out to serial
  //pd.pinState()->print();

  pd.pinState()->update();
  checkPinStates();
  if (millis() - timeLastEvent > startChaseWaitTime)
  {
    attract_on = 1;
  }
}

void checkPinStates()
{
  int trigger = 0;
  // Note:  P11-2 and P12-3 are key pins

  // P11-1 01A Outhole Kicker
  if (pd.pinState()->P11(1) && !pd.pinState()->P12(5))
  {
    //trigger = 1;
  }
  // P11-1 01C L F Wheel (p) & Jackpot (b) Flashers
  else if (pd.pinState()->P11(1) && pd.pinState()->P12(5))
  {
    //trigger = 1;
  }

  // P11-3 02C R F Wheel (p) & Teeth (b) Flashers
  if (pd.pinState()->P11(3) && pd.pinState()->P12(5))
  {
    //trigger = 1;
  }

  // P11-4 03A Ball Shooter Kickbig
  if (pd.pinState()->P11(4) && !pd.pinState()->P12(5))
  {
    //trigger = 1;
  }
  // P11-4 03C Top mif (p) & L Eye (b) Flashers
  else if (pd.pinState()->P11(4) && pd.pinState()->P12(5))
  {
    //trigger = 1;
  }

  // P11-5 04A Boomerang Kickbig
  if (pd.pinState()->P11(5) && !pd.pinState()->P12(5))
  {
    //trigger = 1;
  }
  // P11-5 04C Cat (p) & lwr Fireworks (b) Flashers
  else if (pd.pinState()->P11(5) && pd.pinState()->P12(5))
  {
    //trigger = 1;
  }

  // P11-6 05A Drop Target
  if (pd.pinState()->P11(6) && !pd.pinState()->P12(5))
  {
    //trigger = 1;
  }
  // P11-6 05C Ducks (p) & R Fireworks (b) Flashers
  else if (pd.pinState()->P11(6) && pd.pinState()->P12(5))
  {
    //trigger = 1;
  }

  // P11-7 06C Ferris Wheel (p) Flashers
  if (pd.pinState()->P11(7) && pd.pinState()->P12(5))
  {
    //trigger = 1;
  }

  // P11-8 07A Knocker / Ticket Dispenser (b'box)
  if (pd.pinState()->P11(8) && !pd.pinState()->P12(5))
  {
    //trigger = 1;
  }
  // P11-8 07C Cyclone (p) & R Eye (b) Flashers
  else if (pd.pinState()->P11(8) && pd.pinState()->P12(5))
  {
    //trigger = 1;
  }

  // P11-9 08C Spook House (p) & L Fireworks (b) Flashers
  if (pd.pinState()->P11(9) && pd.pinState()->P12(5))
  {
    //trigger = 1;
  }

  // P12-1 09 Spook House Bonus Flasher (p)
  if (pd.pinState()->P12(1))
  {
    //trigger = 1;
  }

  // P12-2 10 Playfield Gen Illumination Relay (p)
  if (pd.pinState()->P12(2))
  {
    //trigger = 1;
  }

  // P12-4 11 Backglass Gen Illumination Relay (b)
  if (pd.pinState()->P12(4))
  {
    //trigger = 1;
  }

  // P12-6 13 Mystery Wheel (b) Coil B
  if (pd.pinState()->P12(6))
  {
    //trigger = 1;
  }

  // P12-7 14 Mystery Wheel (b) Coil A
  if (pd.pinState()->P12(7))
  {
    //trigger = 1;
  }

  // P12-8 Boomerang Flashers (p)
  if (pd.pinState()->P12(8))
  {
    //trigger = 1;
  }

  // P12-9 Ferris Wheel Motor/Relay (p)
  if (pd.pinState()->P12(9))
  {
    //trigger = 1;
  }

  // trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger)
  {
    timeLastEvent = millis();
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.pinState()->reset();
    trigger = 0;
    attract_on = 0;
  }

  // end function checkPinStates
}

void attractMode()
{
  if (attract_style)
  {
    pd.adrLED1()->sparkle(color, 20, 30);
    pd.adrLED2()->sparkle(color, 20, 30);
    if (random(1000) == 0)
    {
      if (color == "white")
        color = "red";
      else if (color == "red")
        color = "blue";
      else
        color = "white";
    }
  }
  else
  {
    pd.adrLED1()->dataStreamNoTail2Color("blue", "red", 20, 20, 1);
    pd.adrLED2()->dataStreamNoTail2Color("blue", "red", 20, 20, 1);
  }
  if (random(1000) == 0)
  {
    if (attract_style)
    {
      attract_style = 0;
    }
    else
    {
      attract_style = 1;
    }
  }
}
