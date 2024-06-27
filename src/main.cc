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

    std::cout << chain_info() << std::endl;
    return 0;
}