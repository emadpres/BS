#include <string>
#include <vector>
#include <map>

class eval{
        double *mRI,*mPurity;
	std::string cluster_name,class_name;
	double RI,Purity;
        std::map<int,std::vector<std::string> > clusters;
        std::map< std::string ,int> clusters_list;


public:
        eval(std::string Pcluster_name,std::string Pclass_name,double* pRI, double* pPurity);
	virtual ~eval();
	void Run();
};
