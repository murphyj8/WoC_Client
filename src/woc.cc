#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <include/woc.h>


const std::string get_url(const bool& testnet){
    if(testnet){
        return std::string("https://api.whatsonchain.com/v1/bsv/test"); 
    } else {
        return std::string("https://api.whatsonchain.com/v1/bsv/main");
    }
}
web::http::client::http_client_config client_config_for_proxy()
{
    web::http::client::http_client_config client_config;
    if (const char* env_http_proxy = std::getenv("http_proxy"))
    {
        std::string env_http_proxy_string(env_http_proxy);
        if (env_http_proxy_string == U("auto"))
            client_config.set_proxy(web::web_proxy::use_auto_discovery);
        else
            client_config.set_proxy(web::web_proxy(env_http_proxy_string));
    }

    return client_config;
}

web::json::value get_json_response (const std::string& cmd, const bool& testnet=false){
    web::json::value json_response; 
    try{
        // Create an HTTP client

        //web::http::client::http_client client(U("https://api.whatsonchain.com/v1/bsv/test"), client_config_for_proxy());
        web::http::client::http_client client(get_url(testnet), client_config_for_proxy());
        // Perform a GET request
        client.request(web::http::methods::GET, cmd)
        .then([](web::http::http_response response) -> pplx::task<web::json::value>
        {
            if (response.status_code() == web::http::status_codes::OK){
                return response.extract_json();
            }
            // Handle error case
            return pplx::task_from_result(web::json::value());
        })
        .then([&json_response](pplx::task<web::json::value> previousTask)
        {
            try{
                // Get the JSON value from the task
                json_response = previousTask.get();
            }
            catch (const web::http::http_exception& e){
                std::wcout << L"HTTP Exception: " << e.what() << std::endl;
            }
        })
        .wait(); // Wait for all tasks to complete
    }
    catch (const std::exception &e){
        std::wcout << L"Exception: " << e.what() << std::endl;
    }
    return json_response; 
}

void file_buffer_json(const std::string& query, const std::string& outputFileName){
    auto fileBuffer = std::make_shared<concurrency::streams::streambuf<uint8_t>>();
    concurrency::streams::file_buffer<uint8_t>::open(outputFileName, std::ios::out)
        .then([=](concurrency::streams::streambuf<uint8_t> outFile) -> pplx::task<web::http::http_response> {
            *fileBuffer = outFile;

            // Create an HTTP request.
            // Encode the URI query since it could contain special characters like spaces.
            web::http::client::http_client client(U("https://api.whatsonchain.com/v1/bsv/test"), client_config_for_proxy());
            //return client.request(web::http::methods::GET, web::http::uri_builder(U("/chain/info")).append_query(U("q"), searchTerm).to_string());
            return client.request(web::http::methods::GET, web::http::uri_builder(U("/chain/info")).to_string());
        })

        // Write the response body into the file buffer.
        .then([=](web::http::http_response response) -> pplx::task<size_t> {
            //printf("Response status code %u returned.\n", response.status_code());
            std::cout << "Response status code " << response.status_code() << std::endl;
            return response.body().read_to_end(*fileBuffer);
        })

        // Close the file buffer.
        .then([=](size_t) { return fileBuffer->close(); })

        // Wait for the entire response body to be written into the file.
        .wait();
}


const std::string chain_info(const bool& testnet){
    const std::string& info = get_json_response("chain/info").serialize(); 
    return info; 
}