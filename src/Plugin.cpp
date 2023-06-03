/*
This file is part of Media Keys Fix SKSE.

Foobar is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/

#include "Main.h"

using namespace SKSE;
using namespace SKSE::log;
using namespace SKSE::stl;

namespace mdkf {
    void initializeLogging() {
        auto path = log_directory();
        if (!path) {
            report_and_fail("Can't find SKSE log directory");
        }
        *path /= fmt::format("{}.log"sv, PluginDeclaration::GetSingleton()->GetName());

        std::shared_ptr<spdlog::logger> log;
        if (IsDebuggerPresent()) {
            log = std::make_shared<spdlog::logger>("Global", std::make_shared<spdlog::sinks::msvc_sink_mt>());
        } else {
            log = std::make_shared<spdlog::logger>("Global",
                                                   std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true));
        }
        log->set_level(spdlog::level::info);
        log->flush_on(spdlog::level::info);

        spdlog::set_default_logger(std::move(log));
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [%t] %v");
    }
}  // namespace mdkf

using namespace mdkf;

SKSEPluginLoad(const LoadInterface* skse) {
    initializeLogging();
    const auto* plugin = PluginDeclaration::GetSingleton();
    auto version = plugin->GetVersion();

    logger::info("'{} {}' is loading, game version '{}'...", plugin->GetName(), version, REL::Module::get().version());
    Init(skse);

    load();

    logger::info("{} has finished loading.", plugin->GetName());
    return true;
}
