#ifndef METEOPLOTS_H

#define METEOPLOTS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "TGraph.h"

struct entries
{
  std::string date;
  int hour;
  int minute;
  int second;
  std::string dayTime;
  std::vector< std::pair< int, double > > temperatures; 
  std::vector< std:: pair < int, double > > humidities;
  std::pair < double, std::string > atmPressure;
  std::pair < double, std::string > valve1Pressure;
  std::pair < double, std::string > valve2Pressure;
};

class meteoPlots
{
public:
  meteoPlots( std::string filename );
  std::vector<TGraph> plot();
  bool savePlots( std::string outName );
private:
  bool checkFile();
  bool readFile();
  std::string fFileName;
  std::vector< entries > fEntries;
};
#endif //METEOPLOTS_H
