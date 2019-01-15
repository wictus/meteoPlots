#include "meteoPlots.h"

meteoPlots::meteoPlots( std::string filename ) : 
fFileName( filename )
{
  if ( !checkFile() )
  {
    std::cout << "Wrong path to file: " << fFileName << std::endl;
    std::exit(1);
  }
  
  if( !readFile() )
  {
    std::cout << "Cannot read from file: " << fFileName << std::endl;
    std::exit(2);
  }
}

bool meteoPlots::checkFile()
{
  if (FILE *file = fopen(fFileName.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

bool meteoPlots::readFile()
{
  std::ifstream file;
  file.open( fFileName.c_str() );
  std::stringstream ssEntry;
  std::string sEntry = "";
  while( std::getline( file, sEntry ) )
  {
    ssEntry << sEntry;

    entries singleEntry;
    //read date
    ssEntry >> singleEntry.date;
    
    //read time
    std::string tempTime = "";
    ssEntry >> tempTime;
    singleEntry.hour = atoi( (tempTime.substr(0, tempTime.find(":") ) ).c_str() );
    singleEntry.minute = atoi( (tempTime.substr(tempTime.find_first_of(":")+1, 2 )).c_str() );
    singleEntry.second = atoi( (tempTime.substr(tempTime.find_last_of(":")+1, 2 )).c_str() );
    ssEntry >> singleEntry.dayTime;
    singleEntry.dayTime = singleEntry.dayTime.substr(0,2); // to cut out ">" sign
    
    std::cout <<singleEntry.dayTime  << std::endl;
    
    for(int tProbe = 0; tProbe < 10; tProbe++)
    {
      std::string sProbe, sValue;
      ssEntry >> sProbe >> sValue;
      sValue = sValue.substr(0, sValue.find(";"));
      singleEntry.temperatures.push_back( std::make_pair<>(tProbe, atof( sValue.c_str() ) ) );
    }

    for(int hProbe = 0; hProbe < 2; hProbe++)
    {
      std::string sProbe, sValue;
      ssEntry >> sProbe >> sValue;
      sValue = sValue.substr(0, sValue.find(";"));
      singleEntry.humidities.push_back( std::make_pair<>(hProbe, atof( sValue.c_str() ) ) );
    }
    
    std::string tempPressure = "", tempUnits = "";
    ssEntry >> tempPressure; // reads a label "P:"
    ssEntry >> tempPressure; // reads a value
    ssEntry >> tempUnits ; // reads units
    tempUnits = tempUnits.substr(0, tempUnits.find(";"));
    
    singleEntry.atmPressure = std::make_pair<>( atof(tempPressure.c_str()), tempUnits );
    
    ssEntry >> tempPressure; // reads a label "P1:"
    ssEntry >> tempPressure; // reads a value
    ssEntry >> tempUnits ; // reads units
    tempUnits = tempUnits.substr(0, tempUnits.find(";"));
    
    singleEntry.valve1Pressure = std::make_pair<>( atof(tempPressure.c_str()), tempUnits );
    
    ssEntry >> tempPressure; // reads a label "P2:"
    ssEntry >> tempPressure; // reads a value
    ssEntry >> tempUnits ; // reads units
    tempUnits = tempUnits.substr(0, tempUnits.find(";"));
    
    singleEntry.valve2Pressure = std::make_pair<>( atof(tempPressure.c_str()), tempUnits );
    
    fEntries.push_back( singleEntry );
    
    ssEntry.str( (std::string() ) );
  }
  
  
  file.close();
  return true;
}

std::vector< TGraph > meteoPlots::plot()
{
  std::vector< TGraph > graphs;
  std::vector< double > xPoints, t0Points;
  for(int entry = 0; entry < fEntries.size(); entry++)
  {
    xPoints.push_back( entry );
    t0Points.push_back( fEntries[ entry ].temperatures[0].second );
    std::cout << entry << "\t" << fEntries[ entry ].temperatures[0].second << std::endl;
  }
  
  TGraph t0(xPoints.size(), &xPoints[0], &t0Points[0] );
  
  
  graphs.push_back( t0 );
  
  fGraphs = graphs;
  return graphs;
}

bool meteoPlots::savePlots(std::string outName)
{
  fGraphs[0].GetXaxis()->SetTitle("Date [a.u]");
  fGraphs[0].GetYaxis()->SetTitle("Temperature [C]");
  fGraphs[0].Draw("AP");
  fGraphs[0].SetMarkerStyle(21);
  fGraphs[0].SaveAs(outName.c_str());
  return true;
}

