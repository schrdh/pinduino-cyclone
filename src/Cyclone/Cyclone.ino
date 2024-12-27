// schrdh 2024
// Interfaced for pinduino shield v0.3
// Uses pinduino library

#include <pinduino.h>
int aLEDNum1 = 39; // Ferris Wweel Ramp
int aLEDNum2 = 40; // Cyclone ramp

pinduino pd(aLEDNum1, aLEDNum2, "Nano");

int attract_on = 0;                    // flag for running attract mode
unsigned long timeLastEvent = 0;       // time last event was last triggered
unsigned long attractWaitTime = 20000; // Amount of time to wait before attract mode start up again 1000 == 1 second
String attractColor = "green";         // attract color

void setup()
{
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset();
}

void loop()
{
  pd.pinState()->update();

  // Print the pin states out to serial
  // pd.pinState()->print();

  checkPinStates();

  if (millis() - timeLastEvent > attractWaitTime)
    attract_on = 1;

  if (attract_on)
    attractMode();
}

void checkPinStates()
{
  int trigger = 0;
  // Note:  P11-2 and P12-3 are key pins

  // When AC-Relay is enabled (Flashers)
  if (pd.pinState()->P12(5))
  {
    // P11-1 01C L F Wheel (p) & Jackpot (b) Flashers
    if (pd.pinState()->P11(1))
    {
      // trigger = 1;
    }

    // P11-3 02C R F Wheel (p) & Teeth (b) Flashers
    if (pd.pinState()->P11(3))
    {
      // trigger = 1;
    }

    // P11-4 03C Top mif (p) & L Eye (b) Flashers
    if (pd.pinState()->P11(4))
    {
      // trigger = 1;
    }

    // P11-5 04C Cat (p) & lwr Fireworks (b) Flashers
    if (pd.pinState()->P11(5))
    {
      // trigger = 1;
    }

    // P11-6 05C Ducks (p) & R Fireworks (b) Flashers
    if (pd.pinState()->P11(6))
    {
      // trigger = 1;
    }

    // P11-7 06C Ferris Wheel (p) Flashers
    if (pd.pinState()->P11(7))
    {
      // trigger = 1;
    }

    // P11-8 07C Cyclone (p) & R Eye (b) Flashers
    if (pd.pinState()->P11(8))
    {
      // trigger = 1;
    }

    // P11-9 08C Spook House (p) & L Fireworks (b) Flashers
    if (pd.pinState()->P11(9))
    {
      // trigger = 1;
    }
  }

  // When AC-Relay is disabled (Coils)
  else
  {

    // P11-1 01A Outhole Kicker
    if (pd.pinState()->P11(1))
    {
      // trigger = 1;
    }

    // P11-4 03A Ball Shooter Kickbig
    if (pd.pinState()->P11(4))
    {
      // trigger = 1;
    }

    // P11-5 04A Boomerang Kickbig
    if (pd.pinState()->P11(5))
    {
      // trigger = 1;
    }

    // P11-6 05A Drop Target
    if (pd.pinState()->P11(6))
    {
      // trigger = 1;
    }

    // P11-8 07A Knocker / Ticket Dispenser (b'box)
    if (pd.pinState()->P11(8))
    {
      // trigger = 1;
    }
  }

  // P12-1 09 Spook House Bonus Flasher (p)
  if (pd.pinState()->P12(1))
  {
    // trigger = 1;
  }

  // P12-2 10 Playfield Gen Illumination Relay (p)
  if (pd.pinState()->P12(2))
  {
    // trigger = 1;
  }

  // P12-4 11 Backglass Gen Illumination Relay (b)
  if (pd.pinState()->P12(4))
  {
    // trigger = 1;
  }

  // P12-6 13 Mystery Wheel (b) Coil B
  if (pd.pinState()->P12(6))
  {
    // trigger = 1;
  }

  // P12-7 14 Mystery Wheel (b) Coil A
  if (pd.pinState()->P12(7))
  {
    // trigger = 1;
  }

  // P12-8 Boomerang Flashers (p)
  if (pd.pinState()->P12(8))
  {
    // trigger = 1;
  }

  // P12-9 Ferris Wheel Motor/Relay (p)
  if (pd.pinState()->P12(9))
  {
    // trigger = 1;
  }

  // trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger)
  {
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.pinState()->reset();
    trigger = 0;
    attract_on = 0;
    timeLastEvent = millis();
  }
}

void attractMode()
{
  pd.adrLED1()->sparkle(attractColor, 20);
  pd.adrLED2()->sparkle(attractColor, 20);

  if (random(250) == 0)
  {
    if (attractColor == "green")
      attractColor = "red";
    else
      attractColor = "green";
  }
}