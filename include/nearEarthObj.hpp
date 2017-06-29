#ifndef __NEAREARTHOBJ_HPP__
#define __NEAREARTHOBJ_HPP__

#include <string>


class nearEarthObj{
	private:
		std::string objName;
		unsigned int objRefID;
		std::string objJPLURL;		//link to obj-specific JPL page
		double objMinDiameter;		//in meters
		double objMaxDiameter;		//in meters
		bool objDanger;			//true if labeled dangerous
		std::string objCloseApprDate;	//in YYYY-MM-DD format
		double objRelativeVelocity;	//in KM per second
		std::string objOrbitingBody;	//body the obj is orbiting
		unsigned int objMissDistance;	//distance in meters
		const int objReadLines = 35;	//#of lines in each JPL object
	
	public:
		void createNEO(std::string objName, unsigned int objRefID);
		std::string getObjName(unsigned int objRefID);
			
}

#endif
