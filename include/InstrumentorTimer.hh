#pragma once
// reference: https://github.com/GavinSun0921/InstrumentorTimer.git
// and TheCherno: https://gist.github.com/TheCherno/31f135eea6ee729ab5f26a6908eb3a5e

#define USE_PROFILING 1
#if USE_PROFILING
#define EXPAND_CONCAT(x, y) x##y
#define CONCAT(x, y) EXPAND_CONCAT(x, y)
#define PROFILE_WITH_NAME(name) InstrumentorTimer CONCAT(timer, __LINE__)(name)
#ifdef _MSC_VER
#define PROFILE_SCOPE() PROFILE_WITH_NAME(__FUNCSIG__)
#else
#define PROFILE_SCOPE() PROFILE_WITH_NAME(__PRETTY_FUNCTION__)
#define PROFILE_BEGIN() { PROFILE_WITH_NAME(__PRETTY_FUNCTION__)
#define PROFILE_END() }
#endif
#else
#define PROFILE_WITH_NAME(name)
#define PROFILE_SCOPE()
#define PROFILE_BEGIN()
#define PROFILE_END()
#endif

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

struct ProfileResult {
    std::string Name;       // profile name.
    long long   Start, End; // profile start, end time_point.
    uint64_t    ThreadID;   // profile for thread index.
};

class Instrumentor {
  private:
    std::string   m_SessionName;   // current session name
    std::ofstream m_OutputStream;  // file stream
    int           m_ProfileCount;  //
    std::mutex    m_Lock;          // for thread safety.
    bool          m_ActiveSession; // whether this session is actived.

  public:
    ~Instrumentor() {
        EndSession();
    }

    Instrumentor(const Instrumentor&) = delete;

    static void BeginSession(const std::string& name, const std::string& filepath = "Results.json") {
        GetInstance().BeginSessionImpl(name, filepath);
    }

    static void EndSession() {
        GetInstance().EndSessionImpl();
    }

    static void WriteProfile(const ProfileResult& result) {
        GetInstance().WriteProfileImlp(result);
    }

  private:
    Instrumentor()
        : m_SessionName("None")
        , m_ProfileCount(0)
        , m_ActiveSession(false) {
        ;
    }

    static Instrumentor& GetInstance() {
        static Instrumentor instance;
        return instance;
    }

    void BeginSessionImpl(const std::string& name, const std::string& filepath = "Results.json") {
        if (m_ActiveSession) {
            EndSession();
        }
        m_ActiveSession = true;
        m_SessionName   = name;

        m_OutputStream.open(m_SessionName + std::string("_") + filepath);
        WriteHeader();
    }

    void EndSessionImpl() {
        if (!m_ActiveSession) {
            return;
        }
        m_ActiveSession = false;
        m_ProfileCount  = 0;

        WriteFooter();
        m_OutputStream.close();
    }

    void WriteHeader() {
        m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        m_OutputStream.flush();
    }

    void WriteFooter() {
        m_OutputStream << "]}";
        m_OutputStream.flush();
    }

    void WriteProfileImlp(const ProfileResult& result) {
        std::lock_guard<std::mutex> lockGuard(m_Lock);

        if (m_ProfileCount++ > 0)
            m_OutputStream << ",";

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        // write a item.
        m_OutputStream << "{";
        m_OutputStream << "\"cat\":\"function\",";
        m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
        m_OutputStream << "\"name\":\"" << name << "\",";
        m_OutputStream << "\"ph\":\"X\",";
        m_OutputStream << "\"pid\":\"" << m_SessionName << "\",";
        m_OutputStream << "\"tid\":" << result.ThreadID << ",";
        m_OutputStream << "\"ts\":" << result.Start;
        m_OutputStream << "}";

        m_OutputStream.flush();
    }
};

class InstrumentorTimer {
    using inc_time_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

  private:
    const char* m_Name;
    inc_time_t  m_StartTimePoint;
    bool        m_Stoped;

  public:
    InstrumentorTimer() = default;

    // start when constructed.
    InstrumentorTimer(const char* name)
        : m_Name(name)
        , m_Stoped(false) {
        m_StartTimePoint = std::chrono::high_resolution_clock::now();
    }

    // stop when termiate.
    ~InstrumentorTimer() {
        if (!m_Stoped) {
            Stop();
        }
    }

    //  Generate Sington instance.
    static InstrumentorTimer& Get() {
        static InstrumentorTimer instance;
        return instance;
    }

    void Stop() {
        auto      endTimepoint = std::chrono::high_resolution_clock::now();
        long long start        = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
        long long end          = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        // get the id of thread.
        uint64_t threadIDx = std::hash<std::thread::id>{}(std::this_thread::get_id());

        Instrumentor::WriteProfile({m_Name, start, end, threadIDx});

        m_Stoped = true;
    }
};
