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
    
    
    ssEntry.str( (std::string() ) );
  }
  
  
  file.close();
  return true;
}

std::vector< TGraph > meteoPlots::plot()
{
  std::vector< TGraph > graphs;
  
  return graphs;
}

bool meteoPlots::savePlots(std::string outName)
{

  return true;
}

