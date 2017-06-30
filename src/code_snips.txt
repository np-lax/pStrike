ar tBuff[20];
    time_t currTime = time(NULL);
    strftime(tBuff, 20, "%Y-%m-%d", localtime(&currTime));  

    string start(tBuff);
    string end(tBuff);

    string baseURL = "https://api.nasa.gov/neo/rest/v1/feed?start_date="+
                     start + "&end_date=" + end + "&api_key=" + apiKey;

    const char* url = baseURL.c_str();

    CURL *curl;
    CURLcode res;
    std::string readBuffer; 

    curl = curl_easy_init();

    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
        else if(!readBuffer.empty()){
            cout << "GOT" << readBuffer << endl;
//          processNASAData(readBuffer);            
        }else{
            cout << "[ERROR]Got no data from NASA NeoWS....exiting";
            exit(0);
        }
    }


