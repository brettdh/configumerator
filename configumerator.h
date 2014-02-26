#ifndef CONFIG_H_INCL_HGV0YDGSUOAH08FH93U2HBIRVSFB
#define CONFIG_H_INCL_HGV0YDGSUOAH08FH93U2HBIRVSFB

#include <string>
#include <set>
#include <map>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits>

namespace configumerator {
    class ConfigValidationError : public std::runtime_error {
      public:
        ConfigValidationError(const std::string& msg) : std::runtime_error(msg) {}
    };

    class Config {
        // subclass must define public accessors
    private:
        std::set<std::string> boolean_option_keys;
        std::set<std::string> string_option_keys;
        std::set<std::string> double_option_keys;
        std::set<std::string> doubles_list_option_keys;

        std::map<std::string, bool> boolean_options;
        std::map<std::string, std::string> string_options;
        std::map<std::string, double> double_options;
        std::map<std::string, std::vector<double> > doubles_list_options;

        std::map<std::string, std::set<std::string> > string_option_constraints;

        void readFile(const std::string& filename);

        void readBooleanOption(const std::string& line, const std::string& key);
        void readStringOption(const std::string& line, const std::string& key);
        void readDoubleOption(const std::string& line, const std::string& key);

        void readDoublesListOption(const std::string& line, const std::string& key);

        std::vector<std::pair<std::function<void(const std::string&, const std::string&)>, std::set<std::string>* > > readers;
    protected:
        bool getBoolean(const std::string& key);

        bool hasString(const std::string& key);
        std::string getString(const std::string& key);
    
        bool hasDouble(const std::string& key);
        double getDouble(const std::string& key);

        bool hasDoublesList(const std::string& key);
        std::vector<double> getDoublesList(const std::string& key);
    
        Config();
        void loadConfig(const std::string& filename);
        virtual void setup() {}
        virtual void validate() {}

        void registerOptionReader(std::function<void(const std::string&, const std::string&)> reader, 
                                  std::set<std::string> *keys);
        void registerBooleanOption(const std::string& key, bool default_value=false);
        void registerStringOption(const std::string& key, const std::string& default_value="", 
                                  const std::set<std::string>& constraints=std::set<std::string>());
        void registerDoubleOption(const std::string& key, double default_value=std::numeric_limits<double>::quiet_NaN());

        void registerDoublesListOption(const std::string& key, 
                                       std::vector<double> default_value=std::vector<double>());
        
        void checkStringConstraints(const std::string& key, const std::string& value);
    };
}
#endif
