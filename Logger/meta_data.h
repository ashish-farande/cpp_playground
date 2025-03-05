#ifndef C73D5097_30ED_44E3_AEB0_4426E6452DFC
#define C73D5097_30ED_44E3_AEB0_4426E6452DFC

#include <string_view>
#include <variant>
#include <vector>
#include <cstdint>
#include <utility>
#include <span>
#include <array>

#include "utils.h"
#include "TypeDescriptors.h"

struct MetaDataNode;

MetaDataNode *&head_node()
{
    static MetaDataNode *head{nullptr};
    return head;
}

struct MetaData
{
    std::string_view file{};
    std::string_view function{};
    std::string_view fmt_str{};
    int64_t line{};
    Level level;
};

struct MetaDataWithDescriptors
{
    MetaData macroData;
    TypeDescriptors desciprtors;
};

struct MetaDataNode
{
    constexpr MetaDataNode(const MetaDataWithDescriptors *d) : id(gen_id()), data(d)
    {
        auto &head = head_node();
        next = std::exchange(head, this);
    }

    int64_t id;
    const MetaDataWithDescriptors *data{nullptr};
    MetaDataNode *next{nullptr};
};

template <class MetaData_, class... Args>
constexpr auto get_meta_data_ptr()
{
    static constexpr std::array type_descriptors{GetTypeDescriptor<Args>::value...};
    static constexpr MetaDataWithDescriptors meta_data{MetaData_{}(), Span{type_descriptors}};
    return &meta_data;
}

template <class F, class... Args>
inline MetaDataNode meta_data_node{get_meta_data_ptr<F, Args...>()};

#endif /* C73D5097_30ED_44E3_AEB0_4426E6452DFC */
