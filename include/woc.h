#ifndef __WOC_H__
#define __WOC_H__

#include <string>

const std::string chain_info(const bool& testnet = true);
const std::string raw_transaction(const std::string&, const bool& testnet = true); 

const std::string balance(const std::string&, const bool& testnet = false); 
const std::string utxo(const std::string&, const bool& testnet = false);
#endif //#ifndef __WOC_H__
