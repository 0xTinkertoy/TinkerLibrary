//
//  Experiments.hpp
//  TinkerLibrary
//
//  Created by FireWolf on 2020-11-30.
//

#ifndef Experiments_hpp
#define Experiments_hpp

#include <chrono>
#include <vector>

/// Measures the execution time of a function call
struct ExecutionTimeMeasurer
{
    ///
    /// Measure the execution time of a function call
    ///
    /// @param trials Specify the number of trials to invoke the given function
    /// @param func A callable function
    /// @param args Zero or more arguments passed to the function
    /// @return The medium execution time.
    ///
    template <typename Func, typename... Args>
    uint64_t operator()(size_t trials, Func&& func, Args&&... args)
    {
        // Allocate the storage to record the execution time of each trial
        std::vector<uint64_t> durations;

        durations.reserve(trials);

        // Run the experiment
        for (size_t trial = 0; trial < trials; trial += 1)
        {
            // Measure the execution time
            auto start = std::chrono::high_resolution_clock::now();

            std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

            auto end = std::chrono::high_resolution_clock::now();

            // Store the execution time
            durations.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
        }

        // Find the medium value
        std::sort(durations.begin(), durations.end());

        return durations[trials / 2];
    }
};

/// Measures the execution time of a function call and returns the result
struct ExecutionTimeMeasurerWithResult
{
    ///
    /// Measure the execution time of a function call
    ///
    /// @param trials Specify the number of trials to invoke the given function
    /// @param func A callable function
    /// @param args Zero or more arguments passed to the function
    /// @return The medium execution time along with the invocation result.
    ///
    template <typename Func, typename... Args>
    std::pair<uint64_t, std::invoke_result_t<Func, Args...>> operator()(size_t trials, Func&& func, Args&&... args)
    {
        return std::make_pair(ExecutionTimeMeasurer{}(trials, std::forward<Func>(func), std::forward<Args>(args)...),
                              std::invoke(std::forward<Func>(func), std::forward<Args>(args)...));
    }
};

#endif /* Experiments_hpp */
