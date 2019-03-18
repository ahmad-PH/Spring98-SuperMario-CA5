#ifndef ASSETSADDRESSLOOKUP_H
#define ASSETSADDRESSLOOKUP_H

#include <string>
#include <map>

class AssetsAddressLookup {
public:
    AssetsAddressLookup(std::string root_folder);
    std::string get(std::string asset_name);

private:
    std::string root_folder;
    std::map<std::string, std::string> lookup_table;
};


#endif
