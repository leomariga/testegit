#include <Wire.h>
#include <MS5611.h>

MS5611 ms5611;

double referencePressure;

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  //Inicia e calibra o módulo MS5611
  setupMS5611();
  calibrateMS5611();
  
  // Aguarda a resposta do sensor
  delay(1500); 
}

void loop()
{

  // Read raw values
  uint32_t rawTemp = ms5611.readRawTemperature();
  uint32_t rawPressure = ms5611.readRawPressure();

  // Read true temperature & Pressure
  double realTemperature = ms5611.readTemperature();
  long realPressure = ms5611.readPressure();

  // Calculate altitude
  float absoluteAltitude = ms5611.getAltitude(realPressure);
  float relativeAltitude = ms5611.getAltitude(realPressure, referencePressure);
  
  Serial.println(relativeAltitude);

}

void setupMS5611()
{
  ms5611.begin();
}

void calibrateMS5611()
{
	// Get reference pressure for relative altitude
	referencePressure = ms5611.readPressure();

}


