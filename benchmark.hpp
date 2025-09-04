#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <ctime>
#include <string>
#include <map>
#include <fstream>
#include <iomanip>

struct benchmarkTask
{
    int      taskID = -1;
    std::string name;
    clock_t  start = 0;
    clock_t  end   = 0;

    benchmarkTask() = default;
    benchmarkTask(int id, const std::string& n) : taskID(id), name(n) {}

    void startTask() { start = clock(); }
    void endTask()   { end   = clock(); }

    double getDurationMs() const {
        return 1000.0 * static_cast<double>(end - start) / CLOCKS_PER_SEC;
    }
};

// Inline globals so this header can be included in multiple translation units
inline int current_task_id = -1;
inline std::map<int, benchmarkTask> tasks;
inline std::string current_area = "task_id=-1";
inline clock_t benchmark_start_clock = 0;

inline void initBenchmark()
{
    // reset state for a fresh run
    current_task_id = -1;
    tasks.clear();
    current_area = "task_id=-1";
    benchmark_start_clock = clock();
}

inline void startArea(const std::string& name_area = "")
{
    current_task_id += 1;

    if (!name_area.empty()) {
        current_area = name_area + " (task_id=" + std::to_string(current_task_id) + ")";
    } else {
        current_area = "task_id=" + std::to_string(current_task_id);
    }

    // create/overwrite the task entry and start timing
    tasks[current_task_id] = benchmarkTask(current_task_id, current_area);
    tasks[current_task_id].startTask();
}

inline void closeArea()
{
    // End the currently active task, if any
    auto it = tasks.find(current_task_id);
    if (it != tasks.end()) {
        it->second.endTask();
    }
}

inline void endBenchmark(const std::string& file_name)
{
    // If the last area wasn't closed, close it now
    auto it = tasks.find(current_task_id);
    if (it != tasks.end() && it->second.end == 0) {
        it->second.endTask();
    }

    std::ofstream out(file_name);
    if (!out) return;

    out << "task_id,name,start_ticks,end_ticks,duration_ms\n";
    for (const auto& [id, t] : tasks) {
        out << id << ','
            << '"' << t.name << '"' << ','
            << t.start << ','
            << t.end << ','
            << std::fixed << std::setprecision(3) << t.getDurationMs() << '\n';
    }
}

#endif // BENCHMARK_HPP
