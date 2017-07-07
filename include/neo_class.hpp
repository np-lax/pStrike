#ifndef __NEAREARTHOBJ_HPP__
#define __NEAREARTHOBJ_HPP__

#include <string>

class Near_earth_object{
 public:
  Near_earth_object(int ref_id, 
                  std::string name,
                  double max_diameter,
                  double min_diameter,
                  bool hazardous,
                  std::string close_approach_date,
                  double approach_velocity,
                  int miss_distance); //constructor

  //accessors
  int get_ref_id() const;
  std::string get_name();
  double get_size();
  bool get_status();
  std::string get_app_date();
  double get_speed();
  int get_miss_distance();

    
  private:
   int ref_id;
   std::string name;
   double max_diameter;            //in meters
   double min_diameter;
   bool is_hazardous;              //true if hazardous
   std::string close_approach_date;
   double approach_velocity;       //in km/h
   int miss_distance;              //in km
};




#endif
