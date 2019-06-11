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

std::set<std::string> printURLs(std::string text, std::ofstream& to) {
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
    return urls;
}

std::string refactorText(std::string text, std::set<std::string> urls) {
    std::locale loc("Lithuanian");

    for(auto url : urls) {
        text = std::regex_replace(text, std::regex("\\"+url), "");
    }

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

    std::set<std::string> urls = printURLs(text, result);

    result << "--------\n";

    text = refactorText(text, urls);

    std::map<std::string, std::vector<int>> words;
    std::set<std::string> wordCount;

    int last_index = 0, line = 0;
    std::string input;
    int length = 0;
    int x = 0;

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

    for(auto it = words.cbegin(); it != words.cend(); ++it){
        if(it->second.size() <= 1 || it->first == "\n" || it->first == " ")
            continue;

        length = 0;
        x = it->second.size();
        while (x /= 10)
            length++;
        std::string inser = std::string(4 - length, '0') + std::to_string(it->second.size());
        inser += "-";
        inser += it->first;
        wordCount.insert(inser);
//        std::cout << "Insert " << inser <<std::endl;
    }

    int maxsize = 0;
    int maxline = 0;


    for(auto fword : wordCount) {
        int count = std::stoi(fword.substr(0, fword.find("-")));
        std::string word = fword.substr(fword.find("-") + 1, fword.size() - fword.find("-") - 1);
        if(word.size() > maxsize) {
            maxsize = word.size();
        }
        if(words[word].back() > maxline) {
            maxline = words[word].back();
        }
    }

    for(int i = 0; i < 2; i++) {
        result << "| Zodis \\ Eilute" << std::string(std::max(maxsize + 6 - 15, 0), ' ') << " | ";

        for (int i = 1; i <= maxline; i++) {
            result << i << " | ";
        }
    }

    result << std::endl;
    for(int i = 0; i < 2; i++) {
        result << "|---------------" << std::string(std::max(maxsize + 6 - 15, 0), '-') << "-|-";

        for (int i = 1; i <= maxline; i++) {
            length = 0;
            x = i;
            while (x /= 10)
                length++;
            result << std::string(length, '-') << "--|-";
        }
    }

    result << std::endl;

    int linecount = 0;
    int index = 0;
    const int middle = wordCount.size() / 2 + 1;

    for(auto fword : wordCount){
        int count = std::stoi(fword.substr(0, fword.find("-")));
        std::string word = fword.substr(fword.find("-") + 1, fword.size() - fword.find("-") - 1);

//        std::cout << count << " < " << word << " < " << fword.find("-") << std::endl;

        // FIRST WORD IN ROW START
        if(index < middle) {
            length = 0;
            x = count;
            while (x /= 10)
                length++;
            result << "| " << word << " (" << count << ") "
                   << std::string(std::max((int) (maxsize - word.size()) - length, 0), ' ') << " | ";

            for (int i = 1; i <= maxline; i++) {
                linecount = 0;
                for (int j = 0; j < count; j++) {
//                    result << "[" << it->second[j] << " == " << i << "]";
                    if (words[word][j] == i) {
                        linecount++;
                    }
                }

                length = 0;
                x = i;
                while (x /= 10)
                    length++;

                if (linecount > 9) {
                    result << std::string(length, ' ') << "n | ";
                }
                if (linecount > 0) {
                    result << std::string(length, ' ') << linecount << " | ";
                } else {
                    result << std::string(length, ' ') << "  | ";
                }
            }
        }
        //FIRST WORD IN ROW END

        //SECOND WORD IN ROW START
        if(wordCount.size() > middle + index) {
            fword = *std::next(wordCount.begin(), middle + index);
            count = std::stoi(fword.substr(0, fword.find("-")));
            word = fword.substr(fword.find("-") + 1, fword.size() - fword.find("-") - 1);
            length = 0;
            x = count;
            while (x /= 10)
                length++;
            result << "| " << word << " (" << count << ") "
                   << std::string(std::max((int) (maxsize - word.size()) - length, 0), ' ') << " | ";

            for (int i = 1; i <= maxline; i++) {
                linecount = 0;
                for (int j = 0; j < count; j++) {
//                    result << "[" << it->second[j] << " == " << i << "]";
                    if (words[word][j] == i) {
                        linecount++;
                    }
                }

                length = 0;
                x = i;
                while (x /= 10)
                    length++;

                if (linecount > 9) {
                    result << std::string(length, ' ') << "n | ";
                }
                if (linecount > 0) {
                    result << std::string(length, ' ') << linecount << " | ";
                } else {
                    result << std::string(length, ' ') << "  | ";
                }
            }
        }
        //SECOND WORD IN ROW END
        result << std::endl;
        index++;
    }


    return 0;
}