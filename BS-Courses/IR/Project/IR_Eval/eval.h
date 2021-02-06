#include <string>
#include <vector>
#include <boost\unordered\unordered_map.hpp>

class eval{

	std::string cluster_name,class_name;
	double RI,Purity;
	boost::unordered_map<int,std::vector<std::string> > clusters;
	boost::unordered_map< std::string ,int> clusters_list;


public:
	eval(std::string Pcluster_name,std::string Pclass_name);
	virtual ~eval();
	void Run();
};