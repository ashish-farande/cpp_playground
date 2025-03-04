#ifndef C194F1CA_69EB_45E7_947E_6D8A582B3B82
#define C194F1CA_69EB_45E7_947E_6D8A582B3B82

#include <fstream>
#include <array>

#include "meta_data.h"
#include "utils.h"

template <typename T>
void writeToFile(std::ofstream &file, const T &arg)
{
    file << arg;
}

template <typename T, typename... Args>
void writeToFile(std::ofstream &file, const T &arg, const Args &...args)
{
    writeToFile(file, arg);
    writeToFile(file, args...);
}

template <class F, class... Args>
void log(Args const &...args)
{
    std::ofstream file_out("data.txt", std::ios::app);
    file_out << "\n";
    file_out << meta_data_node<F, Args...>.id;
    writeToFile(file_out, args...);
    file_out.close();
}

struct LogInitializer {
    LogInitializer() {
        int size = 0;
        std::ofstream file("metadata.txt");
        auto& temp = head_node();

        while(temp != nullptr)
        {
            ++size;
            file << temp->id << " " << temp->data << "\n";
            temp = temp->next;
        }
        std::cout<<"Total Number of nodes: "<<size<<"\n";

    }
};

#endif /* C194F1CA_69EB_45E7_947E_6D8A582B3B82 */
