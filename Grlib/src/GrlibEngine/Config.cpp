#include "GrlibEngine/Config.h" 

Config::Config() {
    std::stringstream ss; 
    cereal::BinaryOutputArchive oarchive(ss); 
    oarchive(*this); 
}

Config::~Config() {
    save();
}

void Config::save() {
    std::stringstream ss;
    cereal::BinaryInputArchive iarchive(ss);
    iarchive(*this);
}