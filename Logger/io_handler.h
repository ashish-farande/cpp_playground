#ifndef C194F1CA_69EB_45E7_947E_6D8A582B3B82
#define C194F1CA_69EB_45E7_947E_6D8A582B3B82

#include <fstream>
#include <array>

#include "meta_data.h"
#include "utils.h"

template <typename T>
void writeToFile(std::ofstream &file, const T &arg)
{
    file << arg << " ";
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
    std::ofstream file_out("log.txt", std::ios::app);
    file_out << "\n";
    file_out << meta_data_node<F, Args...>.id << " ";
    writeToFile(file_out, args...);
    file_out.close();
}

struct LogInitializer
{
    LogInitializer()
    {
        std::ofstream logfile("log.txt", std::ios::out | std::ios::trunc);
        if (logfile.is_open())
            logfile.close();

        int size = 0;
        std::ofstream file("metadata.txt");
        auto &temp = head_node();

        while (temp != nullptr)
        {
            ++size;
            file << temp->id << " | " << (int)temp->data->macroData.level << " | " << temp->data->macroData.file << " | " << temp->data->macroData.line << " | " << temp->data->macroData.function << " | " << temp->data->macroData.fmt_str << " | ";
            for (const auto &desc : temp->data->desciprtors)
            {
                if (std::get_if<Int>(&desc))
                {
                    file << "int ";
                }
                else if (std::get_if<Float>(&desc))
                {
                    file << "float ";
                }
                else if (std::get_if<CStr>(&desc))
                {
                    file << "char* ";
                }
            }

            file << "\n";
            temp = temp->next;
        }
        std::cout << "Total Number of nodes: " << size << "\n";
    }
};

#endif /* C194F1CA_69EB_45E7_947E_6D8A582B3B82 */
