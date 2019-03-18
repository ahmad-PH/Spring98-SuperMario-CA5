#include "AssetsAddressLookup.h"

using namespace std;

AssetsAddressLookup::AssetsAddressLookup(string root_folder) {
    this->root_folder = root_folder;
    lookup_table["bg_img"] = root_folder + "/background_image.png";
}

std::string AssetsAddressLookup::get(std::string asset_name) {
    return lookup_table[asset_name];
}