#ifndef __NEAREARTHOBJ_HPP__
#define __NEAREARTHOBJ_HPP__

#include <string>

class near_earth_object{
    public:
        near_earth_object(int ref_id, 
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
        double get_avg_diameter() const;
        bool hazardous() const;
        std::string get_close_approach_date() const;
        double get_approach_velocity() const;
        int get_miss_distance() const;

    
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
