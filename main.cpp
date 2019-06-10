//
// Created by Nerijus on 2019-05-29.
//

#include "main.h"

std::string loadFile() {
    std::string file;
    try {
        std::ifstream inf("text.txt");

        if (inf.fail() || inf.bad() || !inf.is_open()) {
            throw std::runtime_error("Can not load file.");
        }

        std::string line;

        while (getline(inf, line)){
            file += " \n " + line;
        }
    } catch (std::exception& e) {
        std::cout << "Klaida ikeliant failus is text.txt. Galbut failas neegzistuoja? " << e.what();
    }
    return file;
}

void printURLs(std::string text, std::ofstream& to) {
    std::string word;
    std::set<std::string> urls;
    std::istringstream iss(text);

    while (iss >> word){
        if(std::regex_match(word, std::regex("[(http(s)?):\\/\\/(www\\.)?a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)")) )
        {
            urls.insert(word);
        }
    }

    to << "Rasti URL: " << std::endl;
    for (auto url : urls) {
        to << url << std::endl;
    }
}

std::string refactorText(std::string text) {
    std::locale loc("Lithuanian");

    for (int i = 0, len = text.size(); i < len; i++)
    {
        if (ispunct(text[i], loc) || isdigit(text[i], loc))
        {
            text.erase(i--, 1);
            len = text.size();
        }

        text[i] = std::tolower(text[i], loc);
    }

    return text;
}

int main() {
    std::ofstream result("result.txt");

    std::string text = loadFile();

    printURLs(text, result);

    result << "--------\n";

    text = refactorText(text);

    std::map<std::string, std::vector<int>> words;

    int last_index = 0, line = 0;
    std::string input;
    for(int i = 0; i < text.size(); i++){
        if(text[i] == '\n'){
            line++;
            continue;
        }
        if(text[i] == ' '){
            input = text.substr(last_index + 1, std::max(i - last_index - 1, 1));
            last_index = i;
            if(input != "\n")
                words[input].push_back(line);
        }
    }


    int maxsize = 0;
    int maxline = 0;
    int length = 0;
    int x = 0;

    for(auto it = words.cbegin(); it != words.cend(); ++it){
        if(it->second.size() >= 2){
            if(it->first.size() > maxsize) {
                maxsize = it->first.size();
            }
            if(it->second.back() > maxline) {
                maxline = it->second.back();
            }
        }
    }

    result << "| Zodis \\ Eilute" << std::string(std::max(maxsize + 6 - 15, 0), ' ') << " | ";

    for(int i = 1; i <= maxline; i++){
        result << i << " | ";
    }

    result << std::endl;
    result << "|---------------" << std::string(std::max(maxsize + 6 - 15, 0), '-') << "-|-";

    for(int i = 1; i <= maxline; i++){
        length = 0;
        x = i;
        while ( x /= 10 )
            length++;
        result << std::string(length, '-') <<"--|-";
    }

    result << std::endl;

    int linecount = 0;

    for(auto it = words.cbegin(); it != words.cend(); ++it){
        if(it->second.size() >= 2){
            length = 0;
            x = it->second.size();
            while ( x /= 10 )
                length++;
            result << "| " << it->first << " (" << it->second.size() << ") "  << std::string(std::max((int)(maxsize - it->first.size()) - length, 0), ' ') << " | ";

            for(int i = 1; i <= maxline; i++) {
                linecount = 0;
                for(int j = 0; j < it->second.size(); j++){
//                    result << "[" << it->second[j] << " == " << i << "]";
                    if(it->second[j] == i){
                        linecount++;
                    }
                }

                length = 0;
                x = i;
                while ( x /= 10 )
                    length++;

                if(linecount > 9) {
                    result << std::string(length, ' ') << "n | ";
                } if(linecount > 0){
                    result << std::string(length, ' ') << linecount << " | ";
                } else {
                    result << std::string(length, ' ') << "  | ";
                }
            }
            result << std::endl;
        }
    }


    return 0;
}