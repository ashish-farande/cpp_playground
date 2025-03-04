#ifndef AB9C9A9D_9BE3_4737_93A3_14DFC24827EC
#define AB9C9A9D_9BE3_4737_93A3_14DFC24827EC

#include <string_view>

#include "meta_data.h"
#include "utils.h"
#include "io_handler.h"

#define LOG_ERROR(format, ...) LOG(Level::kError, format, __VA_ARGS__)
#define LOG_WARN(format, ...) LOG(Level::kWarn, format, __VA_ARGS__)
#define LOG_INFO(format, ...) LOG(Level::kInfo, format, __VA_ARGS__)
#define LOG_DEBUG(format, ...) LOG(Level::kDebug, format, __VA_ARGS__)

#define LOG(level, format, ...)                                           \
    do                                                                    \
    {                                                                     \
        static constexpr std::string_view func{__FUNCTION__};             \
        struct                                                            \
        {                                                                 \
            constexpr MetaData operator()() const noexcept                \
            {                                                             \
                return MetaData(__FILE__, func, format, __LINE__, level); \
            }                                                             \
        } anonym_meta_data;                                               \
        log<decltype(anonym_meta_data)>(__VA_ARGS__);                     \
    } while (false)


#endif /* AB9C9A9D_9BE3_4737_93A3_14DFC24827EC */
