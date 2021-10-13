#include <iostream>
#include <pthread.h>

template <typename T, void (T::*runtime)()>
void* start_routine(void* param) {
  T* obj = (T*)param;
  (obj->*runtime)();
  return NULL;
}
class CThreadWrapper {
 public:
  CThreadWrapper() {
    pthread_create(&m_id, NULL,
                   start_routine<CThreadWrapper, &CThreadWrapper::runtime>,
                   this);
  }
  ~CThreadWrapper() { pthread_join(m_id, NULL); }
  void runtime() { std::cout << "thread function" << std::endl; }

 private:
  pthread_t m_id;
};
int main(int argc, char* argv[]) {
  CThreadWrapper mythread;
  return 0;
}