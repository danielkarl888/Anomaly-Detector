/*
 * Author: 318324563 - Daniel Meir Karl
 */
#include "CLI.h"

CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    commands.push_back(new PrintMenu(dio));
    commands.push_back(new UploadFileCSV(dio));
    commands.push_back(new ThresholdSettings(dio));
    commands.push_back(new Detect(dio));
    commands.push_back(new PrintAnomalies(dio));
    commands.push_back(new AnalyzeAnomalies(dio));
    commands.push_back(new Exit(dio));
}

void CLI::start() {
    bool flag = true;
    globalState global;
    while (flag) {
        commands.at(0)->execute(&global);
        string input = dio->read();
        int choice = input[0] - '0';
        if(choice == 6) {
            flag = false;
        }
        commands.at(choice)->execute(&global);
    }
}


CLI::~CLI() {
}

