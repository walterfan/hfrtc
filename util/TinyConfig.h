/*
 * TinyConfig.h
 *
 *  Created on: Jul 4, 2016
 *      Author: walter
 */

#ifndef UTIL_TINYCONFIG_H_
#define UTIL_TINYCONFIG_H_

namespace wfan {

struct ConfigItemKey {
    std::string groupName;
    std::string itemName;
};

struct KeyComparable {
    bool operator()(ConfigItemKey item1, ConfigItemKey item2) const
    {
        int ret = item1.groupName.compare(item2.groupName) ;
        if(ret == 0) {
           return item1.itemName.compare(item2.itemName);
        }
        return ret;
    }
};

typedef map<ConfigItemKey, std::string, KeyComparable> ConfigItemMap;

class TinyConfig {
public:
    TinyConfig();
    virtual ~TinyConfig();

    void addConfigItem(ConfigItemKey key, std::string val);
    std::string& getConfigItem(ConfigItemKey key);
private:
    ConfigItemMap configItemMap;
};

} /* namespace wfan */

#endif /* UTIL_TINYCONFIG_H_ */
