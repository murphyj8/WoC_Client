#include <iostream>
#include <include/woc.h>

int main(int argc, char * argv[]){
    std::cout << "Running" << std::endl; 
    //if (argc != 3)
    //{
        //printf("Usage: WoC_Client.exe search_term output_file\n");
    //    std::cout << "Usage: WoC_Client chain_info output_file" << std::endl; 
    //    return -1;
    //}

    //const utility::string_t searchTerm = argv[1];
    //const utility::string_t outputFileName = argv[2];

    //std:: cout << get_json_response("/chain/info").serialize() << std::endl; 

    std::cout << chain_info(true) << std::endl;

    //std::cout << raw_transaction("43f24d216f1d991b9ad090ea9b52a97e63c18f6378e7e6de106ea4aefa7191b4", true) << std::endl;

    std::cout << raw_transaction("2f29a4475ef70e47b68c03473f5abee4e3fed4ccafcdca548d53a033ac08e4d1", true) << std::endl; 
    std::cout << balance("mwxrVFsJps3sxz5A38Mbrze8kPKq7D5NxF", true) << std::endl;

    std::cout << utxo("mwxrVFsJps3sxz5A38Mbrze8kPKq7D5NxF", true) << std::endl;
    return 0;
}