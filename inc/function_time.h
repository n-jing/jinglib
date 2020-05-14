#ifndef FUNCTION_TIME_JJ_H
#define FUNCTION_TIME_JJ_H

#include <ctime>
#include <iostream>

// use macros PRINT_FUNC_RUN_TIME to control whether print function run time or not

#ifdef PRINT_FUNC_RUN_TIME
#define PRINT_RUN_TIME true
#else
#define PRINT_RUN_TIME false
#endif

#define CALL_FUNC(func)                                                 \
  {                                                                     \
    clock_t start = clock();                                            \
    func;                                                               \
    clock_t end = clock();                                              \
    if (PRINT_RUN_TIME)                                                 \
      std::cout << "\n-- time cost: " << double(end-start) / CLOCKS_PER_SEC << " second." << std::endl; \
  }

#define CALL_FUNC_MESSAGE(func, message)                                \
  {                                                                     \
    clock_t start = clock();                                            \
    func;                                                               \
    clock_t end = clock();                                              \
    if (PRINT_RUN_TIME)                                                 \
      std::cout << "\n-- " << message << " time cost: " << double(end-start) / CLOCKS_PER_SEC << " second." << std::endl; \
  }

#define CALL_FUNC_MESSAGE_RET(func, message, ret)                       \
  {                                                                     \
    clock_t start = clock();                                            \
    ret = func;                                                         \
    clock_t end = clock();                                              \
    if (PRINT_RUN_TIME)                                                 \
      std::cout << "\n-- " << message << " time cost: " << double(end-start) / CLOCKS_PER_SEC << " second." << std::endl; \
  }

#define GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4
#define CALL_FUNC_TIME_CHOOSE(...)              \
  GET_4TH_ARG(__VA_ARGS__,                      \
              CALL_FUNC_MESSAGE_RET,            \
              CALL_FUNC_MESSAGE,                \
              CALL_FUNC, )

#define CALL_FUNC_TIME(...) CALL_FUNC_TIME_CHOOSE(__VA_ARGS__)(__VA_ARGS__)

#endif // FUNCTION_TIME_JJ_H
