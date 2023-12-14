#include <utilities/utilities.h>

std::shared_ptr<spdlog::logger> Utilities::console_logger() {
    static auto logger = create_console_logger();
    return logger;
}

std::shared_ptr<spdlog::logger> Utilities::file_logger(const std::string& filename) {
    static auto logger = create_file_logger(filename);
    return logger;
}

std::shared_ptr<spdlog::logger> Utilities::combined_logger(const std::string& filename) {
    static std::shared_ptr<spdlog::logger> logger;
    if (!logger) {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true);
        logger = std::make_shared<spdlog::logger>("combined_logger", spdlog::sinks_init_list{console_sink, file_sink});
        spdlog::register_logger(logger);
    }
    return logger;
}

std::shared_ptr<spdlog::logger> Utilities::create_console_logger() {
    auto logger = spdlog::stdout_color_mt("console_logger");
    return logger;
}

std::shared_ptr<spdlog::logger> Utilities::create_file_logger(const std::string& filename) {
    auto logger = spdlog::basic_logger_mt("file_logger", filename);
    return logger;
}