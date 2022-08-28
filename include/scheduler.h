//@author Ryan Xu
#pragma once
#include <functional>
#include <vector>

#include "processor.h"
#include "processor_selector.h"

/**
 * @brief
 * 让用户指定协程运行在某个Processor上，若用户没有指定，则挑选协程数量最少的Processor接管新的协程
 */
namespace tinyco {

class Scheduler {
 protected:
  Scheduler();
  ~Scheduler();

 public:
  DISALLOW_COPY_MOVE_AND_ASSIGN(Scheduler);

  static Scheduler* getScheduler();

  //在idx号线程创建新协程
  void createNewCo(std::function<void()>&& func, size_t stackSize);
  void createNewCo(std::function<void()>& func, size_t stackSize);

  Processor* getProcessor(int);

  int getProCnt();

  void join();

 private:
  //初始化Scheduler，threadCnt为开启线程的数目
  bool startScheduler(int threadCnt);

  //日志管理器实例
  static Scheduler* pScher_;

  //用于保护的锁，为了服务器执行效率，原则上不允许长久占有此锁
  static std::mutex scherMtx_;

  std::vector<Processor*> processors_;

  ProcessorSelector proSelector_;
};

}  // namespace tinyco