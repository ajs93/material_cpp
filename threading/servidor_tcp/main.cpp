#include <Servidor.hpp>

#include <signal.h>

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>

static std::mutex __mtx;
static std::condition_variable __cv;
static std::atomic_bool __run{true};

static void sigint_handler(int sig) {
  __run = false;
  __cv.notify_all();
}

int main() {
  struct sigaction new_handler = {{0}}, old_handler = {{0}};
  new_handler.sa_handler = sigint_handler;
  if (sigaction(SIGINT, &new_handler, &old_handler) == -1)
  {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }

  try {
    Servidor server;

    std::unique_lock<std::mutex> locker(__mtx);
    __cv.wait(locker, []{return !__run.load();});
  } catch (const std::exception &e) {
    std::cerr << "Excepcion: " << e.what() << std::endl;
  }

  return 0;
}